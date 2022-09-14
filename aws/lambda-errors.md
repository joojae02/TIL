# lambda 쓰면서 나온 에러들

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
    