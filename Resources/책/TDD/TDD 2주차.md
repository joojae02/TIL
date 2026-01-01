
## 7장. 사과와 오렌지

```java
public void testEquality() {
	assertTrue(new Dollar(5).equals(new Dollar(5)));
	assertFalse(new Dollar(5).equals(new Dollar(6)));
	assertTrue(new Franc(5).equals(new Franc(5)));
	assertFalse(new Franc(5).equals(new Franc(6)));
	assertFalse(new Franc(5).equals(new Dollar(5)));
}


class Money {
	protected int amount;

	public boolean equals(Object object) {
		Money money = (Money) object;
		return amount == money.amount && getClass().equals(money.getClass());
	}
}
```

통화(currency)와 같은 개념이 있으면 좋지만 아직 도입할 이유가 없다.

- 결함을 테스트에 담았다.
- 어케 테스트를 통과하게 했다.
- **동기, 이유가 있지 않은 한 더 많은 설계를 도입하지 않는다**

## 8장. 객체 만들기

```java
public class Dollar {
	private int amount;
	
	public Dollar(int amount) {
		this.amount = amount;
	}

	public Dollar times(int multiplier) {
		return Dollar(amount * multiplier);
	}
}

public class Franc {
	private int amount;
	
	public Franc(int amount) {
		this.amount = amount;
	}

	public Franc times(int multiplier) {
		return Franc(amount * multiplier);
	}
}
```

Money에 Dollar를 반환하는 팩토리 메서드 도입?

```java
class Money {
	static Dollar dollar(int amount) {
		return new Dollar(ammount);
	}
}
```

```java
public void testMultiplication() {
	Money five = Money.dollar(5);
	assertEquals(new Dollar(10), five.times(2));
	assertEquals(new Dollar(15), five.times(3));
}
```

아직 times()가 없음

Money를 추상 클래스로

```java
abstract class Money
abstract Money times(int multiplier);

class Money {
	static Money dollar(int amount) {
		return new Dollar(ammount);
	}
}
```
https://olrlobt.tistory.com/70
```java
public void testMultiplication() {
	Money five = Money.dollar(5);
	assertEquals(Money.dollar(10), five.times(2));
	assertEquals(Money.dollar(15), five.times(3));
}
```

이제 Dollar라는 하위 클래스가 있다는 사실을 알지 못한다.
하위 클래스를 분리함으로써 모델코드에 영향을 주지 않고 상속 구조를 변경할 수 있게 되었다.

```java
public void testEquality() {
	assertTrue(Money.dollar(5).equals(Money.dollar(5)));
	assertFalse(Money.dollar(5).equals(Money.dollar(6)));
	assertTrue(Money.franc(5).equals(Money.franc(5)));
	assertFalse(Money.franc(5).equals(Money.franc(6)));
	assertFalse(Money.franc(5).equals(Money.dollar(5)));
}

class Money {
	static Money dollar(int amount) {
		return new Dollar(ammount);
	}
	
	static Money frnac(int amount) {
		return new Franc(ammount);
	}
}
```

- 동일한 메서드ㄹ의 두 변이형 메서드 서명부를 통일했다.
- 팩토리 메서드로 하위 클래스의 존재를 분리했다.
- 하위 클래스가 사라지면서 몇몇 테스트는 불필요해졌지만 놔뒀다.

## 9장. 우리가 사는 시간

통화 구현법..? X
통화 테스트법

```java
public void testCurrency() {
	assertEquals("USD", Money.dollar(1).currency());
	assertEquals("CHF", Money.franc(1).currency());
}

```


```java
abstract class Money {
	abstract Money times(int multiplier);
	abstract String currency();
}
```

```java
class Franc {
	private String currency;

	Franc(int amount) {
		this.amount = amount;
		currency = "CHF";
	}

	String currency() {
		return currency;
	}
}

class Dollar {
	private String currency;

	Dollar(int amount) {
		this.amount = amount;
		currency = "UKD";
	}

	String currency() {
		return currency;
	}
}
```

Money로 추상화?

```java
abstract class Money {
	protected String currency;

	String currency() {
		return currency;
	}

	static Money franc(int amount) {
		return new Franc(amount, null);
	}
}

class Franc extends Money {
	Money times(int multiplier) {
		// 팩토리 안썼네???
		return new Franc(amount * multiplier, null);

		return Money.franc(amount * multiplier);
	}
}
```

원래 같으면 기다리는게 맞다.
다만 짧은 중단은 그냥 고치자;
다만 하던 일을 중단하고 다른 일을 하는 상태에서 또 중단하지는 않는다.

