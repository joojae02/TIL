
# Elastic Beanstalk 이란??

Elastic Beanstalk는 간단하게 말하면
> AWS에서 제공하는 웹 애플리케이션 및 서비스를 간편하게 배포, 컨트롤해주는 서비스이다.

단순 코드 업로드로 오토스케일링, 로드밸런싱, 모니터링, 배포, ,등등의 기능을 제공해준다.

따라서 여러 복잡한 리소스들을 한번에 쉽게 관리, 제어가 가능하다.
- 중요한것은 추가 비용이 없다.
그냥 사용하는 리소스들에 대한 비용만 지불하면 된다.
그니까 ec2, rds, elb 이런 기본 비용만 내면 된다.

다만 지원하는 환경이 한정되어 있다.
그치만 대부분 지원함
- Go, Java, .NET, Node.js, PHP, Python 및 Ruby

또한 CLI 또한 존재한다.

![](https://i.imgur.com/6Gr4gQz.png)

그럼 만들어보면서 더 알아보자

# 직접해보자.

간단하게 콘솔에서 진행

![](https://i.imgur.com/aOyH4yJ.png)
## VPC 생성
VPC는

![](https://i.imgur.com/2JoCPkR.png)

간단하게만 만들어주자

## EC2 key-pair

ec2 콘솔창에서 키페어를 하나 만들어주자
![](https://i.imgur.com/5ImPubB.png)


## 애플리케이션 생성

### 환경 구성

![](https://i.imgur.com/cdurtvm.png)

기본적으로 웹서버 환경을 선택해준다.
이름은 자유롭게 설정해준다.

![](https://i.imgur.com/RN4ncdr.png)

플랫폼은
테스트로 파이선을 선택
- 다른 환경 선택해도 상관없다

개인적으로 이전 프로젝트에서는 코드 번들로 올렸지만
도커로 올리는것이 훨씬 좋아보인다.
- 도커로 할껄.. 
- 이미 다 올리고 알아버려서...

코드도 샘플로 일단 해준다.

![](https://i.imgur.com/faLhs0M.png)

사전 설정을 고가용성으로 해주면
로드밸런서, 오토스케일링이 추가된다.

### 서비스 엑세스

![](https://i.imgur.com/1jhKztw.png)
여기서
- 서비스 역할 이름
- EC2 키페어
- EC2 인스턴스 프로파일
3개를 선택해야하는데

- 서비스 역할 이름
- EC2 인스턴스 프로파일
요건 IAM Role이다.

> IAM 역할

Elastic Beanstalk Role
Elastic Beanstalk에 권한을 부여하는 것이다.
예를 들어
- 로그, 모니터링 조회
- ELB 생성, RDS 생성
이런 권한을 줄 수 있다.

EC2 인스턴스 프로파일
요건 EB내 인스턴스가 다른 서비스에 접근하는 권한들을 포함시켜야한다.
예를 들어
- S3에 저장
- RDS에 접근
뭐 등등

요런 권한을 주면 된다.

각자 맞게 추가해주자

## 네트워킹, 데이터베이스 및 태그 설정


![](https://i.imgur.com/3AELnFt.png)

처음 생성한 VPC를 선택

인스턴스는 public 으로 2개 선택해준다.
![](https://i.imgur.com/H3Q9dUb.png)
DB는 private으로 2개
아래 디비는 각자 맞게 설정한다.

> 그치만 일반적으로 EB 내에서 생성하는 경우는 거의 없다.

### 인스턴스 트래픽 및 크기 조정 구성

여기선 
![](https://i.imgur.com/JFjj29T.png)
오토스케일링 그룹 개수 선택

![](https://i.imgur.com/JinmZkh.png)
로드밸런서 유형 

![](https://i.imgur.com/LxISanP.png)
로그

정도만 각자 맞게 설정해주면 된다.

> 고가용성을 선택하는 경우 로드밸런서를 Public Subent에 두고, 인스턴스를 Private Subent에 둠으로써 외부 접근을 제한하도록 구성하는 것이 좋다.
### 업데이트, 모니터링 및 로깅 구성


![](https://i.imgur.com/rH08Awf.png)

배포쪽이 좀 중요하다.

- 한 번에 배포
![](https://i.imgur.com/CfbApvn.png)

- 롤링
![](https://i.imgur.com/7AcpaWT.png)

- 추가 배치를 활용한 롤링
![](https://i.imgur.com/XyFL5vI.png)

- 변경불가
![](https://i.imgur.com/YvbReQY.png)

- 트래픽 분할
변경 불가 방식과 비슷하지만
카나리 배포가 가능하다.

이후 구성 완료 해주면
![](https://i.imgur.com/MDUtS3m.png)

정상적으로 실행이 된다~

# 참고 자료
- https://docs.aws.amazon.com/ko_kr/elasticbeanstalk/latest/dg/Welcome.html
- https://tech.cloud.nongshim.co.kr/2021/11/01/%EC%86%8C%EA%B0%9C-aws-elastic-beanstalk%EB%9E%80/
- https://docs.aws.amazon.com/ko_kr/elasticbeanstalk/latest/dg/concepts.html
- https://docs.aws.amazon.com/ko_kr/elasticbeanstalk/latest/dg/concepts-webserver.html
- https://docs.aws.amazon.com/ko_kr/elasticbeanstalk/latest/dg/concepts-roles.html
- https://dingdingmin-back-end-developer.tistory.com/entry/Elastic-Beanstalk-%EC%A0%95%EB%B3%B5%ED%95%98%EA%B8%B0-1-%EC%BD%98%EC%86%94-1%ED%8E%98%EC%9D%B4%EC%A7%80
- https://www.youtube.com/watch?v=uiM1xzOX8Qg
- https://docs.aws.amazon.com/ko_kr/elasticbeanstalk/latest/dg/eb-cli3.html
- https://dev.classmethod.jp/articles/deploy-express-application-to-elastic-beanstalk/
- https://webmobilez.com/awsmaterial/elastic-beanstalk-deployment/
