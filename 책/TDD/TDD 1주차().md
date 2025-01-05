
## 들어가는 글

TDD에서는
- 오직 자동화된 테스트가 실패할 경우에만 코드를 작성한다.
- 중복을 제거한다.
두가지 규칙만을 따른다.


다음과 같은 순서로 진행된다.
1. 빨강: 실패하는 작은 테스트를 작성한다.
2. 초록: 빨리 테스트가 통과하게끔 만든다.
3. 리펙토링: 모든 중복을 제거한다.

## 1부


TDD의 리듬
1. 빠르게 테스트 하나를 추가한다.
2. 모든 테스트를 실행하고 실패하는지 확인한다.
3. 코드를 조금 바꾼다.
4. 모든 테스트가 성공하는지 확인한다.
5. 리펙토링을 통해 중복을 제거한다.

### 1장. 다중 통화를 지원하는 Money 객체

어떤 기능을 달성하기 위해서 어떤 테스트들이 통과되어야하는지 생각하자.

Money 객체에선
- 통화가 다른 금액을 더해서 환율에 맞게 변한 금액을 결과로 얻을 수 있어야한다.
- 어떤 금액을 어떤 수에 곱한 금액을 결과로 얻을 수 있어야한다.

초록 막대
- 실패하는 테스트 작성하기
	- 보기 이상하고 부작용들이 있어도 상관없음!!
	- 일단 작성하기.

```java
public void testMultiplication() {
	Dollar five = new Dollar(5);
	five.times(2);
	assertEquals(10, five.amount);
}
```


그리고 실패 확인하기.
그리고 간단하게 성공시키기 위해
```Java
public class Dollar {
	int amount;
	
	public Dollar(int amount) {
		this.amount = amount;
	}

	public void times(int multiplier) {
		this.amount = this.amount * multiplier;
	}
}
```

### 2장. 타락한 객체

1. 테스트를 작성한다.
	- 원하는 인터페이스 포함하기
	- 필요한 모든 요소를 포함하기
2. 실행 가능하게 만들기
	- 어떻게든 빠르게 성공하도록 하기
3. 올바르게 만들기
	- 어떻게든 실행가능하게 만들었던 코드들을 깔끔하게 정리하기

> 목적은 동작하는 깔끔한 코드다!!

```java
public void testMultiplication() {
	Dollar five = new Dollar(5);
	five.times(2);
	assertEquals(10, five.amount);
	five.times(3);
	assertEquals(15, five.amount);
}
```

```Java
public class Dollar {
	int amount;
	
	public Dollar(int amount) {
		this.amount = amount;
	}

	// 처음 수정
	public void times(int multiplier) {
		this.amount *= multiplier;
		return null;
	}

	// 테스트 실패하는것 보고 난 후
	public void times(int multiplier) {
		return Dollar(amount * multiplier);
	}
}
```

빠르게 초록색을 보기 위해서
- 가짜로 구현하기: 상수를 반환하게 만들고 단계적으로 변수로 바꾼다.
- 명백한 구현 사용하기: 실제 구현을 입력한다.

삼각층량?? 

- 설계상의 결함으로인해 실패하는 테스트로 변환
- 스텁 구현으로 빠르게 컴파일이 통과하도록 수정
- 올바르다고 생각하는 코드를 입력하여 테스트를 통과

> 느낌을 테스트로 변환하는 것은 TDD의 일반적인 주제인다.

오래학수록 테스트로 담아내는것에 익숙해지게 된다?? - 결국 많이해보라는..
시스템이 어떤식으로 동작해야하는지 논의할 수 있다.

올바른 행위 -> 최상의 방법
결국 어떤 행위를 달성해야하는지를 명확히해야 최상의 방법을 고민할 수 있다.
- 테스트 케이스를 명확하게 짜야한다.
### 3장. 모두를 위한 평등

우선 빨간 막대

```java
public void testEquality() {
	assertTrue(new Dollar(5).equals(new Dollar(5)));
}
```

```Java
public class Dollar {
	int amount;
	
	public Dollar(int amount) {
		this.amount = amount;
	}

	public void times(int multiplier) {
		return Dollar(amount * multiplier);
	}

	public boolean equals(Object object) {
		return true; // 일단 테스트가 통과하도록 return 
	}
}
```



- 상수를 반환하는것으로는 성공할 수 없도록 수정하기