```java
abstract class Money {
	protected String currency;

	String currency() {
		return currency;
	}

	static Money franc(int amount) {
		return new Franc(amount, "CHF");
	}
}

class Franc {
	private String currency;

	Franc(int amount, String currency) {
		this.amount = amount;
		this.currency = currency;
	}

	String currency() {
		return this.currency;
	}
}
```

너무 작은 단위로 진행하나???
좀 더 큰 단위로 리펙토링, 테스트 코드를 짜자

그러다가 좀 불안하면 다시 작게..

계속 늘리고 줄이고

두 Dollar, Franc이 같아졌다면
다시 Money로 추상화


```java
abstract class Money {
	Money(int amount, String currency) {
		this.amount = amount;
		this.currency = currency;
	}
}

class Franc extends Money {
	Franc(int amount, String currency) {
		super(amount, currency);
	}
}

class Dolalr extends Money {
	Dolalr(int amount, String currency) {
		super(amount, currency);
	}
}
```


- 큰 설계하다가 중단하고 더 작은걸 헀다.
- 팩토리 메서드로 옮겨서 생성자를 일치시켰다.


## 10장. 흥미로운 시간

```java
class Franc {
	Money times(int muliplier) {
		return new Franc(amount * multiplier, currency);
	}
}

class Dollar {
	Money times(int muliplier) {
		return new Dollar(amount * multiplier, currency);
	}
}


class Franc {
	Money times(int muliplier) {
		return new Money(amount * multiplier, currency);
	}
}

class Dollar {
	Money times(int muliplier) {
		return new Money(amount * multiplier, currency);
		// Money를 콘크리트 클래스로??
	}
}
```


```java
abstract class Money {
	public String toString() {
		return amount + " " + currency;
	}

	public boolean equals(Object object) {
		Money money = (Money) object;
		return amount == money.amount && getClass().equals(money.getClass());
	}
}
```

toString() 메서드는 디버깅용. 리스크가 적다.

이떄 equals 가 문제
클래스가 같은게 아니라 currency가 같은지 봐야함.

```java
class Franc {

	Money times(int multiplier) {
		return new Franc(amount * multiplier, currency);
	}
}

public void testDifferentClassEquality() {
	assertTrue(new Money(10, "CNF").equals(new Franc(10, "CHF")));
}


```

```java

abstract class Money {
	public String toString() {
		return amount + " " + currency;
	}

	public boolean equals(Object object) {
		Money money = (Money) object;
		return amount == money.amount && currency().equals(money.currency());
	}
}

```


두 times를 일치시키기 위해 호출하는 메서드들을 인라인 시킨 후 상수를 변수로 변경했다.
- currency
디버깅을 위해 테스트 없이 toString()추가


## 11장. 모든 악의 근원


그러면 이제 Franc, Dollar에는 생성자만 있다.
이건 비효율적임

```java
abstract class Money {
	static Money dollar(int amount) {
		return new Money(amount, "USD");
	}

	static Money franc(int amount) {
		return new Money(amount, "CHF");
	}
}
```

그럼 기존 테스트 코드들은 충분한가

```java
public void testEquality() {
	assertTrue(new Dollar(5).equals(new Dollar(5)));
	assertFalse(new Dollar(5).equals(new Dollar(6)));
	assertTrue(new Franc(5).equals(new Franc(5))); // 불필요
	assertFalse(new Franc(5).equals(new Franc(6))); // // 불필요
	assertFalse(new Franc(5).equals(new Dollar(5)));
}
```

Dollar, Franc 클래스를 지우려고 하기에
하위 클래스를 사용하는 테스트는 짐이 된다.

- 하위 클래스의 속을 들어내고 삭제했다.
- 기존 구조에서는 필요했지만 현재 구조에선 필요하지 않은 테스트 코드를 삭제한다.

**불필요한 테스트 코드는 지우자**

## 12장. 드디어, 더하기

```java
public void testSimpleAddition() {
	Money sum = Money.dollar(5).plus(Money.dollar(5))
	assertEquals(Money.dollar(10), sum)
}



Money plus(Money added) {  
    return new Money(amount + added.amount, currency);  
}

```


환율을 표현할 수 있으면서 산술 연산 처럼 다를수 있는 객체..

Money와 비슷하지만 Money의 두 합을 나타내는 객체를 만들자
그럼 연산의 결과로 Expression들이 생긴다.

```java
public void testSimpleAddition() {
	Money sum = Money.dollar(5).plus(Money.dollar(5))
	assertEquals(Money.dollar(10), sum)
	Money reduced = bank.reduce(sum, "USD");
	assertEquals(Money.dollar(10), reduced)
}
```

