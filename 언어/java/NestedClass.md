# 중첩 클래스 & 인터페이스

## 중첩 클래스
### 맴버 클래스
클래스의 맴버로 선언되는 클래스
1. 인스턴스 멤버 클래스: static 키워드가 없음, 안에 정적 멤버 선언 불가능.
```java
public class Outer {
  class Inner {
    Inner() { }
    
    int field1;
    static int field2; //정적 필드 불가능
    
    void method1() { }
    static void method2() { } //정적 메소드 불가능
  }
}
```
  사용: Outter 클래스의 객체를 먼저 생성하고 B의 객체를 선언해야한다.
```java
Outter out = new Outter();
Outter.Inner in = out.new Inner();
```
2. 정적 멤버 클래스: static 키워드가 있음, 모든 종류의 필드와 메소드 선언 가능.
```java
public class Outer {
  static class Inner {
    Inner() { }
    
    int field1;
    static int field2;
    
    void method1() { }
    static void method2() { }
  }
}
```
  사용: Outter 클래스의 객체를 먼저 생성할 필요가 없다. (바로 생성 가능)
```java
Outter.Inner in = new Outter.Inner
```


### 로컬 클래스
메소드 내에서 선언되는 클래스, 정적 멤버 선언x, 접근 제한자x
```java
public class Outter {
  
  void method() {
    class Inner {
      Inner() { }
      
      int field;
      static int field2; //정적 필드 불가능
      
      void method1() { }
      static void method2() { } //정적 메소드 불가능
    }
    Inner in = new Inner();
    ~~~~~
  }
}
```

## 접근 제한
### 멤버 클래스(정적 vs 동적)
1. 멤버 클래스에 접근
```java
public class Outter {
  class Inner_d { }
  static class Inner_s { }
  
  Inner_d field1 = new Inner_d();
  Inner_s field2 = new Inner_s();
  
  static Inner_d field3 = new Inner_d(); //안 됨
  static Inner_s field4 = new Inner_s();
  
  void method1() {
   Inner_d var1 = new Inner_d();
   Inner_s var2 = new Inner_s();
  }
  
  static void method2() {
   Inner_d var3 = new Inner_d(); //안 됨
   Inner_s var4 = new Inner_s();
  }
}
```
2. 멤버 클래스에서 접근
```java
public class Outter {
 int field1;
 void method1() { }
  
 static int field2;
 static void method2() { }
  
 class Inner_d {
  void method() {
   filed1 = 10;
   method1();
    
   field2 = 10;
   method2();
  }
 }
  
 static class Inner_s {
   filed1 = 10; //안 됨
   method1(); //안 
   
   field2 = 10;
   method2();
 }
  
}
```

### 로컬 클래스
로컬 클래스에서는 바깥 클래스의 필드나 메소드를 제한없이 사용 가능.   
그러나 로컬 클래스를 감싸는 메소드의 매개 변수, 로컬 변수를 사용하면 문제가 발생.(메소드는 실행되고 나면 메모리에서 사라지니까)   
따라서 컴파일러에서 자동으로 매개 변수와 로컬 변수를 메소드가 실행될 때 로컬 클래스에 복사함.   
복사 이후 바깥 메소드에서 값을 바꾸면 안되기 때문에 final 키워드를 붙임.   
안 붙여도 되지만 붙이지 않아도 final 특성이 적용됨.   
final 키워드를 붙였을 경우 로컬 클래스의 메소드의 로컬 변수로, final 키워드를 붙이지 않았을 경우 로컬 클래스의 필드로 복사가 된다.

## 바깥 클래스 참조
중첩 클래스 내부에서 바깥 클래스의 맴버에 접근하는 방법
```java
Outter.this.field
Outter.this.method();
```

## 중첩 인터페이스
클래스의 멤버로 선언된 인터페이스. 주로 UI 프로그래밍에 사용.   
중첩 인터페이스
```java
public class Button {
  OnClickListener listener;
  
  void setOnClickListener(OnClickListener listener) {
    this.listener = listener;
  }
  
  void click() {
    listener.onClick();
  }
  
  interface OnClickListener {
   void onClick(); 
  }
}
```
구현 클래스
```java
public class CallListener implements Button.OnClickListener {
   @Override
   public void onClick() {
   System.out.println("메세지를 보냅니다"); 
  }
}
```
사용
```java
public class Example {
 public static void main(String[] args) {
   Button btn = new Button;
   
   btn.setonClickListener(new CallListener());
   btn.touch(); //메세지를 보냅니다.
 }
}
```

## 익명 객체

선언 템플릿
```
부모클래스 [변수명] = new 부모클래스(매개) {
  //필드
  //메소드
}
```
자동으로 상속되는 느낌   
예시
```java
class Parent {
  void parentMethod() { }
}

class A {
   parent field = new parent() {
    int childField;
     void childMethod() { }
     @Override
     void parentMethod() { }
   }
}
```
매개변수 내부에서도 선언과 동시에 사용 가능.
```java
class A {
  void method1(Parent parent) { }
  
  void method2() {
    method1(
      new Parent() {
        int childField;
        void childMethod() { }
        @Override
        void parentMethod() { }
      }
    );
  }
}
```
다형성에서 설명한 것 같이 익명 자식 객체는 부모 타입 변수이므로 부모 클래스에 선언된 부분만 접근이 가능하다.
```java
class Parent {
  void parentMethod() { }
}

class A {
   parent field = new parent() {
    int childField;
     void childMethod() { }
     @Override
     void parentMethod() { }
   }
   
   field.childField = 1; //x
   field.childMethod(); //x
   field.parentMethod();
}
```