```java
public void testEquality() {
	assertTrue(new Dollar(5).equals(new Dollar(5)));
	assertTrue(new Dollar(5).equals(new Dollar(6)));
}
```

```Java
public class Dollar {
	int amount;
	
	public Dollar(int amount) {
		this.amount = amount;
	}

	public void times(int multiplier) {
		return Dollar(amount * multiplier);
	}

	public boolean equals(Object object) {
		Dollar dollar = (Dollar) object;
		return amount == dollar.amount;
	}
}
```

### 4장. 프라이버시

```java
public void testMultiplication() {
	Dollar five = new Dollar(5);
	assertEquals(new Dollar(10), five.times(2));
	assertEquals(new Dollar(15), five.times(3));
}
```

```Java
public class Dollar {
	private int amount;
	
	public Dollar(int amount) {
		this.amount = amount;
	}

	public void times(int multiplier) {
		return Dollar(amount * multiplier);
	}

	public boolean equals(Object object) {
		Dollar dollar = (Dollar) object;
		return amount == dollar.amount;
	}
}
```

동치성 테스트가 동치성에 대한 코드가 정확히 작동한다는 것을 검증하지 못한다면 곱하기 테스트 역시 검증할 수 없다.

- 오직 테스트를 향상시키기 위해서만 개발된 기능을 사용했다.
- 두 테스트가 동시에 실패하면 망핟다는 점 인식.
- 위험 요소가 있음에도 계속 진행했다.
- 테스트와 코드 사이의 결합도를 낮추기 위해, 테스트 객체의 새 기능을 사용했다.

### 5장. 솔직히 말하자면

```java
public void testFrancMultiplication() {
	Franc franc = new Franc(5);
	assertEquals(new Franc(10), five.times(2));
	assertEquals(new Franc(15), five.times(3));
}
```


1. 테스트 작성
2. 컴파일되게 하기
3. 실패하는지 확인하기 위해 실행
4. 실행하게 만듦
5. 중복 제거

1~4 단계는 빠르게 진행해야한다.

현재 장고에서 작성하는 테스트 코드의 형식은 빠르게 진행하기 힘들지 않을까??
- 디비에 저장하는 방식이라..

```java
public class Franc {
	private int amount;
	
	public Franc(int amount) {
		this.amount = amount;
	}

	public void times(int multiplier) {
		return Franc(amount * multiplier);
	}

	public boolean equals(Object object) {
		Franc franc = (Franc) object;
		return amount == franc.amount;
	}
}
```

현재 중복이 너무 많음.

equals()부터 일반화

- 큰 테스트를 공략할 수 없다. 작은 테스트만 구현함
- 중복을 만들고 조금 고쳐서 테스트를 작성했다. - Dollar, Franc
- 모델 코드까지 복사했다.
- 중복이 사라지기 전에는 집에 가지 않기로 약속했다..?

### 6장. 돌아온 '모두를 위한 평등'

현재 모델이 중복으로 작성되어있다.
이를 상속 구조로 수정한다.

Dollar -> Franc
Money -> Dolalr
	ㄴ> Franc 

```java
class Money {
	protected int amount;
}

class Dollar extends Money {}
```


```java
class Money {
	protected int amount;

	public boolean equals(Object object) {
		Money money = (Money) object;
		return amount == money.amount;
	}
}

// Franc 에서 Equals 제거!
```


리팩토링하면서 실수했는데도 테스트가 통과하면 어캄??
- 있으면 좋을거 같은 테스트를 작성해라.


- 리팩토링하다가 하나 빠트림
- 리팩토링에 안좋은 느낌을 가짐
- 리팩토링을 덜함
- 설계의 질이 떨어짐
- 해고.
- 강아지도 곁을 떠남
- 영양상태에 신경을 못씀
- 이가 안좋아짐..?

이를 건강하게 하기 위해 리팩토링하기 전 테스팅을 하자

```java
public void testEquality() {
	assertTrue(new Dollar(5).equals(new Dollar(5)));
	assertTrue(new Dollar(5).equals(new Dollar(6)));
	assertTrue(new Franc(5).equals(new Franc(5)));
	assertTrue(new Franc(5).equals(new Franc(6)));
}
```

```java
public class Franc extends Money {
	public Franc(int amount) {
		this.amount = amount;
	}

	public void times(int multiplier) {
		return Franc(amount * multiplier);
	}
}
```