왜 bank 가 reduce를 하냐??

Expression은 하려고 하는일의 핵심
핵심이 되는 객체가 해당 책임만 가지길 원함.
그래야 유연해짐

Expression에 오퍼레이션은 많아지ㄹ텐데 모두 넣으면 Expression이 너무 커질것


```java
public void testSimpleAddition() {
	Money five = Money.dollar(5);
	Expression sum = five.plus(five);
	Bank bank = new Bank();
	Money reduced = bank.reduce(sum, "USD");
	assertEquals(Money.dollar(10), reduced)
}
```

그럼 Expression이 필요

```java
interface Expression

class Money implements Expression {

	Expression plus(Money added) {
		return new Money(amount + added.amount, currency);
	}
}
```

```java
class Bank {
	Money reduce(Expression source, String to) {
		return Money.dollar(10);
	}
}
```

큰 테스트를 작은 테스트로 ($5 + 10CHF -> $5 + $5) 로 줄여서 먼저 테스트
계산에 대한 메타포들을 생각
새 메타포에 기반하여 테스트 재작성


## 13장. 진짜로 만들기
```java
class Bank {
	Money reduce(Expression source, String to) {
		return Money.dollar(10);
	}
}
```

```java
public void testSimpleAddition() {
	Money five = Money.dollar(5);
	Expression sum = five.plus(five);
	Bank bank = new Bank();
	Money reduced = bank.reduce(sum, "USD");
	assertEquals(Money.dollar(10), reduced)
}
```

이걸 Money.plus()가 Money가 아니라 Expression을 반환해야한다.

```java
public void testSimpleAddition() {
	Money five = Money.dollar(5);
	Expression result = five.plus(five);
	Sum sum = (Sum) result;
	assertEquals(five, sum.augend)
	assertEquals(five, sum.augend)
}
```

이 테스트는 오래 가지 못함
외부행위가 아닌 내부 구현에 너무 깊게 관여하고 있음
그래서 augend, addend 필드가 필요함


```java
class Sum {
	Money augend;
	Money addend;
}

class Money {
	Expression plus(Money addend) {
		return new Sum(this, addend);
	}
}

class Sum implements Expression {
	Sum (Money augend, Money addend) {
		this.augend = augend;
		this.addend = addend;
	}
}
```


Bank.reduce()는 sum을 받고 sum의 Money 통화가 모두 일치하고 reduce를 통해 얻는 Money의 통화도 같다면 Sum 내에 Money의 amount의 합과 같다

```java

public void testReduceSum() {
	Expression sum = new Sum(Money.dollar(3), Money.dollar(4));
	Bank bank = new Bank();
	Money result = bank.reduce(sum, "USD");
	assertEquals(Money.dollar(7), result);
}

class Bank {
	Money reduce(Expression source, String to) {
		Sum sum = (Sum) source;
		int amount = sum.augend.amount + sum.addend.amount;
		return new Money(amount, to);
	}

}
```
- 캐스팅 모든 Exrpession에 대해서 작동해야하는데 Sum에 의존적
- 공용 필드와 그 필드들에 대한 두단계에 걸친 레퍼런스


```java
class Bank {
	Money reduce(Expression source, String to) {
		Sum sum = (Sum) source;
		return sum.reduce(to);
	}
}

class Sum {
	public Money reduce(String to) {
		int amount = augend.amount + addend.amount;
		return new Money(amount, to);
	}
}
```

좀 더 자세하게

```java
public void testReduceMoney() {
	Bank bank = new Bank();
	Money result = bank.reduce(Money.dollar(1), "USD");
	assertEquals(Money.dollar(1), result);
}

class Bank {
	Money reduce(Expression source, String to) {
		if (source instanceof Money) return (Money) source;
		Sum sum = (Sum) source;
		return sum.reduce(to);
	}
}
```

지저분하더라도 일단 돌아가게 하고 리펙토링하자
이런식으로 클래스를 명시적으로 검사한다면 다형성을 이용하도록 만든다

```java
class Bank {
	Money reduce(Expression source, String to) {
		if (source instanceof Money) 
			return (Money) source.reduce(to);
		Sum sum = (Sum) source;
		return sum.reduce(to);
	}
}

class Money {
	public Money reduce(String to) {
		return this;
	}
}

interface Expression {
	Money reduce(String to);
}

class Bank {
	Money reduce(Expression source, String to) {
		return source.reduce(to);
	}
}
```

