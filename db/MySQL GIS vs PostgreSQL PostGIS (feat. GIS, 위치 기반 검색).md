
지난, 이번 프로젝트 모두 위치 기반으로 검색하는 기능이 메인이다.

사실상 디비에서 데이터를 꺼내올 때 위치기반 즉 공간 정보를 필요로 하게 된다.

## 지리정보시스템(GIS)

GIS는 Geographic Information System의 약자로 지리정보를 컴퓨터 데이터로 변환하여 효율적으로 활용하기 위한 정보시스템이다.

보통 이런 데이터를 저장할 때
- 점 (Point) `POINT(10 10)`
- 선 (Line) `LINESTRING(10 10, 20 20)`
- 면 (Polygon) `POLYGON((10 10, 10 20, 20 20, 20 10, 10 10))`
3개로 표현한다.

이런 데이터를 저장하고 있는 디비를 공간 디비라고 부른다.

그중에서 MySQL, PostgreSQL PostGIS가 대표적인데

## MySQL GIS vs PostgreSQL PostGIS

### MySQL GIS

MySQL의 GIS는 5.7버전 이후로 지원하고 있다.
[MySQL 5.7](https://dev.mysql.com/doc/refman/5.7/en/spatial-types.html)여기서 확인해 볼 수 있다.

MySQL은 Geometry 데이터타입과 간단한 공간 인덱스를 지원하고 있다.

### PostgreSQL PostGIS

PostgreSQL 객체지향 데이터베이스이다.
근데 우리가 쓸때는 그냥 일반 관계형 DB처럼 사용하면 된다.

그중에서 PostGIS라는 확장 기능인데
[About PostGIS](https://postgis.net/)를 읽어보면 보다 자세히 알아볼 수 있다.

간단하게 Geometry, Geography 타입, 함수들을 지원한다.

### 비교

우선 간단하게만 말하자면
PostgreSQL PostGIS의 성능이 압도적으로 좋다.

- 고급 위치 기반 쿼리를 자주 수행해야 하는 경우
- GIS 데이터를 다루거나 지리 정보 시스템을 사용하는 경우
- 복잡한 공간 연산이 필요한 경우
와 같이 

GIS 기능을 고급으로 사용하고 복잡한 공간 연산이 이뤄지는 그런 경우에는 당근 성능 좋은 PostgreSQL를 쓰는것이 좋다.

#### MySQL
- 장점
	- 기본적인 공간 데이터 처리
	- 간단한 공간 데이터 처리에 대해서는 성능이 괜찮
	- 많은 문서와 자료
	- 쉽고 익숙함
- 단점
	- 고급 공간 분석 및 기능은 제한적
	- 복잡한 공간 분석이나 대규모 데이터셋에서는 성능이 저하

#### PostGIS
- 장점
	- 다양한 공간 함수와 연산을 제공
	- 복잡한 공간 쿼리와 분석을 지원
	- 대규모 데이터셋에서도 높은 성능
- 단점
	- MySQL 보다는 적은 자료
	- MySQL 보다는 어려움

## 결론

어떤 디비를 쓸지.

> 사실 선택이다.

만약 추후 공간 데이터를 이용한 여러 연산들이 추가될것 같다? 
- PostgreSQL

성능이 중요하고 복잡한 연산, 큰 데이터셋이다? 
- PostgreSQL

개발 시간이 부족하고 PostgreSQL에 익숙하지 않다?
- MySQL

MySQL를 사용하는데 성능이 너무 안좋다??
- 복합인덱스 사용

단순 범위 내 검색과 같은 쿼리는 복합인덱스를 사용해주면 어느정도 속도보완이 되기 때문에
간단한 쿼리에서는 그렇게 크게 차이가 나지 않는다

이래저래 서로 장단점이 달라서
각자 현재 상황에 맞게 선택해주면 될것 같다.

예를 들어서
내 지난 프로젝트에서는 PostgreSQL를 사용했지만 MySQL로 사용하는 것이 좋았을 것 같다.
Prisma에서 PostGIS를 지원하지 않기 때문에 모두 로우 쿼리로 써야해 오히려 불편했던 경험이 있다.
차라리 MySQL 이였다면 Prisma의 장점을 더 챙길 수 있지 않았을까 생각이 든다.


속도 비교 관련해서는
- https://velog.io/@sdsd0908/%EC%8A%A4%ED%94%84%EB%A7%81-%EB%B0%98%EA%B2%BD-%EA%B2%80%EC%83%89-%EA%B8%B0%EB%8A%A5-DB-%EB%B3%80%EA%B2%BD%EC%97%90-%EB%8C%80%ED%95%9C-%EA%B3%A0%EB%AF%BC
- https://steemit.com/kr-dev/@tmkor/db-2-mysql-vs-postgis-postgresql

비교 관련
- https://stackshare.io/stackups/mysql-vs-postgis
- https://stackoverflow.com/questions/3743632/gis-postgis-postgresql-vs-mysql-vs-sql-server

등을 읽어보면 좋을 것 같다.

