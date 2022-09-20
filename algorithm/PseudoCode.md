# Pseudocode 수도코드
> 수도코드?
수도코드는 의사코드로도 불린다.  
코딩하기 전에 전체적인 흐름을 짜는 것이다.  
수업에서는 이렇게 말한다.   
> 직접 실행할 수 있는 프로그래밍언어는 아니지만,  
> 거의 실제 프로그램에 가깝게 계산과정을 표현할 수 있는 언어  

수업에서 알고리즘은 보통 의사코드로 표현한다  
c++ 과 비슷한 수도코드를 사용한다.  
차이점
- 배열 인덱스의 범위에 제한이 없음
    - C++는 반드시 0부터 시작
    - 의사코드는 임의의 값 사용 가능
- 프로시저의 파라미터에 2차원 배열 크기의 가변성 허용 예: void pname(A[][]) { … }
    - 지역배열에 변수 인덱스 허용
    - 예: keytype S[low..high];
- 수학적 표현식 허용
    - low <= x && x <= high , low <= x <= high
    - temp = x; x = y; y = temp , exchange x and y
        - C++에 없는 타입 사용 가능
    - index: 첨자로 사용되는 정수 변수
    - number: 정수(int) 또는 실수(float) 모두 사용 가능
    - bool: “true”나 “false” 값을 가질 수 있는 변수
- 제어 구조
    - repeat (n times) { … }
- 프로시저와 함수
    - 프로시저: void pname(…) {…}
    - 함수: returntype fname (…) {… return x;}
- 참조 파라미터(reference parameter)를 사용하여 프로시저의 결과값 전달
    - 배열: 참조 파라미터로 전달
    - 기타: 데이터타입 이름 뒤에 &를 붙임
    - const 배열: 전달되는 배열의 값이 불

```c++
// Sequential Search Algorithm 
// 수도코드로 표현
void seqsearch(int n, // 입력(1)
               const keytype S[], // (2)
               keytype x, //(3)
               index& location ) { // 출력

    location = 1;
    while (location <= n && S[location] != x)
        location++;
    if (location > n)
        location = 0;
}
```
