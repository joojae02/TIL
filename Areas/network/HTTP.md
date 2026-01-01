# HTTP
> 모든것이 HTTP

- HTML, TEXT
- IMAGE, 음성, 영상, 파일
- JSON, XML
- 거의 모든 형태의 데이터 전송 가능
- 서버간도 HTTP 사용

## 기반 프로토콜
- TCP : HTTP/1.1, HTTP/2
- UDP : HTTP/3
- 현재 HTTP/1.1 주로 사용
    - HTTP/2, HTTP/3도 증가  

## HTTP 특징

- 클라이언트 서버 구조
- 무상태 프로토콜(stateless)
- HTTP 메세지
- 단순, 확장 가능

## 클라이언트 서버 구조
- Request Response 구조
- 클라이언트는 서버에 요청을 보내고 응답 대기
- 서버가 요청에 대한 결과를 응답
```
        요청 -> 
클라이언트          서버
             <- 응답
```     
## 무상태 프로토콜
> 스테이스리스(stateless)  
- 서버가 클라이언트 상태를 보존하지 않음
- 장점 : 서버 확장성 높음
- 단점 : 클라이언트가 추가 정보 전송

## Stateful, Stateless 차이
- 상태유지
    - 중간에 바뀌면 안됨
        - 결제하는 점원이 다른 점원으로 바뀌면 안됨
        - 서버 추가 어려움
- 무상태
    - 중간에 바뀌어도 됨
        - 결제하는 점원이 누구든 상관없음
        - 서버 추가가 편함
- 무상태는 응답 서버를 쉽게 바꿀수 있다. 
    - 서버 증가 무한히 가능!

## 한계
- 무상태로 할수 없는 경우 존재
- 무상태
    - 로그인이 필요없는 단순 서비스
- 상태유지
    - 로그인
        - 로그인한 사용자의 경우 로그인했다는 상태를 저장
        - 쿠키나 세션 사용
- 상태유지는 최소한으로 사용하는 것이 바람직

## 비연결성
- Http는 기본적으로 연결을 유지하지 않음
- 일반적으로 초단위 이하의 빠른 속도의 응답
    - 한시간동안 수천명이 서비스를 사용해도 서버에서 동시에 처리하는 요청은 수십개 이하
- 서버 자원 효율적 사용 가능

## 비연결성 한계
- TCP/IP 연결을 다시 맺어야함
    - 3 way handshake 시간 추가
- 웹 사이트 요청은 HTML 뿐 아닌 많은 자원 다운로드

## 비연결성 극복
- HTTP 지속 연결(Persistent Connections)로 해결
- HTTP/2, HTTP/3 에서 더욱 최적화

## HTTP 초기 
<img src = "https://velog.velcdn.com/images/suyyeon/post/bfdea0f7-0cc7-47ba-bf56-4093349592ba/image.png">  

## HTTP 지속 연결
<img src = "https://velog.velcdn.com/images/suyyeon/post/f2020b2a-5830-4267-b6c8-6844131cc0d5/image.png">  

## Stateless 기억하자!

- 같은 시간에 발생해 처리해야하는 대용량 트래픽
    - 선착순 이벤트

## HTTP 메세지
<img src = "https://velog.velcdn.com/images/suyyeon/post/23e06430-2c1f-45e0-ad81-edba8ccc687d/image.png">  

## HTTP 요청 메세지
<img src = "https://velog.velcdn.com/images/suyyeon/post/d7a78cb7-c2b2-4b64-ae63-b3ad19db3ad8/image.png">  

## 시작 라인
```
HTTP-message = start-line
 *( header-field CRLF )
 CRLF
 [ message-body ]
```
> 요청 메세지
- start-line = request-line / status-line
- request-line = method SP(공백) request-target SP HTTP-version CRLF(엔터)
- HTTP 메소드(GET:조회)
- 요청 대상 (/search?q=hello&hl=ko)
- HTTP Version
```
GET /search?q=hello&hl=ko HTTP/1.1
Host: www.google.com
```
> HTTP 메소드
- 종류: GET, POST, PUT, DELETE
- 서버가 수행해야 할 동작 지정
    - GET: 리소스 조회
    - POST: 요청 내역 처리

> 요청 대상
- absolute-path[?query](절대경로[?쿼리])
- 절대경로 = "/"로 시작하는 경로
> 응답 메세지
```
HTTP/1.1 200 OK
Content-Type: text/html;charset=UTF-8
Content-Length: 3423
<html>
 <body>...</body>
</html>
```

- HTTP 버전
- HTTP 상태 코드: 요청 성공, 실패를 나타냄
    - 200: 성공
    - 400: 클라이언트 요청 오류
    - 500: 서버 내부 오류
- 이유문구: 짧은 상태 코드 설명 글

## HTTP 헤더
```
GET /search?q=hello&hl=ko HTTP/1.1
Host: www.google.com
```
```
HTTP/1.1 200 OK
Content-Type: text/html;charset=UTF-8
Content-Length: 3423
<html>
 <body>...</body>
</html>
```
- HTTP 전송에 필요한 부가 정보




