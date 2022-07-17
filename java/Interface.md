# 인터페이스
## 1. 기초지식
### 1. 역할
개발 코드와 객체가 서로 통신하는 접점 역할.
### 2. 선언
일반적인 선언
```java
  public interface Name { }
```
인텔리J에서의 선언: 원하는 위치에서 우클릭 > New > Java Class > 이름 적을 때 아래 Interface 선택
### 3. 구성 요소
```java
  public interface NewInterface {
    //상수 (일반적인 필드는 선언 x)
    public static final ~~~
    
    //인터페이스의 모든 메소드는 기본적으로 public 접근제한자를 가지므로 기술할 필요 x
    //추상 메소드 (실행 내용 x)
    void method(param);
    
    //디폴트메소드 (실행 내용 o)
    default void defauldMethod(param) { }
    
    //정적 메소드 (실행 내용 o)
    static void staticMethod(param) { }
  }
```

## 2. 구현
### 구현 방법
일반적인 구현
```java
  public class ClassName implements InterfaceName { 
    //필드
    public int field;
    
    //실체 메소드
    @Override
    public void method(param) { }
  }
```
인터페이스의 모든 추상 메소드들을 작성하지 않으면 구현 클래스는 자동으로 추상 클래스가 된다.
<br>
인텔리J에서는 구현클래스 선언 시
```java
  public class Imple3 implements NewInterface{
    
  }
```
까지만 입력하고 alt + Enter > Enter > ok 하면 자동으로 추상 메소드를 오버라이드 해준다.


### 익명 구현 클래스
한 번만 사용하고 버릴 때 클래스 선언하고 소스 파일 만드는 것은 비효율적 -> 선언 없이 객체 생성
```java
Interface myInterface = Interface(){
  //실체 메소드
}
```

### 다중 인터페이스 구현

implements 뒤에 콤마(,)로 구분
```java
public class MyClass implements Interface1, Interface2 {

}
```

## 3. 사용
구현한 클래스의 객체를 생성할 때 타입은 구현한 인터페이스로 해줘야 한다.
```java
Interface myInstance = new Class();
```
따라서 상속에서 배웠던 다형성이 그대로 적용된다.

## 4. 상속
인터페이스는 클래스와 다르게 다중 상속을 허용한다. (extends 뒤에 콤마(,)로 구분)
```java
public interface Interface1 extends Interface2, Interface3 { }
```
인터페이스 간의 상속 관계에서도 다형성이 적용된다.
<br>
부모 인터페이스의 추상 메소드를 오버라이딩 할 필요 없다. (구현하는 "클래스"만 오버라이딩 하면 됨)


## 5. 디폴트 메소드
### 필요성
나중에 인터페이스에 기능을 추가할 때 {추상 메소드 만들기 -> 구현 클래스에서 오버라이딩} 과정은 번거롭기 때문에 한 번에 디폴트 메소드로 기능 추가

### 상속 받았을 때
자식 인터페이스가 부모 인터페이스의 디폴트 메소드를 오버라이딩 할 때 자식 인터페이스를 구현하는 클래스는 오버라이딩된 디폴트 메소드를 호출하게 된다.
```java
public interface Interface1 {
  public default void method1() { 
  System.out.println("1");
  }
}

public interface Interface2 extends Interface1 {
  @Override
  public default void method1() { 
    System.out.println("2");
  }
}

public class Class1 implements Interface2 { }

Interface2 var = new Class1();
var.method1(); //출력 결과: 2
```

<br>
추상 메소드로 오버라이딩 할 수도 있다.

```java
public interface Interface1 {
  public default void method1() { }
}

public interface Interface2 extends Interface1 {
  @Override
  public void method1();
}
```
