# HTTP 메소드 활용
- 클라이언트에서 서버로 데이터 전송

## 클라이언트에서 서버로 데이터 전송
> 전달 방식은 크게 2가지   
- 쿼리 파라미터로 데이터 전송
    - GET
    - 주로 정렬 필터
- 메세지 바디로 데이터 전송
    - POST, PUT, PATCH
    - 회원가입, 상품 주문, 리소스 등록, 변경

## 클라이언트에서 서버로 데이터 전송
> 4가지 상황  

- 정적 데이터 조회
    - 이미지, 정적 텍스트 문서
- 동적 데이터 조회
    - 주로 검색, 게시판 목록에서 정렬 필터
- HTML Form을 통한 데이터 전송
    - 회원가입, 상품 주문, 데이터 변경
- HTTP API를 통한 데이터 전송
    - 회원가입, 상품 주문, 데이터 변경
    - 서버에서 서버, 앱클라이언트, 웹 클라이언트

## 정적 데이터 조회
> 쿼리 파라미터 미사용

<img src = "https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FUxsJo%2FbtrDwPGgZ0C%2FBAJwB5Mf8CgRFFzJPc96YK%2Fimg.png">

정리  

- 이미지, 정적 텍스트 문서
- 조회는 GET 사용
- 정적 데이터는 일반적으로 쿼리 파라미터 없이 리소스 경로로 단순하게 조회 가능

## 동적 데이터 조회
> 쿼리 파라미터 사용

<img src = "https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FdaFgin%2FbtrDpPgJISx%2FchueuGwyHs4PEeU8Je7z40%2Fimg.png">  

정리  
- 주로 검색, 게시판 목록에서 정렬 필터(검색어)
-  조회 조건을 줄여주는 필터, 조회 결과를 정렬하는 정렬 조건에 주로 사용
- 조회는 GET 사용
- GET은 쿼리 파라미터 사용해서 데이터를 전달

## HTML Form 데이터 전송

### POST 전송 - 저장
- HTML Form 데이터를 읽어서 message-body 안에 key-value로 넣어 전송  
- 서버가 POST메세지를 받으면 저장
<img src="https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FA0rOC%2FbtrDpQfE71y%2FojXJafNPvQgWdYt3tf64Y0%2Fimg.png">

### GET 전송 - 저장
- get은 조회에서만!
<img src = "https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2Fzu75M%2FbtrDoTRgCCk%2FvIDIQBTpZkPMG8Nm1nHI41%2Fimg.png">

### GET 전송 - 조회
- HTML Form 데이터 읽어 HTTP 요청 메세지 생성
- 쿼리 파라미터에 key-value 로 데이터 넣음
- 서버가 GET을 받으면 데이터를 전송
<img src ="https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2Fzu75M%2FbtrDoTRgCCk%2FvIDIQBTpZkPMG8Nm1nHI41%2Fimg.png" >

### multipart/form-data
- 파일(binary data)를 보낼떄 사용하는 인코딩 타임  
- 웹 브라우저가 데이터를 나누어 message-body에 담아 전송 
<img src = "https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FeCIHuD%2FbtrDnjVS4EI%2FjbbiDAeVTm4CdalRysd1kK%2Fimg.png">


### 정리
- HTML Form submit시 POST 전송
    - 예) 회원 가입, 상품 주문, 데이터 변경
- Content-Type: application/x-www-form-urlencoded 사용
    - form의 내용을 메시지 바디를 통해서 전송(key=value, 쿼리 파라미터 형식)
    - 전송 데이터를 url encoding 처리
        - 예) abc김 -> abc%EA%B9%80
- HTML Form은 GET 전송도 가능
- Content-Type: multipart/form-data
    - 파일 업로드 같은 바이너리 데이터 전송시 사용
    - 다른 종류의 여러 파일과 폼의 내용 함께 전송 가능(그래서 이름이 multipart)
- 참고: HTML Form 전송은 GET, POST만 지원

## HTTP API를 통한 데이터 전송

<img src ="https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FlvBTC%2FbtrDwPNewNq%2FbLbdYH8ZnJRP8KKucfRvq1%2Fimg.png">

정리  
- 서버 to 서버
    - 백엔드 시스템 통신
- 앱 클라이언트
    - 아이폰, 안드로이드
- 웹 클라이언트
    - HTML에서 Form 전송 대신 자바 스크립트를 통한 통신에 사용(AJAX)
    - 예) React, VueJs 같은 웹 클라이언트와 API 통신
- POST, PUT, PATCH: 메시지 바디를 통해 데이터 전송
- GET: 조회, 쿼리 파라미터로 데이터 전달
- Content-Type: application/json을 주로 사용 (사실상 표준)
    - TEXT, XML, JSON 등등