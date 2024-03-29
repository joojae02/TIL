
데이터베이스를 보다보면 거의 필수적으로 보게되는 인덱싱이라는 내용이 있다.

찾아보면 간단하게는 검색 속도를 향상시키기 위해 사용한다고 주로 말하고 있는데
좀 더 자세히 알아보았다.

우선
> 인덱스는 데이터베이스 분야에 있어서 테이블에 대한 동작의 속도를 높여주는 자료 구조를 말한다.

즉 **추가적인 저장 공간을 사용해서 테이블 검색 속도를 향상**시키기 위한 자료구조이고
인덱스에는 키와 데이터의 물리적 위치가 저장된다.

## 왜 쓰는데??

위에서 말했던대로 검색 속도를 위해 사용하는데

만약 찾고자 하는 데이터가 테이블의 마지막에 있다면?? 모든 데이터를 탐색해야 한다.
이걸 Full Table Scan이라 하고 O(N)의 시간복잡도를 가진다.

또한 메모리 공간에 비해 데이터의 양이 월등히 많다면
작은 메모리에 여러번에 걸쳐 꺼내와진다

이런 경우 **IO 성능이 매우 떨어지게** 된다.

근데 인덱스는 실제 테이블에 비해 훨씬 크기가 작다.
따라서 인덱스를 사용하면 불필요한 IO를 줄여 탐색 성능을 개선할 수 있다.
- 인덱스만을 메모리에 올리면 된다.

## 알고리즘들

그래서 이런 인덱싱을 위해 알고리즘을 사용하는데

### Hash Table

Hash Table은 Key를 사용해 자료에 접근하는 자료구조이다.
데이터의 key를 알고 있다면 O(1)의 시간복잡도로 접근이 가능하다.

근데 보통 Hash Table을 쓰지 않는다

- Hash Table은 부등호 연산에 부적합.

Hash Table의 데이터는 정렬되어 있지 않다.

그래서 부등호 연산을 위해서는 풀스캔을 해야한다.

### B-Tree

B-Tree는 대용량 데이터를 효과적으로 관리하기 위한 자료구조이다.

![](https://i.imgur.com/CZCaJ9x.png)

일단 트리 구조를 가지고 노드가 
- 키
- 키가 가르키는 데이터
- 키 값의 수보다 한개 더 많은 하위 노드들을 가르키는 포인터
를 가진다.

기본적으로는 Binary Tree와 유사하지만
노드에 한개 이상의 키를 가질 수 있다.
- 깊이가 낮아져 빠른 탐색이 가능해짐

그리고
- 리프 노드가 모두 같은 레벨을 갖는다.
Binary Tree는 한쪽으로만 이어지고 깊어져 링크드 리스트 같은 형태가 될 수 있다.

이를 B-Tree는 리프 노드의 레벨을 동일하게 유지해 해결한다.

B-Tree는 
탐색, 삽입, 삭제, 수정에 O(logN)의 시간 복잡도를 가진다.

B-Tree는 Hash Table보다 성능이 좋지는 않지만 범위 탐색이 가능한 자료구조로 더 많이 사용된다.

### B+Tree

위 B-Tree에 단점이 몇가지 있는데
- 탐색에서 방문 노드의 모든 데이터 탐색 필요
- 삽입, 수정, 삭제 연산으로 트리 구조 재정렬 시 데이터의 이동이 필요
- 노드에 데이터가 포함되어 노드가 포함할 수 있는 키의 개수가 적음
	- 트리의 깊이가 깊어짐\
	
![](https://i.imgur.com/d8eTaxM.png)

그래서 다음으로 B+Tree가 나왔는데
내부 노드에 키 값, 자식 노드의 포인터만을 가지고

실질 데이터는 모두 마지막 리프 노드에 위치하고 이 노드들은 링크드 리스트로 이어진다.

노드에 포인터만 존재하게 되면서 노드에 더 많은 키를 저장하게 되고
이는 트리의 높이를 낮아지게 한다.

따라서 탐색 속도가 더 향상된다.

또 순차 검색에 유리하다.
DB에서 부등호 연산이 많이 자주 이뤄지는데 
링크드 리스트라 더 빠르게 순차 검색이 가능해진다.

## 그래서 그냥 다 인덱싱하면 되는건가??

그렇다고 모든 테이블에 인덱스를 적용하게 되면 오히려 안좋을 수 있다..

인덱스는 저장공간을 필연적으로 사용하게 된다.
자칫하면 저장공간만 낭비하게 된다.

또한 조회 성능은 증가하지만 삽입, 수정 삭제가 일어나면 인덱스 또한 업데이트를 해 전체적인 성능이 저하될 수 있다.

쿼리가 인덱스와 잘호환되지 않는 경우 예를 들어 where절의 조건과 일치하지 않는 인덱스인 경우 등등에 성능이 저하될 수 있다.

## 언제 써야되는데??
### 카디널리티 (Cardinality)
주로 말하는 
> 인덱스 대상 컬럼은 **카디널리티(cardinality)가 높은 컬럼**을 선택해야 한다.

여기서 카디널리티란 집합에서 **유일한 데이터의 개수**를 의미한다.
그니까 한 컬럼이 갖고 있는 값의 중복 정도가 낮을 수록 좋다.

### 선택도 (Selectivity)

데이터에서 특정 값을 얼마나 잘 선택할 수 있는지에 대한 지표이다.
선택도
> = 컬럼의 특정 값의 row 수 / 테이블의 총 row 수 * 100  
> = 컬럼의 값들의 평균 row 수 / 테이블의 총 row 수 * 100

보통 5~10%가 적당하다고 한다.
> 즉, 선택도는 특정 필드값을 지정했을 때 선택되는 레코드 수를 테이블 전체 레코드 수로 나눈 것
### 활용도

해당 컬럼이 실제 작업에서 얼마나 활용되는지에 대한 값이다.
수동 쿼리 조회, 로직과 서비스에서 쿼리를 날릴 때 WHERE 절에 자주 활용되는지를 판단하면 된다.

### 중복도

중복 인덱스 여부에 대한 값이다.

당연히 없을수록 좋다.

## 참고
- https://tcpschool.com/mysql/mysql_index_create
- https://www.geeksforgeeks.org/introduction-of-b-tree-2/
- https://yurimkoo.github.io/db/2020/03/14/db-index.html
- https://velog.io/@sem/DB-%EC%9D%B8%EB%8D%B1%EC%8A%A4-%EC%9E%90%EB%A3%8C-%EA%B5%AC%EC%A1%B0-B-Tree
- https://ko.wikipedia.org/wiki/B_%ED%8A%B8%EB%A6%AC
- https://www.baeldung.com/cs/b-trees-vs-btrees
- https://jjy0821.tistory.com/45
- https://velog.io/@bsjp400/Database-DB-%EC%9D%B8%EB%8D%B1%EC%8B%B1Indexing%EC%9D%B4%EB%9E%80