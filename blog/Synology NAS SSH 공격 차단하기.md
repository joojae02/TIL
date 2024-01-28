
시놀로지 나스를 사용하고 있는데
최근들어 SSH 접근 실패 로그들이 엄청나게 쌓이기 시작했다..

![](https://i.imgur.com/Iik6Yfe.png)

이런 SSH 접근을 막는 방법은
간단하게는 모든 SSH를 꺼주면 된다

### SSH 비활성화

![](https://i.imgur.com/HRVNRdl.png)

이렇게 제어판 > 터미널 및 SNMP에 
Telnet과 SSH이 활성화 되어있다면 SSH를 모두 비활성화 해주자

근데 이미 비활성화가 되어있는 경우가 있다
보통 이 경우엔
SFTP 혹은 rsync가 활성화되어 있을 수 있다

![](https://i.imgur.com/xW3td8m.png)

제어판 > 파일 서비스 > FTP 에서 SFTP를 비활성화해주자
똑같이 rsync 또한 비활성화

이렇게 한 뒤 보통 라우터 또한 열어놨을 것이니
제어판 > 외부 엑세스 > 라우터 구성 에서

> 암호화된 터미널 서비스 (암호화된 네트워크 rsync 및 SFTP 포함)

요걸 비활성화 해주자

이러면 SSH를 모두 종료할 수 있다..!!

### 근데 SSH 써야된다면..? 한국 IP 만 허용

사실 SSH를 쓰든 안쓰든 해놓으면 좋은 방법이다

제어판 > 보안 > 방화벽 에 방화벽 활성화를 해주자
![](https://i.imgur.com/jfkycYE.png)


후에 default 규칙 편집에 들어가 
방화벽 규칙 생성 클릭

![](https://i.imgur.com/d2rJ1g3.png)


위치를 대한민국 선택 후 확인을 눌러주자

그 다음 로컬 IP 허용을 위해

![](https://i.imgur.com/yLwsOlO.png)

보통 192.168.0.X 로 시작할텐데
본인 환경에 맞게 추가해주자
![](https://i.imgur.com/5PUdtYV.png)


![](https://i.imgur.com/eGGHXFK.png)

그리고 마지막으로 모두 거부를 해주자


![](https://i.imgur.com/yhYZZZH.png)

최종적으로 이런 순서대로 놓아주면 된다
규칙의 우선순위가 있어 마지막에 모두 거부를 넣어줘도 된다~

사실 이렇게 해도 공격 시도가 올 수도 있다
보통 이런 공격들은 중국, 러시아 ip로 오기 때문에 방화벽 설정을 마쳤다면 차단되지만

가끔 최종 ip를 한국으로 공격이 오는 경우가 있기 때문에...
나스 2차 인증을 꼭꼭 걸어서 사용하자~




