# self

## self 인자란?
클래스 내부에 정의된 함수인 메서드의 첫번째 인자는 반드시 self여야 한다.

```python
class Foo:
        def func1():
                print("function 1")
        def func2(self):
                print("function 2")
```
- `fun2()` 일때
    - 정상 추력
- `fun1()` 일때
    - 에러 
    ``` 
    TypeError: func1() takes 0 positional arguments but 1 was given 
    ```
<img src = "https://wikidocs.net/images/page/1742/6.08.png">  

- - - 

### 결론

- self는 객체의 인스턴스 그 자체이다.
- 객체 자기 자신을 참조하는 매개변수인 셈

다른 객체 지향 언어는 이를 명시 하지 않는다.  
파이썬은 클래스의 메소드를 정의할 때 self를 명시한다.

- **클래스 메소드 인자 첫번째에는 self를 쓰자!!**