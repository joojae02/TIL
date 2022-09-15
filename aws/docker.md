# Docker
Docker란 Go언어로 작성된 리눅스 컨테이너 기반으로하는 오픈소스 가상화 플랫폼  

## 컨테이너
-  가상화 기술 중 하나로 대표적으로 LXC(Linux Container)가 있음
- OS레벨의 가상화로 프로세스를 격리시켜 동작하는 방식

## VM 가상화 Docker 가상화

<img src = 'https://t1.daumcdn.net/cfile/tistory/9934023E5B8D2CCF15'>  

### VM 가상화
- Host OS 위에 Hypervisor 위 gest os
- 가상화된 하드웨어 위에 OS가 올라가는 형태로 거의 완벽하게 Host와 분리
- OS위 OS라 느림
- 높은 격리 레벨 보안 유리
- 멀티 OS 가능
### Docker 가상화
- Docker 엔진 위 바로 Application을 위한 바이너리만
- Host의 커널 공유 성능 높아짐
- 멀티 OS 불가

## Docker 쓰는 이유
- 성능향상
- 이식성
- Scale out 유연성

## Docker Image
컨테이너를 실행할 수 있는 실행파일, 설정값들을 담고 있는 것  

<img src = 'https://t1.daumcdn.net/cfile/tistory/991ACC3C5B8D445C0C'>

# Docker File
## FROM 
- 기반이 되는 이미지 레이어

<이미지 이름>:<태그> 형식으로 작성 

ex) ubuntu:14.04

## MAINTAINER 

- 메인테이너 정보


RUN 

도커이미지가 생성되기 전에 수행할 쉘 명령어



## VOLUME 

- VOLUME은 디렉터리의 내용을 컨테이너에 저장하지 않고 호스트에 저장하도록 설정

- 데이터 볼륨을 호스트의 특정 디렉터리와 연결하려면 docker run 명령에서 -v 옵션을 사

ex) -v /root/data:/data



## CMD

- 컨테이너가 시작되었을 때 실행할 실행 파일

- 해당 명령어는 DockerFile내 1회만 쓸 수 있음



## WORKDIR  

- CMD에서 설정한 실행 파일이 실행될 디렉터리



## XPOSE 

- 호스트와 연결할 포트 번호

## image 만들기
```
docker build -t [만들고싶은 이미지 이름]
```