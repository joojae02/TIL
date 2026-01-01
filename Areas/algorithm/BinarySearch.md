# BinarySearch

> W(n) = log n + 1

- 문제: 크기가 n인 정렬된 배열 S에 x가 있는지를 결정하라.
- 입력: 자연수 n, 비내림차순으로 정렬된 배열 S[1..n], 찾고자 하는 항목 x
- 출력: locationout - x가 S의 어디에 있는지의 위치. 만약 x가 S에 없다면 0

```c
index location (index low, index high) {
    index mid;
    if (low > high)
        return 0; // 찾지 못했음
    else {
        mid = (low + high) / 2; // 정수 나눗셈 (나머지 버림)
        if (x == S[mid])
            return mid; // 찾았음
        else if (x < S[mid])
            return location(low, mid-1); // 왼쪽 반을 선택함
        else
            return location(mid+1, high); // 오른쪽 반을 선택함
    }
}
...
locationout = location(1, n); // evoke location
...

```
- 분할 `(low, mid-1)`,`(mid+1, high)`
- 해결 재귀 호출   

정리
- 재귀에선 스택에 계속 쌓임
    - 메모리 낭비
    - 전역으로 처리
- O(lgN)

## Worst-Case Time Complexity Analysis
### case 1 : n is a power of 2
- W(n) = W(n/2) + 1 (n>1)
- W(1) = 1
이는 
- W(1) = 1
- W(2) = W(1) + 1 = 2
- W(3) = W(2) + 1 = 3
- W(4) = W(3) + 1 = 4
- W(8) = W(4) + 1 = 5
- ...
- W(2^k) = k + 1
    - 2^k = n 이라 할때 k = log n
- W(n) = lg n + 1

### case 2: n is not restricted to being a power of 2



