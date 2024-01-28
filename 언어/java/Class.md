# 1. 클래스
## 1) 객체 지향 프로그래밍의 특징
객체 지향 프로그램의 특징으로는 캡슐화, 상속 다형성이 있다.
<br>
### 캡슐화
외부의 잘못된 사용을 막기 위해 접근 제한자(Access Modifier)를 사용해 필드와 메소드의 사용 범위를 제한하여 외부로부터 보호한다. 
### 상속
상위 객체는 자기가 가지고 있는 필드와 메소드를 하위 객체에게 물려주어 하위 객체가 사용할 수 있도록 해준다.
### 다형성
1. 서로 상속 관계에 있는 클래스 사이에만 타입 변환 가능
2. 자식 > 부모 타입 변환은 생략 가능
3. 부모 > 자식 타입 변환은 생략 불가능

## 2) 클래스
인스턴스(객체)를 만들기 위한 설계도
<br>
### 선언
 작성 규칙
> 1. 첫 글자 대문자
> 2. 단어 연결 시 단어 첫 글자 대문자

 소스 파일 관련
> 1. 소스 파일의 이름은 "클래스이름.java"
> 2. 일반적으로는 소스 파일 하나당 클래스 한 개 (두 개 이상도 가능 / 가급적 하나 선언하기)
> 3. 두 개 이상 클래스를 선언했을 때는 소스 파일의 이름과 같은 클래스에만 public 붙이기 가능

방법
``` java
public class 클래스이름 {

}
```
### 객체 생성
new 연산자 사용
```java
클래스 var = new 클래스();
```

## 3) 클래스의 구조
```java
public class ClassName{
    //필드
    int fildName;
    
    //생성자
    ClasssName() { }
    
    //메소드
    void methodNmae() { }

}

```
### 1. 필드
변수의 형태와 같지만 변수라고 부르진 않는다.

### 2. 생성자
* new 연산자로 호출
* 객체 생성 시 초기화 담당.
* 메소드와 비슷하지만 클래스 이름으로 되어있고 리턴 타입이 없다.

#### this() 코드를 사용해 다른 생성자 호출

```java

public class Car {
 //필드
 
 Car() {
 }
 
 Car(String model) {
  this(model, "은색", 250);
 }
 
 Car(String model, String color) {
  this(model, color, 250);
 }
 
 //실제로 코드가 실행되는 
 Car(String model, String color, int maxSpeed) {
  this.model = model;
  this.color = color;
  this.maxSpeed = maxSpeed;
 }


}

```

#### 클래스 오버로딩 (아는 내용이므로 스킵)



### 3. 메소드
* 호출하면 중괄호 블록 내 코드 실행
* 메소드도 오버로딩 가능

### 4. 기타
1. this: 생성자 or 메소드의 매개 변수 이름이 필드랑 같을 때 사용한다. ("this.이름"은 필드, "이름"은 매개 변수)
2. static
   * static이 붙은 필드 or 메소드는 객체를 생성하지 않고 호출이 가능하다. (정적 필드는 보통 초기값을 준다.)
   * 정적 초기화 블록 : 클래스가 로딩될 때 바로 실행되는 코드 블록
     ```java
     static {
     }
     ```
   * 주의점
     + 인스턴스 필드 or 메소드 (static이 붙지 않은 것들)에 접근이 불가능 하다.
     + this 키워드를 사용할 수 없다.
     + 정적 메소드에서 인스턴스 멤버를 사용하려면 객체를 먼저 생성하고 참조 변수로 접근해야 한다.
     ```java
     static void Method() {
      ClassName obj = new ClassName();
      obj.field = 10; //필드 참조
      obj.method1(); //메소드 참조
     }
     ```
3. 싱글톤 (객체 하나만 생성하도록 만들고 싶을 때)
  ```java
  public class ClassName {
   //필드에 정적으로 인스턴스 하나 생성
   private static ClassName name = new ClassName;
   
   //생성자에 private를 붙여 외부에서 접근 금지
   private ClassName() { }
   
   //필드에 생성한 인스턴스를 가져오는 정적 메소드
   static ClassName getInstance() {
     return name;
   }
   
  }
  
  ```
  ```java
  //둘이 같은 인스턴스 참조
  ClassName var1 = ClassName.getInstance();
  ClassName var2 = ClassName.getInstance();
  ```
 4. final 필드 : 선언 시 초기화 or 생성자로 초기화 밖에 안 됨. 
 5. 상수 (static final) : 이름을 전부 대문자로 해야함.

### 5. 패키지
많은 양의 클래스를 저장 관리 하는 폴더와 같은 개념.

1. 선언
  ```java
  //패키지 이름은 전부 소문자가 관례
  package 상위패키지.하위패키지;
  
  public class ClassName {    }
  ```
  or
  인텔리j src폴더에 alt + insert -> 패키지 생성
  
2. import
   예시 1
   ```java
   public class Car {
     com.package.Class name = new com.package.Class();
   }
   ```
   
   예시2
   ```java
   import com.package.Class;    //or import com.package.*;
   
   public class ClassName {  
     Class name = new Class();
   }
   ```
   *** 주의사항 : 각기 다른 패키지에 이름이 같은 클래스가 있을 경우 풀 네임으로 기재 ***
 
### 6. 접근 제한자
* 종류
  1. public : 전부 공개
  2. protected : 같은 패키지 or 자식 클래스
  3. difault : 같은 패키지 (기본 값)
  4. private : 자기 자신만
* 생성자의 접근 제한 : 오버로딩된 생성자에 각각 다른 접근 제한자를 붙일 수 있음
* 필드/메소드의 접근 제한 : 다른 클래스에서 인스턴스로 생성했더라도 read / write 가 전부 안 됨

### 7. Getter, Setter
```java
//필드값은 private로
private int field;

//Getter
public int getField() {
  return field;
}

//Setter
public void setField(int field) {
  this.field = field;
}
```
 
