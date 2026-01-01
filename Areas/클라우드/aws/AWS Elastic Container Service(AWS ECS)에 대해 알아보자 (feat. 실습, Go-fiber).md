aws를 사용해본 사람이라면 대부분 들어봤을 서비스이다.

어떤 구조로 되어있고 어떻게 사용하는지

# AWS Elastic Container Service

> Amazon Elastic Container Service(Amazon ECS)는 컨테이너 애플리케이션을 쉽게 배포, 관리 및 확대할 수 있도록 도와주는 완전 관리형 컨테이너 오케스트레이션 서비스입니다.

AWS 공식 문서에서 설명하는 ECS이다.

여기서 오케스트레이션이란
- 컨테이너의 배포,관리,확장,네트워킹을 자동화 해주는 것을 말한다.

간단하게 말하면 ECS는 컨테이너 딴으로 서비스를 배포, 관리, 확장할 수 있는 서비스이다.
기존 EC2, EB 등에서 프로젝트를 단순 빌드, 배포하였다면
ECS로 Docker 컨테이너를 기반으로 쉽게 배포, 운영이 가능해진다.
- [Docker](https://joojae.com/docker/) 이전에 작성한 포스트이다

![](https://i.imgur.com/BOjwA3W.png)

우리가 개별로 컨테이너들을 관리할 필요 없이 ECS에서 컨테이너들의 집합을 관리해준다.

## ECS 구성

우선 ECS를 구성하는 4가지 요소에 대해 알아야한다.

- Task Definition(테스크 정의)
	- 컨테이너를 실행할 때 사용하는 설정이다.
	- 예) Image, CPU, Memory, Runtime 등등
- Task(테스크)
	- Task Definition으로 실행된 컨테이너이다.
- Cluster(클러스터)
	- Task가 배포되는 환경들이 논리적으로 그룹화되는 단위
	- 클러스터 밑에 서비스, 테스크, 인프라 등이 존재한다.
- Service(서비스)
	- Task 개수, Auto Scaling 정책 등 LifeCycle 설정

![](https://i.imgur.com/BCW0eFn.png)

![](https://i.imgur.com/Jbt5845.png)

대충 이런 구성이된다.

## AWS Elastic Container Registry(AWS ECR)

ECS를 볼 때 빼놓을 수 없는 ECR이라는 서비스가 존재한다.

ECS에서 사용할 Container Image 레지스트리이다.

![](https://i.imgur.com/hVNrZUA.png)

그냥 이미지 저장소이다.

외부 저장소를 사용하게 되면 보안상 정책과 설정을 별도로 해줘야해 불편한 점들이 존재한다.
그래서 해당 ECR을 사용한다면. IAM에서 ECR 관련 정책을 넣어주기만 하면 편하게 사용이 가능하다.

## 한번 해보자.

보통은 Code Pipeline 등을 이용한 CI/CD를 구축해 사용하는것이 보통이지만
해당 내용은 다음 포스트들에서 작성해보겠다.

이번엔

- Dockerfile 작성
- Docker Image Build
- ECR upload
- ECS
	- Task Definition 작성
	- Cluster 생성 - Fargate
	- Service 생성
	- Task 생성

순서로 진행할 예정이다.

## Dockerfile

어떤 언어, 프레임워크든 상관 없지만 

지금은 go fiber로 hello world 작성해보겠다

[joojae/go-fiber](https://joojae.com/go-fiber-install/) 자세한 설명은 해당 포스트를 참고하자

```
$ go mod init go-fiber
$ go get github.com/gofiber/fiber/v3
```

```go
package main


import (
	"github.com/gofiber/fiber/v3"
)

func main() {
	app := fiber.New()
	app.Get("/", func(c fiber.Ctx) error {
		return c.SendString("Hello, World!")
	})
	
	app.Listen(":3000")
}
```

```Dockerfile
FROM golang:1.21.6-alpine

WORKDIR /app

COPY go.mod ./
COPY go.sum ./

RUN go mod download

COPY . .

RUN go build -o main .

CMD ["./main"]
```

```shell
$ docker build -t go-fiber:latest .
// local test 용
$ docker build -t go-fiber:latest --platform linux/amd64 .
// 요건 ECR로 올릴 이미지 현재 mac m1기준이라 linux로 설정해줘야함
```


```
$ docker image ls
$ docker run -p 3000:3000 go-fiber
    _______ __             
   / ____(_) /_  ___  _____
  / /_  / / __ \/ _ \/ ___/
 / __/ / / /_/ /  __/ /    
/_/   /_/_.___/\___/_/          v3.0.0-beta.3
--------------------------------------------------
INFO Server started on:         http://127.0.0.1:3000 (bound on host 0.0.0.0 and port 3000)
INFO Total handlers count:      1
INFO Prefork:                   Disabled
INFO PID:                       1
INFO Total process count:       1
```


## ECR

![](https://i.imgur.com/mOsPjva.png)

요렇게 만들어주면~
안에 푸시명령을 확인하자ㅏ
![](https://i.imgur.com/JD5R5eM.png)
\
나와있는 순서대로 명령어를 실행하자~

```
$ aws ecr get-login-password --region ap-northeast-2 | docker login --username AWS --password-stdin {account_id}.dkr.ecr.ap-northeast-2.amazonaws.com

$ docker build -t ecs-test --platform linux/amd64 .

$ docker tag ecs-test:latest {account_id}.dkr.ecr.ap-northeast-2.amazonaws.com/ecs-test:latest

$ docker push {account_id}.dkr.ecr.ap-northeast-2.amazonaws.com/ecs-test:latest
```


![](https://i.imgur.com/i7doiQO.png)


> ~~흠.. 그냥 nginx 같은걸로 할껄 후회가...~~

## ECS - Task Definition

콘솔에서 만드는 법과 JSON으로 하는법이 있는데
콘솔로 일단 해보겠습니다.

![](https://i.imgur.com/x17t6s8.png)


![](https://i.imgur.com/Tc6isWa.png)

이미지 URI 에서는 ECR image latest URI를 넣어주자

그리고 나머지 설정을 뭐.. 해도 되고.. 일단 패스

## Cluster 생성

![](https://i.imgur.com/voWHUPy.png)

Fargate로 테스트해볼거라 설정하고 넘어간다

![](https://i.imgur.com/ufSTuQ4.png)


## Service 생성


![](https://i.imgur.com/fPbnkS1.png)

![](https://i.imgur.com/7j19t4G.png)

서비스에서 Task Definition 이름과 버전을 넣어준다

## 결과~

![](https://i.imgur.com/YUbAWkD.png)

이런식으로 테스크가 실행되었다면~

해당 테스크 안에 들어가

![](https://i.imgur.com/YQs7nWA.png)

퍼블릭 IP를 가져와

`http://{퍼블릭 IP}:3000/`
으로 접속해주면~
![](https://i.imgur.com/nQ2uWOW.png)

성공~~~



### 참고
- https://aws.amazon.com/ko/ecs/
- https://docs.aws.amazon.com/ko_kr/AmazonECS/latest/developerguide/Welcome.html
- https://blog.kyobodts.co.kr/2022/03/25/aws-ecs%EB%9E%80/
- https://tech.cloud.nongshim.co.kr/2021/08/30/%EC%86%8C%EA%B0%9C-amazon-ecs%EB%9E%80/