테스트는 돌아가지만 모든 중복이 제거될떄까지 통과한것으로 치지 않는다.
구현하기 위해 순방향으로 구현했다.
앞으로 필요할것 같은 객체의 생성을 강요하기 위한 테스트를 짰다.
빠른 속도로 구현.


## 14장. 바꾸기

```java
public void testReduceMoneyDifferentCurrency() {
	Bank bank = new Bank();
	bank.addRate("CHF", "USD", 2);
	Money result = bank.reduce(Money.franc(2), "USD");
	assertEquals(Money.dollar(1), result);
}
```
일단 1:2인 경우 

```java
class Money {
	public Money reduce(String to) {
		int rate = (currency.equals("CHF") && to.equals("USD")) ? 2 : 1;
		return new Money(amount / rate, to);
	}
}
```
코드에서 하드코딩으로 박아버림;;

이걸 바꿔야지.
Expresson.reduc()인자로 bank를 던지자

```java
class Bank {
	Money reduce(Expression source, String to) {
		return source.reduce(this, to);
	}

	int rate (String from, String to) {
		return (currency.equals("CHF") && to.equals("USD")) ? 2 : 1;
	}
}

interface Expression {
	Money reduce(Bank bank, String to);
}

class Sum {
	public Money reduce(Bank bank, String to) {
		int amount = augend.amount + addend.amount;
		return new Money(amount, to);
	}
}

class Money {
	public Money reduce(Bank bank, String to) {
		int rate = bank.rate(currency, to);
		return new Money(amount / rate, to);
	}

}
```
아직도 환율 하드코딩.

해시테이블로 매핑시키자

```java
public void testArrayEquals() {
	assertEquals(new Object[] {"abc"}, new Object[] {"abc"});
}
```

키를 위한 새로운 객체

```java
private class Pair {
	private String from;
	private String to;

	Pair(String from, String to) {
		this.from = from;
		this.to = to;
	}
}
```

Pair를 Key로 쓸꺼니까 equals(), hashCode()구현 필요
지금은 리펙토링 중에 코드를 작성하는거니까 일단 테스트코드를 작성하지는 않음.
리펙토링을 마치고 모든 테스트코드가 다 돌아가면 ???

```java
private class Pair {
	private String from;
	private String to;

	Pair(String from, String to) {
		this.from = from;
		this.to = to;
	}

	public boolean equals(Object object) {
		Pair pair = (Pair) object;
		return from.equals(pair.from) && to.equals(pair.to);
	}

	public int hashCode() {
		return 0;
	}
}
```

0?? 이거도 일단 상수

환율 저장할 자료구조 필요

```java
class Bank {
	private Hashtable rates = new Hashtable();

	void addRate(String from, String to, int rate) {
		rates.put(new Pair(from, to), new Integer(rate));
	}

	int rate(String from, String to) {
		if (from.equals(to)) return 1;
		Integer rate = (Integer) rates.get(new Pair(from, to));
		return rate.intValue();
	}
}

public void testIdentityRate() {
	assertEquals(1, new Bank().rate("USD", "USD"));
}
```

- 필요할것이라 생각했던 인자를 빠르게 추가
- 코드와 테스트 사이 중복을 끄집어내기
- 오퍼레이션에 대한 가정을 검증하기 위해 테스트 추가
- 별도의 테스트 없이 private helper를 생성 (Pair)
- 

## 15장. 서로 다른 통화 더하기


```java
public void testMixedAddition() {
	Expression fiveBucks = Money.dollar(5);
	Expression tenFrancs = Money.franc(10);
	Bank bank = new Bank();
	bank.addRate("CHF", "USD", 2);

	Money result = bank.reduce(fiveBucks.plus(tenFrancs), "USD");
	assertEquals(Money.dollar(10), result);
}
```


```java
public void testMixedAddition() {
	Money fiveBucks = Money.dollar(5);
	Money tenFrancs = Money.franc(10);
	Bank bank = new Bank();
	bank.addRate("CHF", "USD", 2);

	Money result = bank.reduce(fiveBucks.plus(tenFrancs), "USD");
	assertEquals(Money.dollar(10), result);
// 실패

class Sum {
	public Money reduce(Bank bank, String to) {
		int amount = augend.amount + addend.amount;
		return new Money(amount, to);
	}

	public Money reduce(Bank bank, String to) {
		int amount = augend.reduce(bank, to).amount + addend.reduce(bank, to).amount;
		return new Money(amount, to);
	}
}

```

Expression이여야할 Money들을 수정한다.


```java
class Sum {
	Expression augend;
	Expression addend;

	Sum(Expression augend, Expression addend) {
		this.augend = augend;
		this.addend = addend;
	}
}


```

## 16장.

## 17장.