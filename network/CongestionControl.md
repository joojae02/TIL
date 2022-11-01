A와 B가 같은 라우터를 거칠때 먼저 A가 큐에 쌓이게 된다면  
B는 딜레이가 걸림 이를 해결하기 위해 congestion  

네트워크에 패킷로스가 나는거 ㄹ어케 확인하는가  
- timeout 발생
- 중복된 ack가 발생
이렇게 된다면 보내는 데이터량 조절  

Host A에서 B로 전송  
- Host B에서 feedback (End-to-end congestion control)
- 라우터에서 feedback (Network-assisted congestion control)  
바람적인 건 전자  


## TCP congestion control
> 보내는 양을 증가해보고 전송되는지 확인 안된다면 낮추는 방식  
`LastByteSent - LastByteAcked <= min(cwnd, rwnd)`  

- slow start 
- congestion avoidance
- fast recovery

### slow start
> 더블링해서 전송

- 첫번째 로스가 날때까지 더블링

### congestion avoidance
> 어느정도 더블링 후 1 씩증가 시키자
로스난 값의 절반부턴 slow start는 하지말자  
- 1 -> 2 -> 4 -> 6 -> 7 ~  
로스 나면 1로 떨어짐  
이럼 품질이 떨어짐

### fast recovery
> 로스가 나면 그 절반부터 3씩 증가 시켜서 보내자
- 왜 3인가
    - TCP는 loss가 나면 ack가 안오거나 duplicate ack가 오면 loss인가 확인
    - Reno면 Duplicate이 3개 나면 fast recovery
    - timeout 즉 ack가 안오면 1부터  

## TCP Fairness
> 두 연결에서 패킷을 보낼떄 우선순위를 정하지 않는다
- 왜 공정해야하는가
    - 어차피 보낼수 있는 양은 정해져 있음
    - 하나가 더 많이 보내려 해도 loss가 발생함
    - 어차피 같이 보내지게 됨  

## ECN Explicit Congestion Notification
network-assisted congestion control  
- ECN bit가 IP에 있고
- 이를 B로 ECN Echo로 ack

