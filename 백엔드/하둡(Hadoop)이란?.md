MSA나 빅데이터, 등등 분산 처리, 비동기 처리 같은 내용을 찾아보다 보면
하둡이라는 말이 자주 등장하는 것을 볼 수 있다

아무튼 하둡이란 간단히 말하면
> 안정적이고 확장 가능한 분산 컴퓨팅을 위한 오픈 소스 소프트웨어이다

## 하둡 ?.?
더그 커팅이 '넛치'라는 검색엔진을 개발하는 과정에서 대용량의 비정형 데이터를 기존의 RDB 기술로는 처리가 힘들다는 것을 깨닫고
새로운 기술을 찾는 중 구글에서 발표한 GFS와 MapReduce 관련 논문을 참고하여 개발되었다
이후 아파치 재단의 오픈 소스로 공개되었다

논문이 궁금한 사람은 [GFS](https://static.googleusercontent.com/media/research.google.com/en//archive/gfs-sosp2003.pdf), [MapReduce](https://static.googleusercontent.com/media/research.google.com/en//archive/mapreduce-osdi04.pdf)를 확인해보자
좀 많이 많이 어려움..ㅎ..

결국 분산처리 시스템인 구글 파일 시스템(GFS)을 대체할 수 있는 **하둡 분산 파일 시스템(HDFS)**
그리고 데이터를 분산시켜 처리한 뒤 하나로 합치는 기술인 **MapReduce**를 구현한 오픈소스 프레임워크이다

여러 컴퓨터로 구성된 클러스터를 이용하여 방대한 양의 데이터를 처리할 수 있도록 도와주는 프레임워크이다


원래는 하둡파일시스템(HDFS)과 맵리듀스(MapReduce) 프레임워크로 시작되었으나
이제는 **하둡 생태계 (Hadoop Ecosystem)** 전반을 포함하는 의미가 되었다

![](https://i.imgur.com/GB1dVb4.png)


## 하둡 코어 프로젝트 
- HDFS(분산 데이터 저장)
- MapReduce(분산 처리)

### 하둡 분산형 파일 시스템 (HDFS)
> 하둡 네트워크에 연결된 기기에 데이터를 저장하는 분산형 파일 시스템

하둡 분산 파일 시스템은 하둡 프레임워크를 위해 자바 언어로 작성된 분산 확장 파일 시스템이다
HDFS는 여러 기계에 대용량 파일을 나눠서 저장해 데이터 안정성을 확보한다

- HDFS는 데이터를 저장하면 다수의 노드에 복제 데이터도 함께 저장해 데이터 유실을 방지한다
- HDFS에 파일을 저장하거나, 저장된 파일을 조회하려면 스트리밍 방식으로 데이터에 접근해야한다
	- 랜덤 방식의 데이터 접근을 고려하고 있지 않음
- 한번 저장한 데이터는 수정할 수 없고, 읽기만 가능해서 데이터 무결성을 유지한다
- 데이터 수정은 불가능, 파일 이동, 삭제, 복사할 수 있는 인터페이스를 제공한다

![](https://i.imgur.com/6SMMXHV.png)

뭐 여러 세부 내용들이 있는데 현재 글은 하둡에 대해서 간단히 설명하는것이라
몇몇 특징만 적고 넘어가겠다

- 블록 단위 저장
- 마스터-슬레이브 구조로 네임노드와 데이터노드 존재
### 맵 리듀스(MapReduce)
> 대용량의 데이터 처리를 위한 분산 프로그래밍 모델, 소프트웨어 프레임워크

대규모 분산 컴퓨팅 환경에서 대량의 데이터를 병렬로 분석 가능케 한다

흩어져있는 데이터를 수직화
그 데이터를 각각의 종류별로 모으고(Map)
필터링과 sorting을 거쳐 데이터를 뽑아내는(Reduce) 분산처리 기술
등을 총 집합하는 프레임워크를 의미한다

![](https://i.imgur.com/XfmZN6v.png)


## 다른 프로젝트
### ZooKeeper
![](https://i.imgur.com/uoSC2SH.png)
- 주키퍼는 분산 코디네이션 서비스를 제공하는 오픈소스 프로젝트이다
- 직접 어플리케이션 작업을 조율하는 것을 쉽게 개발할 수 있도록 도와준다
- API를 이용해 동기화나 마스터 선출 등의 작업을 쉽게 구현할 수 있게 해준다

### YARN
![](https://i.imgur.com/nTnLeBM.png)

**CPU, memory와 같은 하둡 클러스터 리소스를 관리하고 스케쥴링**하는 hadoop의 컴포넌트이다
### Kafka
![](https://i.imgur.com/1oyDCja.png)

데이터 스트리밍을 실시간으로 관리하기 위한 분산시스템, 대용량 이벤트 처리를 위해 사용
요새는 MSA 아키텍처로 가면서 많이 사용한다

### Hive
![](https://i.imgur.com/JMFFHKx.png)



하둡에 저장된 데이터를 쉽게 처리하는 데이터 웨어하우스 패키지이다
핵심용어는 SQL기반의 **HiveQL**이라는 쿼리문을 사용해 데이터를 처리한다
### Pig
![](https://i.imgur.com/rLQ9qmQ.png)
대용량 데이터를 다루기 위한 스크립트 언어이다
MapReduce에 없는 Join 등과 같은 기능이 존재한다

### Spark
![](https://i.imgur.com/g3BQrKo.png)
![](https://i.imgur.com/xQsibfJ.png)

빅데이터 처리를 위한 오픈소스 분산 처리 플랫폼이다
카프카, 플럼, 키네시스, TCP 소켓 등 다양한 경로를 통해서 데이터를 입력 받고, map, reduce, window 등의 연산을 통해 데이터를 분석하여 최종적으로 파일시스템, 데이터베이스 등에 적재된다


## 결론

사실 하둡 에코시스템에는 글에서 설명한 것들 외에도 많이 존재한다

백엔드 개발하면서 주로 접하게되는건 주키퍼, 카프카, 스파크라고 생각한다
MSA와 같은 분산형 아키텍쳐를 사용하면서 메세지 큐로 카프카를 사용하고
로그들을 모으는 용도로 스파크를 사용하고
전체를 관리해주는 주키퍼를 사용하게 된다

근데 AWS 등에서 완전 관리형으로 모두 지원해준다

그치만 인프라에서 중요한 점이 또 금액인 만큼
전체 규모가 커질수록 오픈소스로 직접 구축하는게 훨~씬 싸다

그래서 하둡에 대해서 기본적인 내용들만 알아봤는데
다음 글에서는 주키퍼, 카프카 등 하나하나 정리해봐야겠다

#### 참고 자료
- https://www.databricks.com/kr/glossary/hadoop
- https://wikidocs.net/22654
- https://hadoop.apache.org/
- https://aws.amazon.com/ko/elasticmapreduce/details/hadoop/
- https://velog.io/@jochedda/%ED%95%98%EB%91%A1Hadoop%EC%9D%B4%EB%9E%80
- https://www.youtube.com/watch?v=tzsPfkub5XY
- https://aws.amazon.com/ko/what-is/apache-kafka/
- https://aws.amazon.com/what-is/apache-spark/?trk=faq_card
- 