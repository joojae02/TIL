# 예외 처리
## 예외의 종류
### 일반 예외 (컴파일러 체크 예외)
소스를 컴파일 하는 과정에서 예외 처리 코드가 필요한지 검사하고 예외 처리 코드가 없다면 컴파일 오류를 발생시킨다.   
java.lang.Exception 클래스를 상속받는다.
### 실행 예외
자바 컴파일러가 체크를 하지 않기 때문에 개발자의 경험에 의해서 예외 처리 코드를 집어넣어야한다.
java.lang.RuntimeException 클래스를 상속받는다.
1. NullPointerException: null값을 갖는 참조변수로 객체에 접근할 때   
예시
```java
String data = null;
System.out.println(data.toString()); //null값을 갖는 객체에 접근
```
2. ArrayIndexOutOfBoundsException: 배열의 인덱스 범위를 초과하여 사용할 경우   
예시
```java
int[] arr = new int[3]; //arr의 인덱스는 0~2
arr[3] = 1; //arr의 3번 인덱스에 접근했기 때문에 오류
```
3. NumberFormatException: 문자열을 숫자로 변환하려 할 때, 숫자로 변환될 수 없는 문자가 포함되어 있을 때   
예시
```java
String data1 = "100";
String data2 = "a100";

int value1 = Integer.parseInt(data1); //(o)
int value2 = Integer.parseInt(data2); //a는 정수로 바꿀 수 없음
```
4. ClassCastException: 다형성을 배울 때 강제 타입 변환은 이미 자동으로 타입 변환된 자식 객체의 타입을 다시 자기 자신으로 돌릴 때만 가능하다고 했다. 이를 어길 시 발생하는 예외

## 예외의 처리
예외 처리 코드는 try-catch-finally 블록을 이용  
### 기본 틀
```java
try {
 //예외가 발생할 수 있는 코드 (예외가 발생할 경우 catch문의 블록 실행)
} catch(Exception1 | Exception2 e) { //(Exeption = 예외 클래스)
 //예외 처리 (여러 개 사용 가능)
} catch(Exception e) {
  
} finally {
 //항상 실행 (예외 처리가 안 되어도)
}
```
### 다중 catch
상위 예외 클래스가 하위 예외 클래스보다 아래에 위치해야 한다.   
  느슨한 그물망(하위 예외 클래스)부터 하나 씩 예외를 잡아야지 처음 부터 너무 촘촘한 그물망(상위 예외 클래스)로 예외를 잡으면 다양한 예외 처리가 불가능하다.   
  예시
  ```java
  try {
    
  } catch (Exception e) {
    //Exception 클래스가 모든 예제를 잡아먹음
  } catch (ArrayIndexOutOfBoundsException e) {
    
  }
  ```
  해결
  ```java
  try {
    
  } catch (ArrayIndexOutOfBoundsException e) {
   //array~~ 클래스가 놓친 예외를 
  } catch (Exception e) {
    //Exception 클래스가 마저 잡아주는 구조
  }
  ```

### 멀티 catch
한 catch 블록에 여러 개의 예외를 처리하기 위한 방법
```java
try {
  
} catch (Exception1 | Exception2 e) {
  
}
```

### 파일 입출력
원래 자바에선 파일을 열었으면 닫아야 했음 하지만 try-with-resources 구문을 이용하면 안 닫아도 됨
```java
try(FileInputSystem fis - new FileInputStream("file.txt")) {
  
} catch(IOException e) {
  
}
```
try에서 예외가 발생하면 일단 close()문이 실행되고 catch문이 실행되는 구조. 만일 파일이 여러 개라면
```java
try(
  FileInputSystem fis1 = new FileInputSystem("file1.txt");
  FileInputSystem fis2 = new FileInputSystem("file2.txt");
  ) {
  
} catch(IOException e) {
  
}
```
의 구조로 실행하면 된다. 이를 사용하기 위해서는 리소스 객체가 AoutoCloseable 인터페이스를 구현해야한다.   
구현 여부를 확인하려면 API 도큐먼트에서 AoutoCloseable인터페이스를 찾아 All Known Implementing Classes:를 보면 구현하는 클래스들을 볼 수 있다.

## 예외 떠넘기기
메소드 내부에서 예외가 발생할 수 있는 코드를 작성할 때 경우에 따라서 메소드를 호출한 곳으로 예외를 떠넘길 수 있다.
```java
void method1(int param) throws Exception1, Exception2 {
}
```
각각 맞는 예외를 떠넘길 수 있지만 thorws Exception으로 모든 예외를 떠넘길 수 있다. (이런 예외가 생길 수 있다 라고 알려주는 느낌..?)   
throws 키워드가 붙은 메소드는 무조건 try 블록 안에서만 실행이 가능하다.   
물론 throws 키워드가 붙은 메소드를 실행하는 메소드에도 throws를 붙일 수 있고 마지막까지도 try-catch문으로 잡아주지 않는다면 콘솔창에 뜨는 경고 방식으로 컴파일러가 예외를 처리한다.

## 사용자 정의 예외
### 예외 선언
일반 예외로 선언하려면 Exception 상속, 실행 예외로 선언할 경우에는 RuntimeException 상속
```java
public class XXXException extends Exception {
  public XXXException() { }
  public XXXException(String message) { super(message); }
}
```
사용자 정의 예외에도 필드, 메소드, 생성자 등을 선언할 수 있지만 대부분 생성자 선언만을 포함.   
생성자는 예제 코드와 같이 매개 변수가 없는 생성자 하나, String 타입의 매개 변수를 갖는 생성자 하나가 보통이다.   

### 예외 실행
```java
throw new XXXException();
throw new XXXException("메시지");
```
예외 떠넘기기와 합쳐서 보면
```java
void method1(int param) throws XXXException {
  if( ) {
    throw new XXXException("메시지"); //호출부의 try-catch문이 처리해야할 부분 
  }
}
```

## 예외 정보 얻기
catch문에서 매개변수(?)로 사용되는 예외의 객체를 통해 예외의 정보를 얻을 수 있다.   
가장 자주 사용되는 메소드는 getMessage()와 printStackTrace()이다.   
사용 예제
```java
try {
  
} catch (Exception e) {
  String message = e.getMessage(); //예외의 Message 얻기
  
  e.printStackTrace(); //예외의 발생 경로 
}
```
