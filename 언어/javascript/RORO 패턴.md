
## RORO 패턴이란??
> **"객체로 받고 객체로 반환한다(Receive an object, return an object)"**의 줄임말이다

ES2015에 도입된 _구조 분해_ 기능을 이용한 패턴인데

- 명명된 매개변수
- 더 깔끔한 기본 매개변수
- 더 풍부한 반환 값
- 간편한 기능 구성
등의 이점이 있다

만약 이런 함수가 있다고 가정해보자
```typescript
function findUsersByRole (role: stirng, withContactInfo?: boolean, includeInactive?: boolean) {...}
```
이 함수의 호출은
```typescript
findUsersByRole(  'admin',   true,   true)
```
이런식으로 사용한다

마지막 두 매개변수는 어떤 역할을 담당하는지 한번에 알 수 없다.
> true, true????

대신에 단일 객체로 전송한다면??
```typescript
type FindUsersParams = {
	role: string;
	withContactInfo?: boolean;
	includeInactive?: boolean;
}

function findUsersByRole ({role, withContactInfo, includeInactive}: FindUsersParams) {...}
```
호출한다면
```typescript
findUsersByRole({  role: 'admin',   withContactInfo: true,   includeInactive: true})
```
이런식으로 호출하게 될 것이다

또는

```typescript
findUsersByRole({  role: 'admin',   includeInactive: true})
```
요렇게

기존 코드에서 
```typescript
function findUsersByRole (role: stirng, withContactInfo?: boolean, includeInactive?: boolean) {...}
```
이런 코드로 호출했다라고 할 때


```typescript
// 씁.. 
findUsersByRole('admin', undefined, true);
```
->
```typescript
type FindUsersParams = {
	role: string;
	withContactInfo?: boolean;
	includeInactive?: boolean;
}

function findUsersByRole ({role, withContactInfo, includeInactive}: FindUsersParams) {...}

findUsersByRole({  role: 'admin',   includeInactive: true})
```
요렇게 훨씬 깔끔하게 작성할 수 있다.

그리고 만약 빈 객체를 보내도 오류가 안나게 해야된다면??

```typescript
type FindUsersParams = {
	role: string;
	withContactInfo?: boolean;
	includeInactive?: boolean;
}

function findUsersByRole ({role, withContactInfo, includeInactive}: FindUsersParams = {}) {...}

findUsersByRole()
```
요렇게도 가능하다


```typescript
findUsersByRole('admin', undefined, true);
```
사실 이렇게 쓴 코드가 있ㅇ서ㅓ..
RORO로 바꾸니 확실히 깔끔해졌다


- 참고 자료
- [Elegant patterns in modern JavaScript: RORO](https://www.freecodecamp.org/news/elegant-patterns-in-modern-javascript-roro-be01e7669cbd/)
- [자바스크립트 디자인 패턴: RORO](https://taegon.kim/archives/8058)
- [Wikipedia: Named parameter](https://en.wikipedia.org/wiki/Named_parameter)