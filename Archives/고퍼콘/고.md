# Golang프로젝트 스텝
코드패턴, 아키텍쳐 등등..
## 작은 플젝 큰 플젝 차이

기술 도입은 어렵다.. 적재적소 해야함..

작은 유니콘을 만들자

기본 라이브러리 사용해서 개발하기

### 기능 단위의 프로젝트 코드 패턴
Struct 를 쓰면 의존성 문ㅈ제가 생김
- 기능단위로 개발해야하는데 너무 많은 필드, 의존성을 가짐

- Handler 
	- 명확한 구조
- HandlerFunc
	- 간단한 작성
	- 의존성 주입이 쉬움
	- 작은 단위 플젝에서 좋음

선택 기준) 기능단위면 HandlerFunc 복잡한 로직, 어려우면 Handler

### 엔터프라이즈를 위한


도메인은 내부로직 전반
모델이 내부에서 돌아야함

- Presenter: 도메인 모델 api로 전환
	- 다양한 클라에 서로다른 presenter
- Handler: 요청 처리 응답 생성 담당
	- 핸들러는 유즈케이스를 가지고 프레젠터로 변경하고 응답 줌
- UserCase: 서비스, 레포를 의존성으로 받아 느슨한 결합
	- 복잡한 비지니스 로직 가장 상위 서비스
	- 살짝 검증 역할??
- Serivce
	- 유즈케이스의 무거운 로직을 서비스로 분리
	- 필요한 경우 (불필요한 추상화를 피하자)
- Reopsitory: 데이터 접근 로직만
	- 의존성 역전 원칙
- Recoder:
	- 옵셔널
	- api, 쿼리 언어 추상화
	- 근데 복잡도가 없는 경우 레포딴에서 마무리 하기도

Reopsitory/Recoder??

쿼리에서만 쓰고 비지니스 로직에서 불필요하지만
검증하기 위해 레코더란 레이어를 사용

#### 각 레이어 테스트 코드
- Fake Implementations

레코더, 도메인 fakes 만들기

#### 앱 릴리즈 위해 붙이는 도구

APM  datadog
Error Sentry
Metric Prometheus
Log service

APM 가시성 성능 문제

# 이미지 성능 개선

- Golang 으로 빠르게 마이그레이션
- 이미지 처리, 컨테이너

프레임워크로 Gin 사용
PHP / Golang 비교 PHP가 빠르고 리소스도 적게 사용

이미지 리사이징 속도
nfnt/resize 가 느렸음

libvips 라이브러리 사용
- 훨씬 더 좋은 성능을 가진다

빠른 롤백 가능하게
점진적 배포

컨테이너 최적화
GOMAXPROCS
런타임에서 최대 CPU 사용량 지정

autogomaxprocs

# 차량 업데이트

### 보안 기본 개념
CIA Triad
- 기밀성
	- enveloped encription
- 무결성
	- uptane: 차량 업데이터 보안 무결성 오픈소스 프레임워크
- 가용성


암호화. 
크립토 기본 패키지


Wails???

# Golang 웹 프레임워크 Gin 모니터링

### Gin

가장 유명 최근 나오는 프레임워크보단 느리지만 충분히 좋은 성능


MSA로 갈때 복잡해서 APM 이 필수

### Gin monitoring 
APM 과정 톺아보기

Metric
Trace
~~Log~~


Gin 모니터링 위해서 미들웨어 필요

#### Metric

- Request Duration
- Request Count
- Status Code

### Trace

Http 로우 레발 transport - roundtripper

Header span id

미들웨어는 
- TransID (있다며 유지) - 하나의 흐름
- SpanID (매번 새로 생성) - 하나의 작업
검사


# 랜덤 실패 테스트 방지

### Deterministic Testing

monkey patch?
파이썬에선 쉽지만
golang에서는 아쉽다

Flaky Testing..


비 결정적 요소를 고정하기
rand.Seed?? xx 없어짐

Rander를 주입해서 사용하도록 수정

생성함수를 인자로 받기

map 순회시 순서 보장 X
Slice sorting

Go Routine

시간 테스트
time.now()

time func 같은걸로 하자

Clock 인터페이스를 구성해서 사용하기??

type Clock interface {
	After
Sleep

}



# 쿠버네티스 LMA


k8s LMA 벤티 스택

AGPL