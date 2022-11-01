# Network Layer

- Forwarding
- Routing

## Data plane
> Forwarding
- 어디로 보낼지
    - 패킷의 헤더를 보고 판단

## Control plane
> Routing  
- 라우터끼리 통신도 함  

Traditional Approach
- routing algorithm 을 이용 라우터 끼리 통신 후
- forwarding table을 만듦  

SDN Approach
- 중간 Controller를 사용  

## Switching

## Scheduling mechanisms
> First in First out

### priority
> FIFO scheduling
> 우선순위로 전송
- 우선순위가 낮은건 packet loss가 날수도 있음
- 시간 임계값을 정해서 priority를 증가시켜 전송하기

### Round Robin (RR)
> 돌아가면서 보냄  

Weighted Fair Queuing (WFQ)
- generalized Round Robin

## IP 주소 체계
- version number
- header length
- Datagram length - 전체적인 길이
- 16-bit Identifier - 큰단위에서 쪼개질때 재조합을 위한
- Flags - 상동
- 13~
- Time-to-live - 라우터를 갈때마ㅏㄷ 1씩 감소
- Upper-layer protocol - 어플리케이션에서 transport layer로 전송 TCP 헤더가 붙고 network 에서 IP 헤더가 붙음 mac -> ip -> TCP -> Data 

### IP fragmentation, reassembly


### IP addressing
- IP address 32-bit identifier
- IP 주소에서 네트워크 주소, 호스트 주소를 뽑아야함 - 서브넷
    - 이를 이용해 데이터 전송
    - 네트워크 주소를 보고 라우팅




