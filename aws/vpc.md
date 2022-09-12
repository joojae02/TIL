# AWS VPC

## VPC란??
> VPC(Virtual Private Cloud)는 사용자가 정의하는 가상의 네트워크이다  
- vpc로 네트워크를 구분해 설정 가능
- vpc 없이 인스턴스 생성시 시스템 복잡도 증가  


아래와 같이 vpc 적용해 네트워크 구분 가능!
<img src = 'https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FcZd3VV%2Fbtq4eKGt56L%2FdVWt2cbgpb15IkJUqLWiVk%2Fimg.png'>

## VPC
> VPC는 독립된 하나의 네트워크를 구성하기 위한 가장 큰 단위    

각 region에 종속되며 RFC1918이라는 사설 IP 대역에 맞추어 설계해야 한다  
> region이란 말그대로 실제 서버가 있는 위치를 말함  

사설 IP 대역  
- 10.0.0.0 ~ 10.255.255.255(10/8 prefix)
- 172.16.0.0 ~ 172.31.255.255(182.16/12 prefix)
- 192.168.0.0 ~ 192.168.255.255(192.168/16 prefix)  

perfix란 IP주소의 접두사이다  
- prefix는 Network를 판별하기 위한 Network ID

x/y prefix라 할때  
x는 0~255사이 숫자 y는 x의 길이(bit)를 나타낸다  
- 1번은 00001010~
- 2번은 0101100.0001~
- 3번은 11000000.10101000~   
이렇게가 앞에 고정으로 달리게 된다   

## Subnet(서브넷)
> VPC의 IP 주소를 나누어 리소스가 배치되는 물리적인 주소 범위  
이는 vpc를 나누어 놓은 것이기 때문에 VPC보다 대역폭이 낮다.  
하나의 AZ(Availability Zone)에 서브넷이 연결되어 region의 AZ를 확인하고 설정해야한다.  

서브넷은
- private
- public   
으로 나뉜다  
- 인터넷과 연결된 것이 public  
- 안된것이 private     

인터넷과 연결 여부로 구분하는 것은 보안의 이유 때문이다  
public은 인바운드 아웃바운드 트래픽을 주고 받을수 있지만  
private은 그렇지 않다   
  
   

<img src="https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2F6e309%2Fbtq4cNKOlyj%2FptMqOasi1g1t0DKRV8JIEK%2Fimg.png">

   
## Router(라우터)
> VPC 안에서 발생한 네트워크 요청을 처리하기 위해 어디로 트래픽을 전송해야 하는지 알려주는 표지판 역할  
  
- 서브넷은 네트워크 트래픽 전달 규칙에 해당하는 라우팅 테이블을 가지고 있다  
- 또한 요청이 발생하면 가장 먼저 라우터로 트래픽을 전송한다  

일반적으로 VPC 내부 네트워크에 해당하는 주소는 local로 향하도록 한다  

<img src = 'https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FdesaOh%2Fbtq4dMxY76n%2FJt4C5umce4a59mKUfoIzeK%2Fimg.png'>  
  
## Internet Gateway(igw, 인터넷 게이트웨이)
> VPC 리소스와 인터넷 간 통신을 활성화하기 위해 VPC에 연결하는 게이트웨이  

public subnet만 외부와 통신해야 하므로 public subnet의 라우팅 테이블에만 인터넷 게이트웨이로 향하는 규칙을 포함한다  
<img src = 'https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FbazdRh%2Fbtq4ejhZXir%2FJSixVUkarIcZ68hzfYiiQK%2Fimg.png'>  

## NAT Gateway(NAT 게이트웨이)
> private subnet이 인터넷 간 통신을 위해 필요한 게이트웨이  

private subnet에서 직접적으로 통신하는 것은 불가능   
따라서 트래픽을 public subnet에 속한 인스턴스에 전송해서 인터넷과 통신   

- 네트워크 요청이 VPC 내부의 주소를 목적지로 하는 것이 아니라면 public subnet에 존재하는 NAT로 트래픽을 전송
- NAT는 public subnet의 라우팅 규칙에 따라 처리함으로써 private subnet이 인터넷과 통신

<img src= 'https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FLEKCb%2Fbtq4f9M6s6v%2FOh1stJ4lyLrVGwXzkF6d80%2Fimg.png'>  
  
## VPC Endpoint
> 인터넷 게이트웨이나 NAT 게이트웨이와 같은 다른 게이트웨이 없이 AWS 서비스와 연결하여 통신할 수 있는 private connection을 제공하는 서비스  

Private link를 통해 AWS 서비스와 연결함으로써 데이터를 인터넷에 노출하지 않고 바로 접근할 수 있다  




