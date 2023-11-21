![](https://i.imgur.com/51F8UZx.png)

# Docker란?
> Go언어로 작성된 리눅스 컨테이너 기반으로하는 오픈소스 가상화 플랫폼  

- 컨테이너 환경에서 독립적으로 애플리케이션을 실행할 수 있도록 컨테이너를 만들고 관리하는 것을 도와주는 도구

## 컨테이너
-  가상화 기술 중 하나로 대표적으로 LXC(Linux Container)가 있음
- OS레벨의 가상화로 프로세스를 격리시켜 동작하는 방식

### Docker 가상화
- Docker 엔진 위 바로 Application을 위한 바이너리만
- Host의 커널 공유 성능 높아짐
- 멀티 OS 불가

## Docker 쓰는 이유
- 성능향상
- 이식성
- Scale out 유연성

## Docker Image
>  컨테이너를 실행할 수 있는 실행파일, 설정값들을 담고 있는 것  

<img src = 'https://t1.daumcdn.net/cfile/tistory/991ACC3C5B8D445C0C'>

### 레이어??
> 레이어란 **기존 이미지에 추가적인 파일이 필요할 때** 다시 다운로드받는 방법이 아닌 해당 파일을 추가하기 위한 개념

`ubuntu 이미지`가 `A + B + C`의 집합이라면, `ubuntu 이미지를 베이스로 만든 nginx 이미지`는 `A + B + C + nginx`가 된다
# Docker File
## FROM 
> 베이스 이미지 설정
## RUN 
> 컨테이너 내부에서 실행할 명령어

## COPY
> 컨테이너 내부에 파일 복사

## WORKDIR
> 명령어 실행할 디렉토리

## CMD
> 컨테이너가 실행될 때 실행할 명령어

## EXPOSE
> 노출할 컨테이너 포트

# Docker compose
> 단일 서버에서 여러개의 컨테이너를 하나의 서비스로 정의해 컨테이너의 묶음으로 관리할 수 있는 작업 환경을 제공하는 관리 도구

- 서비스 시작, 중지 및 재구축
- 실행 중인 서비스 상태 보기
- 실행 중인 서비스의 로그 출력 스트리밍
- 서비스에서 일회성 명령 실행

![](https://i.imgur.com/lTwmJZm.png)

## 어떻게 사용하는가
1. 각각의 컨테이너의 Dockerfile를 작성
2. docker-compose.yml를 작성
3. 각각 독립된 컨테이너의 실행 정의
4. `docker-compose up` 실행하여 컨테이너 개시
## docker-compose.yml?
> yaml으로 Docker 컨테이너에 관한 실행 옵션 등을 기재한 파일


# Docker 허브
> 공용 Docker 이미지 저장소

![](https://i.imgur.com/KjBpUor.png)

# 도커의 한계

Docker는 **단일 컨테이너 관리**에 적합하다

수백 개로 세분화된 컨테이너와 컨테이너화된 앱을 점점 더 많이 사용하기 시작하면 **관리와 오케스트레이션이 매우 어려워질 수 있다.**

결국 모든 컨테이너 전체에서 네트워킹, 보안, 텔레메트리와 같은 서비스를 제공하기 위해서는 **컨테이너를 그룹화**를 해야한다. =>`쿠버네티스` 사용