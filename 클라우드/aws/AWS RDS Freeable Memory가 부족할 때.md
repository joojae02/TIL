
![](https://i.imgur.com/Q9O9eoO.png)

최근 RDS의 Freeable Memory가 부족하다는 경고가 왔습니다.
현재 RDS MySQL를 사용하고 있습니다.

Freeable Memory란 인스턴스에서 사용할 수 있는 가용 메모리를 얘기합니다.

AWS Docs에서는 DB 인스턴스 RAM에 working set이 실제 메모리에 충분히 할당되어 있어야 된다고 말합니다.
당근 메모리에 올라와 있어야 디스크 읽는 횟수도 줄어들고 훨씬 빠르게 값을 줄 수 있습니다.

그래서 RDS를 사용하게 되면 기본적으로 75% 정도를 InnoDB 버퍼 풀로 사용하게 됩니다.

```
innodb_buffer_pool_size = {DBInstanceClassMemory*3/4}
```

이런식으로 파라미터 그룹에 할당되어 있습니다.

근데 당근 여기서만 메모리를 사용하는게 아니죠
```
Maximum MySQL Memory Usage = innodb_buffer_pool_size + key_buffer_size + ((read_buffer_size + read_rnd_buffer_size + sort_buffer_size + join_buffer_size) X max_connections)
```

총 MySQL 메모리를 계산하려면 다음과 같은 식으로 계산할 수 있습니다.

## 그래서 Freeable Memory가 줄어들면 뭐가 문제??

기본적으로 어떤 값을 찾을때 메모리를 확인하고 없다면 디스크를 읽습니다.
당근 메모리가 빠르죠

그래서 성능면에서 최대한 메모리에 올라와있는것이 좋습니다.

다만 Freeable Memory가 줄어 0에 가까워지고 Swap을 사용하기 시작하면
ReadIOPS, DiskIO 가 급격하게 상승하면서 속도가 매우 느려지게 됩니다.

위 계산식에서 

```
((read_buffer_size + read_rnd_buffer_size + sort_buffer_size + join_buffer_size) X max_connections)
```

접속이 늘어나게 되면 메모리가 줄어들게 됩니다.

만약 접속자가 급격하게 늘어나고 Freeable Memory가 없다면??
- DB 성능이 매우 떨어지게 됩니다.

그래서 어느정도의 Freeable Memory를 남기는것이 좋습니다.
AWS에서는 전체 메모리의 5%정도로 유지하는것을 권장합니다.

## 해결방법

### 더 큰 메모리의 인스턴스로 교체
가장 편하고 권장되는 방식입니다.

당근 더 큰 메모리가 있다면 문제가 없겠죠

다만 비용이 많이 비싸집니다....

### innodb_buffer_pool_size 수정

기본적으로 가장 많은 메모리를 사용하는 값을 수정하는 방식입니다.

DBInstanceClassMemory* 3/4 는 5/8 또는 1/2로 수정하여 사용할 수 있습니다.

다만 버퍼 풀 사이즈를 줄이게 되면 그만큼 메모리에 올라가는 값이 줄어들게 되어서 성능이 저하될 수 있습니다.
따라서 **BufferCacheHitRatio** 값을 확인하면서 적절하게 변경하는것이 좋습니다.

### 기본적인 쿼리 개선 및 인덱스 관리

다중 쿼리, 효율적이지 못한 쿼리, 다중 조인 등등 이런저런 이유로 메모리가 많이 차지될 수 있습니다.

특히 다중 조인, 다중 쿼리 같은 경우 쿼리는 하나씩 실행되지만 모든 쿼리가 끝나기 전까지 메모리에서 free 되지 않습니다.

따라서 지표를 보며 슬로우 쿼리를 개선하고 사용하지 않는 인덱스는 지우는 등의 작업이 필요합니다.

- 지속적으로 Freeable Memory가 줄어드는것이 아니고 급격하게 줄어들었다면 특정 쿼리의 문제일 가능성이 높습니다.

### DB 부하 분산

Read Replica나 Multi AZ 등 여러 대의 DB를 이용해서 성능을 개선할 수 있습니다.

예를 들어 Read Replica를 이용해서 Read시에 사용하는 DB를 놓고 분산하는 등의 작업을 할 수 있습니다.
- 레플리카를 이용할 때는 복제 지연이 있을 수 있기에 적절하게 선택해줘야합니다.

다만 다른 방법들에 비해 난이도가 높고 작업 규모가 크다는 단점이 있습니다.

또한 Lambda와 같이 빠르게 접속하고 끊어지는 작업이 많은 경우에 RDS Proxy를 사용해 커넥션 풀링을 사용할 수 도 있습니다.
- 커넥션 수를 줄여 성능을 개선할 수 있습니다.

## 결론

- 현재 워크로드에 맞는 적절한 인스턴스를 선택하자
- 쿼리, 인덱스를 신경쓰자

- ReadIOPS를 보고 innodb_buffer_pool_size를 조정하자

전 innodb_buffer_pool_size를 조정하는 방식을 선택하게 되었습니다.


## 참고자료
- https://aws.amazon.com/blogs/database/best-practices-for-configuring-parameters-for-amazon-rds-for-mysql-part-1-parameters-related-to-performance/
- https://repost.aws/knowledge-center/low-freeable-memory-rds-mysql-mariadb
- https://repost.aws/knowledge-center/rds-sql-server-correct-low-memory
- https://stackoverflow.com/questions/15332158/amazon-rds-running-out-of-freeable-memory-should-i-be-worried
- https://tech.buzzvil.com/blog/rds-mysql-%EB%A9%94%EB%AA%A8%EB%A6%AC-right-sizing/
- https://www.bluematador.com/docs/troubleshooting/rds-free-memory
- https://www.percona.com/blog/best-practices-for-configuring-optimal-mysql-memory-usage/