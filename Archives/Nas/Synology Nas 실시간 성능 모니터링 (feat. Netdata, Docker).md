
## Netdata란??

> Netdata는 오픈소스 모니터링 시스템 중 가장 유명한 도구이다.

Netdata는 CPU 사용량, 디스크 활동, 대역폭 사용량, 웹 사이트 방문 등과 같은 실시간 메트릭을 수집 한 다음 해석하기 쉬운 실시간 차트로 표시하도록 설계된 오픈 소스 도구이다.

![](https://private-user-images.githubusercontent.com/2662304/253744683-af4caa23-19be-46ef-9779-8fdad8d99d2a.gif?jwt=eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJnaXRodWIuY29tIiwiYXVkIjoicmF3LmdpdGh1YnVzZXJjb250ZW50LmNvbSIsImtleSI6ImtleTUiLCJleHAiOjE3MDUwNzc0NTQsIm5iZiI6MTcwNTA3NzE1NCwicGF0aCI6Ii8yNjYyMzA0LzI1Mzc0NDY4My1hZjRjYWEyMy0xOWJlLTQ2ZWYtOTc3OS04ZmRhZDhkOTlkMmEuZ2lmP1gtQW16LUFsZ29yaXRobT1BV1M0LUhNQUMtU0hBMjU2JlgtQW16LUNyZWRlbnRpYWw9QUtJQVZDT0RZTFNBNTNQUUs0WkElMkYyMDI0MDExMiUyRnVzLWVhc3QtMSUyRnMzJTJGYXdzNF9yZXF1ZXN0JlgtQW16LURhdGU9MjAyNDAxMTJUMTYzMjM0WiZYLUFtei1FeHBpcmVzPTMwMCZYLUFtei1TaWduYXR1cmU9NWVkOTcwZjZjZWNjOTc0ZTcwZWFkOWU0YWJmOGI3MDIzNzVkNGNlYmZjMjkyMjlmMWZiNDRkODlkODU5NTVjMiZYLUFtei1TaWduZWRIZWFkZXJzPWhvc3QmYWN0b3JfaWQ9MCZrZXlfaWQ9MCZyZXBvX2lkPTAifQ.6XVRZbcwMSpzNqFiqE6hdEChcIL3XYGNRXQUdFmG384)

실시간 모니터링을 생각하면 Prometheus와 Grafana를 사용하는 경우도 많이 있는데
Netdata는 즉시 사용 가능한 도구이다.
Prometheus와 Grafana 같은 경우는 자체 모니터링 시스템을 구축하기 위한 도구다.

쉽게 말해 그냥 한번에 쉽게 쓸꺼면 Netdata를
자체 스택에 최적화 된 모니터링 시스템을 구축해야한다면 시계열 데이터베이스인 Prometheus와 시각화 도구인 Grafana를 쓰는게 적합하다 생각한다.

서버가 여러대면 Netdata Cloud를 써도 되고 Zabbix를 쓰는것도 좋은 방법인거 같다.


## 설치

우선 사용하는 시놀로지 패키지들에 대한 설명은 스킵하고 진행하겠다

### Netdata 이미지 다운로드
어디서 다운받아도 되지만 쉽게 컨테이너 매니저에서 검색해 다운 받아주자
![](https://i.imgur.com/bqacXcH.png)

netdata 검색후 그냥 최신껄로 받아주기
![](https://i.imgur.com/gIRUd8i.png)

### 디렉토리 생성

File Station 에서 netdata 디렉토리를 생성하고
하위에 cache, config, data를 각각 만들어주자

![](https://i.imgur.com/Uqf2msr.png)

다음은 만든 netdata의 속성에 들어가준다
![](https://i.imgur.com/cwMMOYl.png)

후에 권한 > Everyone > 편집 에 들어간다

![](https://i.imgur.com/mhpPOqP.png)

읽기, 쓰기에 모두 체크해주고 완료

![](https://i.imgur.com/ghd9obi.png)

다음 이 폴더, 하위 폴더 및 파일에 적용에 체크해주고 저장


### 컨테이너 실행

그 다음 컨테이너를 실행해줘야 되는데

```
docker run -d --name=netdata \
  --pid=host \
  --network=host \
  -v netdataconfig:/etc/netdata \
  -v netdatalib:/var/lib/netdata \
  -v netdatacache:/var/cache/netdata \
  -v /etc/passwd:/host/etc/passwd:ro \
  -v /etc/group:/host/etc/group:ro \
  -v /etc/localtime:/etc/localtime:ro \
  -v /proc:/host/proc:ro \
  -v /sys:/host/sys:ro \
  -v /etc/os-release:/host/etc/os-release:ro \
  -v /var/log:/host/var/log:ro \
  -v /var/run/docker.sock:/var/run/docker.sock:ro \
  --restart unless-stopped \
  --cap-add SYS_PTRACE \
  --cap-add SYS_ADMIN \
  --security-opt apparmor=unconfined \
  netdata/netdata
```

해당 명령어가 공식문서에서 알려주는 명령어이다

근데 바꿔야하는 부분들, 빼도 되는 부분들이 있어서

```
docker run -d --name=netdata \
-p 19999:19999 \
-v /proc:/host/proc:ro \
-v /sys:/host/sys:ro \
-v /var/run/docker.sock:/var/run/docker.sock:ro \
-v /volume1/docker/netdata/config:/etc/netdata \
-v /volume1/docker/netdata/data:/var/lib/netdata \
-v /volume1/docker/netdata/cache:/var/cache/netdata \
-e PUID=1026 \
-e PGID=100 \
--cap-add SYS_PTRACE \
--security-opt apparmor=unconfined \
--restart always \
netdata/netdata
```

요걸 실행해준다

실행하는 방법은 ssh 접속해서 해도 되고 여러 방법으로 해도 되는데
젤 쉬운 방법은

제어판 > 작업 스케줄러 > 생성 > 예약된 작업 > 사용자 정의 스크립트

![](https://i.imgur.com/OKnxdRk.png)
![](https://i.imgur.com/4gOX8gJ.png)

![](https://i.imgur.com/RZxhuQA.png)

![](https://i.imgur.com/R9xX0AE.png)

이렇게 넣고 실행해주면 되는데

```
-e PUID=1026 \
-e PGID=100 \
```

이게 다른 경우가 있다

이건 위 작업스케줄러에서 똑같이 만든다음
실행 명령에 `id` 만 적어서 실행해주면 email로 해당 정보가 적혀서 온다

이제 실행을 눌러서 비번 치고 실행해준다

![](https://i.imgur.com/4vpIqdc.png)

그럼 이렇게 실행이 된다ㅏ

그리고
라우터 설정에서 19999 열어주고

`http://개인주소:19999/`
로 들어가 정상적으로 나오면 성공이다

뭐 역프록시 같은거 걸었으면 각자 맞게 설정해주자

그럼
![](https://i.imgur.com/QDrHlIZ.png)

이래저래 성공~

근데 따라했는데 안된다면...
밑 자료들 보면서.... 
## 참고자료
- https://learn.netdata.cloud/docs/installing/docker
- https://learn.netdata.cloud/docs/architecture
- https://github.com/netdata/netdata
- https://github.com/netdata/netdata?tab=readme-ov-file#getting-started
- https://mariushosting.com/how-to-install-netdata-on-your-synology-nas/
- https://sonhc.tistory.com/771
