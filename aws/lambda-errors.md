# lambda 쓰면서 나온 에러들

## 라이브러리 import error
> selenium, chromedriver 등을 import를 하지 못하거나 제대로 기능을 하지 않음  
- chromedriver을 .zip으로 같이 묶어 올림
    - chromedriver의 용량이 커 preview가 되지 않고 제대로 동작을 하지 않음
    - 레이어로 만들어 올리기
        - 이또한 제대로 동작하지 않음
- 레이어로 모든 라이브러리 올리기
    - 동작하지 않음
    - 파이썬 버전탓인지? 혹은 lambda의 opt 디렉토러 문제인지
    - 동작하지 않았음
- docker을 이용해 버전 관리
    - dockerfile을 작성해 image로 배포
    - 정상적으로 동작
    - [docker 내용 정리]()
## empty page source return error
> driver.get(url) 에서
```<html><head></head><body></body></html>```
을 리턴   
- 해결하기 위한 방법
    - selenium, chorme, headless chrome, chronium 등
    - 사용하는 라이브러리의 버전이 맞는지 확인함 - docker
    - 라이브러리와 파이썬 버전 등 모두 정상작동중
- 원인
    - rds로 db를 연결중이라 rds와 lambda를 vpc로 연결해놓음
    - vpc가 문제
    - vpc로 사설 네트워크망에 분리해놓으면
    - private subnet에서 외부 인터넷에 접속하기 위해선 별도의 nat gateway가 필요함
    - [vpc 내용 정리]()
- 해결방법
    - nat gateway는 유료 서비스임
        - 시간 단위로 가격이 측정되어 부담이됨
    - 그냥 rds의 접근을 public으로 바꾼후
    - lambda함수를 rds에서 제외
    - 후 접근을 해보니 정상적으로 웹페이지 소스가 받아와짐
- 문제점
    - rds의 접근을 public으로 사용
    - lambda를 vpc에서 제외했기 떄문에 보안성 문제

## TimeoutException
> [ERROR] TimeoutException: Message: timeout: Timed out receiving message from renderer  

원인  
- lambda 구성에서 제한시간을 너무 짧게 설정
    - 너무 느린 코드
    - 최적화 하기
- 구성에서 메모리를 적게 설정해서 성능이 충분하지 않음
    - 128MB로 설정했을 때
    - selenium driver.get(url) 사용
    - 너무 느려 타임아웃이 뜨게 됨
    - 256MB로 늘리니 성공  

결론
- 람다 함수 제한 시간을 늘리자
- 람다 성능을 올리자
- **하지만 우선적으로 빠른 코드를 짜자**
    - 빠르고 간결한 코드

