
## 이미지 다운
synology container manger에서
`mysql`, `ghost` 를 받아와줍니다

![](https://i.imgur.com/IXzy1AT.png)

![](https://i.imgur.com/5Vy2UuE.png)


## 컨테이너 실행

### Mysql

#### 네트워크
brige로
#### 포트 설정
로컬 포트:컨테이너 포트를 설정합니다.
```
3306:3306
```
이런식으로 컨테이너 포트는 고정 로컬은 자유롭게 설정하시면 됩니다
#### 볼륨 생성
대충 이런 느낌으로 디렉토리를 만들어줍니다
```
/docker
`- ghost-db
    |- conf.d
    `- mysql
```
그리고 각자 만든 디렉토리에 매핑해줍니다
![](https://i.imgur.com/i2aKzgq.png)

#### 환경
미 `{}` 사이는 개인 설정에 맞게 넣어줍니다
```
MYSQL_ROOT_PASSWORD: {root_password}
MYSQL_DATABASE: {database_name}
MYSQL_USER: {user}
MYSQL_PASSWORD: {password}
```

그리고 생성


### Ghost
#### 네트워크
브릿지로
#### 포트 설정
로컬 포트:컨테이너 포트를 설정합니다.
```
2368:2368
```
#### 볼륨 설정
이런식으로 만들어주고요

```
/docker
`- ghost-blog
    `- content
```

`/var/lib/ghost/content` 여기로 매핑해줍니다

![](https://i.imgur.com/5x1NDiZ.png)

#### 환경
```
database__client: mysql
database__connection__host: {database 주소}
database__connection__port: {database 포트 번호}
database__connection__user: {MYSQL_USER 의 값}
database__connection__password: {MYSQL_PASSWORD 의 값}
database__connection__database: {MYSQL_DATABASE 의 값}
url: {Ghost5 의 주소(https:~.~.~)}
```

후에 생성

그리고 이 주소로 들어가면 정상적으로 들어가집니다!
`{NAS_주소}:2368`


### 혹시 역방향 프록시를 걸어 놓으셨다면.. 안됩니다

제어판 > 로그인포탈 > 고급 > 역방향프록시 에 들어가줍니다

![](https://i.imgur.com/8ptkXGb.png)

그리고 생성을 눌러서 넣어줍시다

![](https://i.imgur.com/WHE2s8e.png)

역방향 프록시 세팅할 때 아래와 같이 사용자 지정 머리글을 넣어주시면
![](https://i.imgur.com/d8JuGFH.png)

외부에서 서브도메인을 이용해 접속할때 제한이 걸리는 부분들 
- DNS접속시 터미널이 열리지 않는다
- 소켓이 닫혔다
- 외부에서 ESPHome compile 하기
들도 해결 가능합니다.


그다음
보안 > 인증서 > 인증서 생성

![](https://i.imgur.com/1xltNfE.png)

![](https://i.imgur.com/KGtXA8M.png)

![](https://i.imgur.com/4z87BRV.png)

전 시놀로지 주소라고 한글로 써놨는데
개인 시놀로지 주소 이름.synology.me 이런거 넣어주시면됩니다
아까 역방향 프록시 해놨던 주소랑 동일해야합니다

그리고 완료 하시고
설정에서 
![](https://i.imgur.com/fkkbhld.png)
이런식으로 바꿔주셔야 됩니다

이러면 끝.

![](https://i.imgur.com/nqxy6i6.png)


잘 나옵니다

후에 
`주소/ghost`에 들어가서 설정해주시면 됩니다



### 참고
- https://svrforum.com/svr/130908?ref=yomojomo
- https://ymjm.synology.me/install-ghost-5-to-synology-docker/
- https://dev.to/lrth06/deploy-a-ghost-blog-with-docker-j5m?ref=yomojomo