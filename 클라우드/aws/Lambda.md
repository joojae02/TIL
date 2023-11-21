
## 우선 서버리스란??
> 서버가 없다??? 

서버가 없다는 뜻이 아닌 서버의 존재를 신경 쓸 필요가 없다는 뜻이다.  
사용자는 코드에만 집중하면 된다

#### 장점
- 개발자가 서버를 직접 관리할 필요가 없는 아키텍쳐
- 사용량에 따라 자원 할당. Auto Scaling
- 사용한 만큼 지불
- 서버에 대해 일정 관리할 필요가 없어 비즈니스 로직에 집중할 수 있음

코드를 Function 단위로 쪼개 대기 상태에 둠
-> 요청이 들어오면 서버가 대기상태의 Function을 실행시켜 처리
-> 끝나면 다시 대기 상태로 만듬
# lambda
## labmbda란?
lambda는 AWS에서 제공하는 서버리스 컴퓨팅 플렛폼이다  

- Function 단위로 어플리케이션을 올림
- 이벤트가 발생되면 실행
- 서버리스의 대표적인 서비스

- 로드 밸런싱 지원
- 오토 스케일링 지원
- 에러시 자동 에러 핸들링

![](https://i.imgur.com/xHB2WzT.png)

### 언제 쓰는게 좋은가?
코드를 계속 실행시키는 것보단 특정 조건때 실행하는 코드를 사용할때 유용한다.
- 서버 없이 간단한 코드 실행
- 특정 기간, 특정 주기로 코드 실행
- 트리거 실행될 때 코드 실행
이럴때 사용 하면 편하다.

단점도 존재한다
- 코드 용량이 250MB
- 함수 실행 시간 최대 15분
- 처음 함수가 cold start를 하게 되여 초기 지연시간이 발생
- 비쌈

## Lambda 함수 구성
#### Handler() 함수
람다 호출 시 실행되는 함수
하나의 람다당 하나의 `Handler()`
#### event 객체
람다 호출 시 전달되는 데이터
#### context 객체
람다에 대한 런타임 관련 정보가 담겨있음

```python
import json
def lambda_handler(event, context):
	print(event)
	print(context.get_remaining_time_in_millis())
	print(context.memory_limit_in_mb)
	
	return {
		'statusCode': 200,
		'body': json.dumps(event['Records']['s3']['bucket']['name'])
	}
```

## Lambda 함수 실행

#### Cold Start
- 함수를 실행 시킬 실행환경이 없으면, 새로운 실행환경을 만듦
#### Warm Start
- 함수를 실행 시킬 실행환경이 있으면, 해당 실행 환경 에서 함수를 실행 시킴

### 실행 환경

![](https://d2908q01vomqb2.cloudfront.net/fc074d501302eb2b93e2554793fcaf50b3bf7291/2019/06/27/Screen-Shot-2019-06-27-at-2.23.51-PM-1024x510.png)

#### 동기 호출
- API Gateway
#### 비동기 호출
- Amawon SNS, S3
	- SNS에 메세지가 도달했을때
	- S3 객체 생성시 
	- 비동기로 전달
#### Stream 기반 호출
- DynamoDB Stream, Kinesis를 플링하여 전달

## Lambda 개발 환경

- Lambda Web Console
- AWS CLI 
- CDK (Cloud Development Kit)
- SAM (Serverless Framework)

## Lambda 사용 예시

### Web Apps
- 정적 HTML 페이지
### Backends
- Apps, services
- 백엔드 서버
### Data Processing
- 실시간 스트리밍
- Batch
### IT Automation
- 시스템 정책 관리
- 인프라 구조 관리


## 레이어
> Lambda 계층은 추가 코드 또는 데이터를 포함하는 .zip 파일 아카이브
> 	일반적으로 라이브러리 종속 항목, 사용자 지정 런타임 또는 구성 파일이 포함

#### 사용 이유
- 배포 패키지의 크기를 줄이기 위해
- 핵심 함수 로직을 종속 항목과 분리하기 위해
- 여러 함수에서 종속 항목을 공유하기 위해
- Lambda 콘솔 코드 편집기를 사용하기 위해

![](https://i.imgur.com/CxZOk5b.png)

- AWS 람다는 함수 실행에 필요한 모든 라이브러리를 담아야함  
- 레이어를 사용하지 않으면 모든 함수에 라이브러리를 매번 넣어줘야함

- 람다 레이어를 이용하면 공통 부분을 만들어 함수사이 고유 가능함  

참고  
- https://docs.aws.amazon.com/lambda/latest/dg/welcome.html
- https://docs.aws.amazon.com/lambda/latest/dg/getting-started.html
- https://docs.aws.amazon.com/ko_kr/lambda/latest/dg/chapter-layers.html
- https://www.44bits.io/ko/keyword/aws-lambda
