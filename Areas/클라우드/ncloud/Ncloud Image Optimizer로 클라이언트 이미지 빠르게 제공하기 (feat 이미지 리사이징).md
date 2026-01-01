
버킷에 담긴 이미지를 클라이언트로 뿌릴때 
특정 크기로 리사이징 해서 보내고 싶다면????

# 이미지 리사이징

프로젝트를 진행 중 특정 사진을 보여줄 때 굳이 원본 품질, 사이즈의 이미지를 보여줄 필요가 없는 경우들이 생김

이 경우 이미지를 리사이징 하는 등의 작업으로 이미지를 불러오는 속도를 빠르게 최적화할 수 있다

총 3가지 정도를 생각해봤다
### 처음부터 리사이징 후 저장

우선 처음 클라이언트 혹은 백 서버에서 원본을 저장하는 것이 아닌 리사이징 후 저장하는 것이다

이 경우 범용성이 사라진다

이미지를 처음부터 작게 리사이징 해 올리는 경우
다른 원본 혹은 그보다 큰 사이즈가 필요한 경우를 커버할 수 없다...

물론 어느정도의 압축과 같은 작업은 해주는것이 좋다 생각한다ㅏ

### 원본, 썸네일 용 사진 모두 저장

이 경우 당연하게 여러 사이즈, 품질의 이미지를 저장하게 되면
S3와 같은 저장소의 공간을 2배, 3배로 차지하기 때문에 비효율적이라 생각했다

