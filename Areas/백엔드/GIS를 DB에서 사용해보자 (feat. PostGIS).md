
## GIS(Geographic Information System)란??

지리 정보 시스템(GIS)은 지리 공간 데이터를 말한다.
즉 지구를 공간적으로 참조하는 데이터를 연결하여 시각화를 생성하는 컴퓨터 시스템입니다.

간단하게 말하면 지리 정보를 수치 데이터로 사용하는 걸 말한다.

예를 들어
특정 위치를 표한하면
- Point
- Line
- Polygon
- MultiPolygon
같은 방식으로 공간 데이터를 저장할 수 있다.

## 그럼 DB에 어케 저장하는데?

DB에 저장할떄는 보통 GIS를 지원하는 데이터베이스에 저장하거나
raw data 형태로 저장할 수 있다.

다만 raw형태는 공간 기반 같은 쿼리를 사용하기 어렵기 떄문에
GIS를 지원하는 DB에 저장하는것이 간편하고 성능에도 좋다.

그럼 어떤 디비를 쓸지 선택해줘야한다.

주로 
- mysql
- postgresql

두가지 중 하나를 사용한다.

### MySQL

MySQL의 GIS는 5.7버전 이후로 지원하고 있다.  
[MySQL 5.7](https://dev.mysql.com/doc/refman/5.7/en/spatial-types.html?ref=joojae.com)여기서 확인해 볼 수 있다.

MySQL은 Geometry 데이터타입과 간단한 공간 인덱스를 지원하고 있다.

예를 들어서
```sql
CREATE EXTENSION IF NOT EXISTS `mysql-geometry`;
```
Extension을 깔아주고

```sql
CREATE TABLE Region (
    id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(255) NOT NULL,
    boundary GEOMETRY NOT NULL, -- Geometry 타입 사용
);
```


```sql
INSERT INTO regions (name, boundary) VALUES
(
    'Region A',
    ST_GeomFromText('MULTIPOLYGON(((
        0 0, 10 0, 10 10, 0 10, 0 0
    )), ((
        15 15, 25 15, 25 25, 15 25, 15 15
    )))')
),
(
    'Region B',
    ST_GeomFromText('MULTIPOLYGON(((
        30 30, 40 30, 40 40, 30 40, 30 30
    )))')
);

SELECT id, name 
FROM regions 
WHERE ST_Contains(boundary, ST_GeomFromText('POINT(5 5)'));
```


요런 식으로 현재 Point가 포함된 지역을 찾는 쿼리를 사용해볼 수도 있다~

### PostgreSQL + PostGIS

```sql
CREATE EXTENSION postgis;
```

똑같이 Extention 활성화 후

```sql
CREATE TABLE regions (
    id SERIAL PRIMARY KEY,
    name VARCHAR(255) NOT NULL,
    boundary GEOMETRY(MultiPolygon, 4326) NOT NULL  -- WGS 84 좌표계 사용
);
```

```sql
INSERT INTO regions (name, boundary) VALUES
(
    'Region A',
    ST_GeomFromText('MULTIPOLYGON(((
        0 0, 10 0, 10 10, 0 10, 0 0
    )), ((
        15 15, 25 15, 25 25, 15 25, 15 15
    )))', 4326)
),
(
    'Region B',
    ST_GeomFromText('MULTIPOLYGON(((
        30 30, 40 30, 40 40, 30 40, 30 30
    )))', 4326)
);

SELECT id, name 
FROM regions 
WHERE ST_Contains(boundary, ST_GeomFromText('POINT(5 5)', 4326));
```

### 비교

PostGIS가 대부분의 상황에서 더 좋다고 한다.

기본적으로 제공되는 GIS 함수 자체도 PostGIS의 개수가 많다.

또한 인덱스에도 차이가 있는데
MySQL은 R-Tree 기반의 인덱스
PostGIS는 Gist라는 인덱스를 사용한다.

PostGIS의 초기 버전은 PostgreSQL R-Tree 인덱스를 사용했는데
PostgreSQL R-트리는 완전히 폐기되었고 GiST로 변경되었다고 한다.

> 원래 MySQL를 쓰던게 아니면.. PostGIS 쓰자~

## GeoJSON

다음은 지리 데이터를 저장하는 방식들 중 GeoJSON에 대한 내용이다.

```sql
INSERT INTO regions (name, boundary) VALUES
(
    'Region A',
    ST_GeomFromText('MULTIPOLYGON(((
        0 0, 10 0, 10 10, 0 10, 0 0
    )), ((
        15 15, 25 15, 25 25, 15 25, 15 15
    )))', 4326)
),
(
    'Region B',
    ST_GeomFromText('MULTIPOLYGON(((
        30 30, 40 30, 40 40, 30 40, 30 30
    )))', 4326)
);
```

해당 예시에서 사용하는 `ST_GeomFromText` 는 네이밍에서 나와있듯
Text에서 데이터를 뽑는 형태이다.

Well-Known Text 형태로 알아보기는 쉽지만 
한 두건 데이터 삽입할 떄는 좋지만

대량의 데이터를 넣기에는 가공하기 불편한 부분이 있다.

그래서 주로 사용하는 형태가 GeoJSON 형태인데

```json
{
  "type": "FeatureCollection",
  "features": [{
    "type": "Feature",
    "geometry": {
      "type": "Point",
      "coordinates": [125.6, 10.1]
    },
    "properties": {
      "name": "Dinagat Islands"
    }
  }]
}
```

요런 JSON 형태로 구성된다.

- type
- features

로 구성이 된다.
각 데이터하나하나가 features 배열에 저장된다.

```json
{
  "type": "Feature",
  "properties": {
  }, 
  "geometry": {
    "type": "MultiPolygon", 
    "coordinates": [] 
  } 
}
```

feature는 윗 예시 처럼 구성이 되어있는데

- `geometry` : Geometry Object (, Feature의 위치 값이 없는 경우 null 값을 사용 가능)
- `properties` : 속성 정보가 Key - Values 형태로 저장

이다.

여기서 GeoJSON의 장점이 나오는데 properties 에 자유롭게 데이터를 넣어서 저장이 가능하다

```sql
SELECT ST_GeomFromGeoJSON('{"type":"Polygon","coordinates":[[[354576.1845094707,370380.9369197765],[353507.26405659976,355721.45642326097],[377328.91986343754,352056.58629913203],[374885.6731140183,382139.06190135673],[363280.2510542768,383513.38819790503],[354576.1845094707,370380.9369197765]]],"crs":{"type":"name","properties":{"name":"EPSG:5186"}}}');
```

요런 식으로 `ST_GeomFromGeoJSON` 를 쓰면 간단하게 사용할 수 있다.




