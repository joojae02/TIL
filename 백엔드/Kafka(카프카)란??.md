![Apache Kafka 란 무엇인가요?팁코 소프트웨어|center|400](https://www.tibco.com/sites/tibco/files/media_entity/2020-10/apache-kafka-diagram.svg)

Kafka는 고성능 데이터 파이프라인, 스트리밍 분석 등을 위해 사용하는 오픈 소스 분산 이벤트 스트리밍 플랫폼이다.

## 이벤트 스트리밍??
**이벤트 스트리밍**은 연속 **이벤트 스트림**을 처리하거나 분석하는 것이다.
**이벤트 스트림**은 시간별로 정렬된 일련의 비즈니스 이벤트이다

달리 말하면 이벤트 소스에서 이벤트 스트림 형태로 실시간 데이터를 캡쳐하는 방식이다.
이를 나중에 검색할 수 있도록 영구적으로 저장한다 그리고 이벤트 스트림에 대해 실시간으로 반응한다.

따라서 이벤트 스트리밍은 데이터의 지속적인 흐름과 해석, 저장을 보장해 올바른 장소, 시간에 제공되도록 한다.

![|400](https://i.imgur.com/3KXMOec.png)

## 카프카가 이벤트 스트리밍 플랫폼??
Kafka는 3가지 주요 기능을 결합해 단일 솔루션으로 event streaming end-to-end을 사용할 수 있게 해준다

1. 데이터를 지속적으로 가져오기/내보내기 하며 이벤트 스트림을 **Publish**(쓰기), **Subscribe**(읽기)한다
2. 원하는 기간 동안 이벤트 스트림을 지속적, 안정적으로 **저장**한다.
3. 이벤트 스트림발생시 처리한다.

이 모든 기능들은 확장성이 뛰어나고 탄력적이며 안전한 분산 방식으로 제공된다.

## 어떻게 작동하는데??
Kafka는 고성능 **TCP network protocol**을 통해 통신하는 서버와 클라이언트로 구성된 분산 시스템이다.
#### 서버

Kafka는 하나 이상의 클러스터로 실행된다.
클러스터는 여러 데이터 센터 또는 클라우드 지역에 걸쳐 있을 수 있다.

이러한 서버 중 일부는 스토리지 계층으로 브로커라고 한다.

Kafka 클러스터는 확장성이 뛰어나고 내결함성이 뛰어나다.
> 서버 중 하나에 죽어도 다른 서버가 해당 작업을 대신하여 데이터 손실 없이 지속적인 작업을 보장함

#### 클라이언트

클라이언트는 데이터를 모으고 사용한다.

병렬로 확장하여 네트워크 문제나 시스템 오류가 있어도 작동할 수 있게 한다.
분산 애플리케이션과 마이크로서비스를 구현할 수 있도록 해준다.

## 주요 개념, 용어
#### Event(이벤트)
이벤트는 월드나 비지니스에 *무언가 일어난* 그 사실을 의미한다.
이는 레코드 또는 메시지로도 불린다.

Kafka에 데이터를 쓰고 읽을 때 이벤트의 폼으로 수행된다.

이벤트는 key, value, timestamp, optional metadata headers를 가진다.


#### Producer(생산자), Consumer(소비자)
Producer는 Kafka에 이벤트를 Publish(게시)하는 클라이언트이고 Consumer은 이런 이벤트를 Subscribe(읽고 처리)하는 클라이언트이다.

Kafka에서 Producer, Consumer는 서로 완전 분리되어 있다.
이는 Kafka의 높은 확장성를 위한 핵심 요소이다.
![](https://i.imgur.com/bYNKziM.png)

#### Topics

이벤트들은 주제별로 구성되고 저장된다.
간단하게 주제는 파일 시스템의 폴더와 유사하다고 보면 된다.

Topics는 항상 multi-producer, multi-subscriber이다.
토픽안 이벤트들은 필요할 때마다 읽을 수 있다.

전통적인 메세징 시스템과 달리 Kafka에서 이벤트는 소비 이후 지워지지 않는다.
대신 Kafka에 토픽별 설정을 통해 이벤트의 유지 시간을 설정한다.

Topic은 분할된다.
즉 다른 여러 Kafka 브로커에 같은 Topic이 존재한다.

이런 데이터 분산 배치는 클라이언트가 동시에 여러 브로커에서 데이터를 읽고 쓸 수 있도록 해준다.

![](https://i.imgur.com/5BQWWl9.png)

이벤트가 주어졌을 때 어떤 파티션으로 보낼지는 Key로 나누지만 없을 경우 라운드 로빈 방식으로 배정된다.

> **메시지가 같은 키를 가지게 하여 순서를 보장할 수 있게 만들 수 있다**

![](https://i.imgur.com/GPwlQXe.png)


- 참고자료
	- https://kafka.apache.org/intro
	- https://www.redhat.com/ko/topics/integration/what-is-apache-kafka
	- https://www.tibco.com/ko/reference-center/what-is-event-streaming
	- https://www.redhat.com/ko/topics/integration/what-is-apache-kafka