물론 장점으로 
- 속도, 성능
- 간편한 관리
가 있다
### 이미지 요청시 이미지 리사이징 후 반환
![](https://i.imgur.com/SH4sPdf.png)

마지막으로 생각한 것이 주로 사용하는 이미지 요청시 `param`에 원하는 사이즈, 품질을 넣어 요청하는 순간 이미지 리사이징 후 반환해 주는 방법이였다

이 경우
- 저장 공간 효율
- 업데이트 간편
하지만
- 처리가 지연될 경우 응답이 느려짐
- 위 모두 저장보다 복잡함

같은 장단점이 있다

추후 필요한 사이즈가 변동되는 경우가 있을것 같아
이미지 요청시 이미지 리사이징 후 반환을 선택했다


# 구현

구글에 검색해보면 주로 `Lambda`, `CloudFront` 를 사용해 구현한다
[Resizing Images with Amazon CloudFront & Lambda@Edge](https://aws.amazon.com/blogs/networking-and-content-delivery/resizing-images-with-amazon-cloudfront-lambdaedge-aws-cdn-blog/)

요 링크 참고

하지만.. 

## Ncloud Image Optimizer

![](https://i.imgur.com/jlJvffo.png)

![](https://i.imgur.com/F6ioxTG.png)

원하는걸 다 해주는 서비스를 NCloud에서 제공해준다~

많은 기능들이 있는데

- 이미지 변환
- 크기 변환
- 워터마크
- 필터 효과
- 포멧 변경
- 등등
를 제공해준다

### 금액

![](https://i.imgur.com/iIOcaIm.png)

금액은 다음과 같다
근데 이거 말고도 기본적으로 `CDN`, `Log Analytics`등의 요금도 추가라 직접 계산해봐야 할듯하다


### 구성

[NCloud Blog Image Optimizer](https://blog.naver.com/n_cloudplatform/221275312619)
공식 블로그를 보면
> > On Demand 프로세싱
> 
> Image Optimizer는 첫 번째 요청에 on demand로 섬네일이 생성되며,
> 그 뒤로는 CDN에 캐싱 되어 사용자에게 서비스됩니다.

라는 말을 볼 수 있다

첫 요청시 파라미터의 조합으로 썸네일을 생성하고 `CDN`에 캐싱해 2번째 요청부턴 캐싱되어있는 값만을 읽게 된다

이제 실제로 사용해보자ㅏ
https://www.ncloud.com/guideCenter/guide/28

## 간단하게 사용해보기
### Object Storage에 버킷 생성 및 공개 설정

Object Storage는 `VPC` 서비스이며 이름은 고유한 값을 가져야함

#### 버킷 생성
![](https://i.imgur.com/9HTRm1H.png)

![](https://i.imgur.com/96mVP9F.png)

![](https://i.imgur.com/aSKJoJA.png)

테스트용 버킷이니까 그냥 공개로..
실제로는 이렇게 하면 안됨


![](https://i.imgur.com/GlktvxV.png)
이런식으로 생성하게 되면

#### 버킷에 이미지 업로드
![](https://i.imgur.com/Kl1URYC.png)

![](file:///var/folders/3h/hrjphk6x4cv_670dtprs5kb40000gn/T/TemporaryItems/NSIRD_screencaptureui_3ksKbs/%E1%84%89%E1%85%B3%E1%84%8F%E1%85%B3%E1%84%85%E1%85%B5%E1%86%AB%E1%84%89%E1%85%A3%E1%86%BA%202023-12-15%20%E1%84%8B%E1%85%A9%E1%84%8C%E1%85%A5%E1%86%AB%2012.04.49.png)

![](https://i.imgur.com/2NyRT8Q.png)

대충 아무거나 올려주기

### Global Edge 프로필 생성

Global Edge는 네이버 클라우드 플랫폼의 CDN 서비스이다
일단은 이정도만 알아두고 패스

![](https://i.imgur.com/TLs8xjm.png)

우선 Global Edge 프로필을 만들어준다

![](https://i.imgur.com/7x2MMVZ.png)

### Image Optimizer 프로젝트 생성, 설정

#### Image Optimizer 프로젝트 생성
![](https://i.imgur.com/xV2xXWV.png)

![](https://i.imgur.com/jpHtl9J.png)

![](https://i.imgur.com/zMuuiPe.png)

이러고 생성하면??


![](https://i.imgur.com/AiOWZDL.png)

요렇게 생성 중으로 표시된다ㅏ

그리고 Global Edge에 들어가보면??
![](https://i.imgur.com/OUp3JKl.png)

요거도 생성중이라 나오게 된다

근데 생성되는데 시간이 좀 걸려서..
기다리자.....
#### Image Optimizer 룰 설정

[Query String 작성 가이드](https://guide.ncloud-docs.com/docs/media-media-3-2)
세세한 설정 관련은 위 링크에서 확인

![](https://i.imgur.com/rDkBQSz.png)

일단 예제로
- 리사이즈 및 크롭
    - 가로 100, 세로 100으로 줄인 후 넘치는 부분은 크롭
    - `/파일명.jpg?type=f&w=100&h=100`
- 리사이즈
    - 회전 정보가 있을 경우 회전하고 "가로 320, 세로 320" 프레임 안에 들어가도록 비율 유지 축소, 여백을 FFFFFA 색상으로 채우고 JPGE quality 95로 압축
    - `/파일명.jpg?type=m&w=320&h=320&autorotate=true&bgcolor=FFFFFA&quality=95`

로 있는데

그냥 `쉬운 입력`으로 가자

일단은 리사이즈만 설정

![](https://i.imgur.com/Ubd2WcU.png)

이렇게 2개 추가했다

![](https://i.imgur.com/GMsA81A.png)

#### 300, 300
![](https://i.imgur.com/CllLrU9.png)
#### 100, 100
![](https://i.imgur.com/kBQHcK2.png)

이런식으로 `URL`을 이용해 확인해보면 정상적으로 처리 되는 것을 볼 수 있다~

![](https://i.imgur.com/K6McGo1.png)

그리고 여러번 요청해도 캐싱되어 있기 때문에 첫 요청 2번만 변환된 것을 볼 수 있다


## 결론

이렇게 Image Optimizer를 사용해봤다

다른 aws의 `Lambda`, `CloudFront`를 사용해 구성하는 과정보다
훨씬 쉽게 `On-Demand` 이미지 리사이징을 구현할 수 있다

직접 `CDN`, `Serverless` 로 구현하는 것보단 자유도가 떨어지지만
이 구현에 많은 시간, 리소스를 들이지 않고 싶다면 Image Optimizer를 이용하는 것도 좋은 선택이 될 것 같다



#### 참고자료
- https://up7wvzqs1914.edge.naverncp.com/7MYQuUV5TJ/cat.jpeg?type=m&w=300&h=300
- https://guide.ncloud-docs.com/docs/media-media-3-2
- https://www.ncloud.com/guideCenter/guide/28
- [[이렇게 사용하세요!] **Image Optimizer** 활용하여 손쉽게 이미지 리사이징하기](https://blog.naver.com/n_cloudplatform?Redirect=Log&logNo=222027090816&from=postView)
- [[미디어 기술의 이해] **Image Optimizer** Query String 및 Filter 원리 집중 탐구](https://blog.naver.com/n_cloudplatform?Redirect=Log&logNo=222488916447&from=postView)
- [[이렇게 사용하세요!] **Image Optimizer**로 섬네일 만드는 방법](https://blog.naver.com/n_cloudplatform?Redirect=Log&logNo=221362200392&from=postView)