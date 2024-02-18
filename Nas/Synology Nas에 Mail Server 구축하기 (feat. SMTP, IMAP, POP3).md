메일 서버 구축하기 전에 이전 포스트인 [SMTP, IMAP, POP3에 대해 알아보자](https://joojae.com/about-smtp-imap-pop3/) 참고;

## 도메인 구매 및 설정

원하는 도메인을 구입 후 DNS 설정을 해준다

![](https://i.imgur.com/Gp9vfmR.png)

- A 타입에 호스트 mail 값/위치에 ip 주소
- TXT 타입에 @, "v=spf1 ip4:(서버 IP 주소) -all"
- MX 타입에 @, mail.(도메인).

## Synology MailPlus Server Install (MTA Setup)

![](https://i.imgur.com/6g5nV4g.png)

현재 Synology NAS 720+ 를 사용하고 있기 때문에
Synology Mail Server 대신 Synology MailPlus Server를 설치해준다

후 설치가 완료되면

joojae.com (도메인)
mail.joojae.com (호스트)

이런식으로 각자의 도메인에 맞게 넣고 설치해주면 된다.
이미 설정을 완료한 상태라 별도의 스크린샷은 없음.. 

여튼 후에 도메인에 사용자를 들어가 사용할 사용자만 활성화 해주면 된다

![](https://i.imgur.com/Qz2Of1a.png)


![](https://i.imgur.com/kwKpZFn.png)

메일 배달에 SMTP 인증을 활성화 해주고
호스트 이름이 mail.도메인 으로 되어있는지 확인해준다

![](https://i.imgur.com/GDy5csS.png)
SMTP 활성화되어 있는지 확인해주고
포트도 개인 설정에 맞게 변경해준다
당근 해당 포트들도 열어줘야한다

![](https://i.imgur.com/mTAi9rB.png)

이렇게 POP3, IMAP, 암호화 모두 활성화 해줬는데
POP3, IMAP은 개인 선택이라 각자 원하는대로 설정해주면 된다.
[SMTP, IMAP, POP3에 대해 알아보자](https://joojae.com/about-smtp-imap-pop3/)

## MAC Mail에서 연결하기

![](https://i.imgur.com/9ATQsg6.png)
![](https://i.imgur.com/qBylDJi.png)
![](https://i.imgur.com/BWlHPm2.png)
이런식으로 수신, 발신 서버 모두 이전에 설정한 호스트를 설정해놓으면 된다.
IMAP 대신 POP3으로 사용해도 무방하다.

![](https://i.imgur.com/hh3Xt6p.png)

이런식으로 연결이 되었다면 성공이다ㅏㅏ