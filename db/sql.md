# SQL
> Structured Query Language의 줄임말로써, 번역하면 구조적인 Query언어를 의미

## 쿼리(Query)
>  "질의문" 이라는 뜻  
> 데이터를 필터하기 위한 질문

## SQL 쿼리문

### CREATE DATABASE
```sql
CREATE DATABASE [데이터베이스 명]
```
### DROP
- 데이터 베이스 자체를 삭제할때 사용
- 테이블을 삭제 할때도 사용가능
```sql
DROP DATABASE [데이터베이스 명]
DROP TABLE [테이블명]
```
### ALTER
- 테이블에 컬럼을 추가 및 삭제
```sql
ALTER TABLE [테이블명] ADD [추가할 컬럼이름] 데이터형(데이터크기) 컬럼속성
ALTER TABLE [테이블명] DROP COLUMN [삭제할 컬럼이름]
```
### TRUNCATE
- 테이블에 있는 데이터를 한번에 제거
- 테이블이 최초 생성되었을 당시의 Storage만 남김
-  DROP은 테이블을 완전히 날려버리지만 TRUNCATE는 테이블이 남기 때문에 재사용 가능
```sql
TRUNCATE TABLE [테이블명]
```

### CRAEAT TABLE
- 테이블을 새롭게 추가
- 데이터베이스를 생성한 후, use [데이터베이스]로 해당 데이터 베이스를 사용한다고 선언한 후 CREAT TABLE [테이블명]
- 필드(컬럼)또한 같이 만들어 주어야함
```sql
CREATE TABLE 테이블명
```

### SELECT
- SELECT는 데이터셋에 포함될 특성을 특정
```sql
SELECT DISTINCT Country FROM Customers;
//Customers 테이블에서 Country라는 필드만 중복없이 출력해라

SELECT City FROM Customers;
//Customers 테이블에서 City라는 필드만 출력해라
```
### FROM
- 테이블과 관련한 작업을 할 경우 반드시 입력을 해야함.
### Distinct
- 데이터의 중복을 제거 할 때 사용
```sql
SELECT DISTINCT Country FROM Customers;
//Customers 테이블에서 Country라는 필드만 중복없이 출력해라
```
### Where
- 필터 역할, 선택적으로 사용
- 조건문
```sql
SELECT * FROM Customers 
WHERE City= 'Berlin';
//Customers라는 테이블에서 City라는 필드명에 'Berlin'이라는 값이 들어가 있는것의 row를 전부다 출력하라.

SELECT * FROM Customers
WHERE NOT City= 'Berlin';
//Customers라는 테이블에서 City라는 필드명에 'Berlin'이라는 값이 들어가 있는것만 빼고 모든 값을 전부다 출력하라.
```
### Order By
- 데이터 결과를 어떤 기준으로 정렬하여 출력할지 결정

### Insert
- 테이블에 데이터를 추가

```sql
INSERT INTO 테이블 이름 (column,column, ...)
VALUE (값1, 값2, ...);
```
### Update
- 테이블에 데이터를 수정할때 사용
- SET과 같이 씀
```sql
UPDATE [테이블] SET [column] = '변경할값' WHERE [조건]
```
### Delete
- 테이블에서 행을 제거하기위해 delete를 사용
-  FROM으로 어느 테이블을 지울것인지 설정
```sql
DELETE FROM [테이블] WHERE [조건]
```
### IN
- WHERE절 내에서 특정값 여러개를 선택하는 SQL 연산자
```sql
SELECT * FROM [테이블명] WHERE [컬럼명] IN(값,값)
```
### Between
- 특정한 범위나 값 사이에 있는 값을 가져옴
```sql
SELECT * FROM [테이블] WHERE [컬럼] BETWEEND A AND B
```
### Join
- 둘 이상의 테이블을 연결해서 데이터를 검색
- 연결하려면 테이블들이 적어도 하나의 공통된 컬럼이 있어야함
