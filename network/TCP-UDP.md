# TCP UDP

## 인터넷 프로토콜 스택의 4계층

- 애플리케이션 계층 - HTTP, FTP
- 전송 계층 - TCP,UDP
- 인터넷 계층 - IP
- 네트워크 인터페이스 계층
<img src="https://velog.velcdn.com/images/suyyeon/post/f2a89aed-d04f-4afb-95e0-189c19a71ba9/image.png">


## TCP 패킷 정보

<img src= "https://velog.velcdn.com/images/suyyeon/post/d94d7ea2-041f-44ac-b4d9-3f99df98a74c/image.png">  

## TCP 특징
> 전송 제어 프로토콜(Transmission Control Protocol)  

- 연결지향 - TCP 3 way handshake(가상연결)
- 데이터 전달 보증
- 순서 보장
- 신뢰할 수 있는 프로토콜

### TCP 3 way handshake
<img src = "https://velog.velcdn.com/images/suyyeon/post/c2234268-94df-4518-9150-9781cd5f16c5/image.png">  

> Client > Server : TCP SYN
> Server > Client : TCP SYN
> ACKClient > Server : TCP ACK  

- SYN = 'synchronize sequence numbers' 
- ACK = 'acknowledgment'   

연결 과정
- 클라이언트가 서버에 SYN 패킷 전송
    - 이떄 클라이언트는 SYN/ACK응답을 기다리는 SYN_SENT 상태
- 서버는 SYN 요청 받고 수락 의미의 ACK, SYN flag 의 패킷 전송
    - 클라이언트의 응답을 기다리는 SYN_RECEIVED 상태
- 클라이언트는 서버에 ACK를 보내고 이후는 연결이 이루어짐
    - 이때 서버상태가 ESTABLISHED 상태

- 신뢰성 있는 연결을 맺어줌

### 데이터 전달 보증

<img src = "https://velog.velcdn.com/images/suyyeon/post/31831bf8-dd65-4e4a-867f-39ad725e13f3/image.png">  

### 순서 보장

<img src = "https://velog.velcdn.com/images/suyyeon/post/c2dccd94-ce76-4c42-8928-20fda262c783/image.png">    


## UDP 특징
> 사용자 데이터그램 프로토콜(User Datagram Protocol)
- 하얀 도화지에 비유(기능이 거의 없음)
- 연결지향 - TCP 3 way handshake X
- 데이터 전달 보증 X
- 순서 보장 X
- 데이터 전달 및 순서가 보장되지 않지만, 단순하고 빠름
 
정리
- IP와 거의 같다. +PORT +체크섬 정도만 추가
- 애플리케이션에서 추가 작업 필요

------------
