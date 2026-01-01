
## **1. 컴프리헨션 (Comprehension) 활용법**

컴프리헨션은 반복문을 사용하지 않고도 List, Dict, Set과 같은 자료구조를 매우 간결하게 생성할 수 있는 기능이다.
for 루프를 한 줄로 압축한 형태로, 가독성과 성능 면에서 이점을 가진다.

### 리스트 컴프리헨션 (List Comprehension)
- **리스트 컴프리헨션 (List Comprehension)** 가장 일반적으로 사용되는 컴프리헨션으로, 기존 리스트를 기반으로 새로운 리스트를 생성한다.
    - **기본 구문:** `[표현식 for 항목 in 반복 가능한 객체 if 조건]`       
- **예시:** 0부터 9까지의 숫자 중 짝수만 제곱하여 새로운 리스트 만들기
```python
# 기본 for문
squares = []
for i in range(10):
	if i % 2 == 0:
		squares.append(i * i)
print(squares) # [0, 4, 16, 36, 64]

# 리스트 컴프리헨션 활용
squares_comp = [i * i for i in range(10) if i % 2 == 0]
print(squares_comp) # [0, 4, 16, 36, 64]
```
	
### 딕셔너리 컴프리헨션 (Dictionary Comprehension) 
- **딕셔너리 컴프리헨션 (Dictionary Comprehension)** 리스트 컴프리헨션과 유사하게 한 줄로 딕셔너리를 생성할 수 있다.
    - **기본 구문:** `{키_표현식: 값_표현식 for 항목 in 반복 가능한 객체 if 조건}`
    - **예시:** 단어 리스트를 사용하여 {단어: 단어 길이} 형태의 딕셔너리 만들기
    
```python
words = ['apple', 'banana', 'cherry']
word_lengths = {word: len(word) for word in words}
print(word_lengths) # {'apple': 5, 'banana': 6, 'cherry': 6}
```

### 셋 컴프리헨션 (Set Comprehension) 
- **셋 컴프리헨션 (Set Comprehension)** 중복을 허용하지 않는 셋(Set)을 생성할 때 사용한다.
    - **기본 구문:** `{표현식 for 항목 in 반복 가능한 객체 if 조건}`
- **예시:** 리스트에 있는 숫자들 중 고유한 셋 만들기
```python
numbers = [1, 2, 2, 3, 4, 5, 5]
odd_squares = {x for x in numbers if x % 2 != 0}
print(odd_squares) # {1, 2, 3, 4, 5}
```

### 속도 차이?

일반적인 상황에서 List comprehension 의 동작이 유의미하게 빠르다.
아래 예제를 통해 간단하게 확인이 가능하다.
> 정확히 설명하자면 인터프리터 모드인 경우에 유의미하게 빠르다.

```python
import timeit

# 테스트할 코드
setup_code = "numbers = range(10000000)"
for_loop_code = """
squared_numbers = []
for x in numbers:
    squared_numbers.append(x**2)
"""
comprehension_code = "squared_numbers = [x**2 for x in numbers]"

# 실행 시간 측정
for_loop_time = timeit.timeit(stmt=for_loop_code, setup=setup_code, number=1)
comprehension_time = timeit.timeit(stmt=comprehension_code, setup=setup_code, number=1)

print(f"For loop: {for_loop_time:.6f} seconds")
print(f"List comprehension: {comprehension_time:.6f} seconds")
```

```bash
For loop: 0.271319 seconds
List comprehension: 0.245245 seconds
```

---

## **2. 언패킹(Unpacking)과 제너레이터(Generator)**

### 언패킹 (Unpacking) 
- **언패킹 (Unpacking)** 언패킹은 튜플이나 리스트 같은 시퀀스 자료형의 요소들을 여러 변수에 한 번에 할당하는 기능이다. 
- **예시:**
```Python
# 기본 언패킹
a, b, c = (1, 2, 3)
print(a, b, c) # 1 2 3

# *를 이용한 언패킹 (나머지 요소들을 리스트로 받기)
head, *body, tail = [10, 20, 30, 40, 50]
print(head)  # 10
print(body)  # [20, 30, 40]
print(tail)  # 50
```

### 제너레이터 (Generator) 
- **제너레이터 (Generator)** 제너레이터는 모든 값을 메모리에 올리지 않고, 필요할 때마다 값을 하나씩 생성하여 반환하는 **이터레이터(iterator)**를 만드는 기능이다. 
- 대용량 데이터를 처리할 때 메모리 효율성을 극대화할 수 있다. 함수 내에서 `yield` 키워드를 사용한다.
    - **특징:**
        - `yield`를 통해 값을 하나씩 반환하고, 함수의 상태는 그대로 유지된다.
        - 다음에 `next()` 함수로 호출되면 이전에 멈췄던 지점부터 다시 실행된다.
- **예시:** 1부터 n까지의 숫자를 생성하는 제너레이터
```Python
def number_generator(n):
	print("Generator starts")
	for i in range(1, n + 1):
		yield i
		print(f"{i} yielded")

my_gen = number_generator(3)
print(next(my_gen)) # Generator starts, 1 출력
print(next(my_gen)) # 1 yielded, 2 출력
print(next(my_gen)) # 2 yielded, 3 출력
```


---

## **3. 매직 메서드 (Magic Methods)**

매직 메서드(또는 특별 메서드, Special Methods)는 파이썬 클래스 내에서 `__` (더블 언더스코어)로 시작하고 끝나는 특별한 이름의 메서드이다. 
이 메서드들은 `+`, `len()`, `print()`와 같은 파이썬의 내장 연산이나 함수가 해당 객체에 사용될 때 자동으로 호출된다.

- `__init__(self, *args, **kwargs)`
	- 클래스의 **생성자(constructor)** 메소드이다.
- `__str__(self)`
    - `print()` 함수나 `str()` 내장 함수를 사용하여 객체를 **문자열로 변환**할 때 호출된다.
    - 주로 사용자가 보기 쉬운, **비공식적인** 문자열 표현을 반환하는 데 사용된다.
- `__repr__(self)`
    - `repr()` 내장 함수를 호출할 때나, 인터프리터에서 객체를 그냥 출력할 때 호출된다.
    - 주로 개발자가 디버깅 목적으로 사용하는, 객체를 **명확하게 식별**할 수 있는 **공식적인** 문자열 표현을 반환하는 데 사용된다. `eval(repr(obj)) == obj`가 성립하는 것을 목표로 한다.
- `__eq__(self, other)`
    - `==` 연산자를 사용하여 두 객체의 **내용이 같은지** 비교할 때 호출된다.
    - 이 메서드를 구현하지 않으면, 기본적으로 두 객체의 메모리 주소를 비교한다.
- **예시:**
```Python
class Person:
	def __init__(self, name, age):
		self.name = name
		self.age = age

	def __str__(self):
		return f"{self.name}, {self.age}살"

	def __repr__(self):
		return f"Person('{self.name}', {self.age})"

	def __eq__(self, other):
		return self.name == other.name and self.age == other.age

p1 = Person("Alice", 30)
p2 = Person("Alice", 30)
p3 = Person("Bob", 25)

print(p1)          # __str__ 호출 -> Alice, 30살
print(str(p1))     # __str__ 호출 -> Alice, 30살
print(repr(p1))    # __repr__ 호출 -> Person('Alice', 30)
print(p1 == p2)    # __eq__ 호출 -> True
print(p1 == p3)    # __eq__ 호출 -> False
```
    

---

## **4. 데코레이터 (Decorator)**

데코레이터는 기존 함수의 코드를 수정하지 않으면서, 함수에 **새로운 기능을 추가하거나 수정**할 때 사용하는 강력한 디자인 패턴이다.

함수를 인자로 받아서, 새로운 기능이 추가된 또 다른 함수를 반환하는 형태로 동작한다.
- 주로 로깅, 실행 시간 측정, 접근 제어 등 AOP(관점 지향 프로그래밍)에 유용하게 사용된다.
- **기본 구조:**
```Python
def decorator_function(original_function):
	def wrapper_function(*args, **kwargs):
		# --- 함수 실행 전 처리 ---
		print(f"{original_function.__name__} 함수 실행 전입니다.")

		result = original_function(*args, **kwargs) # 원래 함수 실행

		# --- 함수 실행 후 처리 ---
		print(f"{original_function.__name__} 함수 실행 후입니다.")
		return result
	return wrapper_function
```
- **사용법 (`@` 구문):** 기능을 추가하고 싶은 함수 위에 `@데코레이터_이름`을 붙여준다
- **예시:** 함수의 실행 시간을 측정하는 데코레이터
```Python
import time

def measure_time(func):
	def wrapper(*args, **kwargs):
		start_time = time.time()
		result = func(*args, **kwargs)
		end_time = time.time()
		print(f"'{func.__name__}' 실행 시간: {end_time - start_time:.4f}초")
		return result
	return wrapper

@measure_time
def slow_function(delay):
	print(f"{delay}초 대기 시작...")
	time.sleep(delay)
	print("대기 완료!")
	return "완료"

slow_function(2)

```
    
**실행 결과:**
```
2초 대기 시작...
대기 완료!
'slow_function' 실행 시간: 2.0021초
```

## 출처

- https://docs.python.org/ko/3.13/tutorial/controlflow.html#unpacking-argument-lists
- https://docs.python.org/ko/3.13/reference/datamodel.html#special-method-names
- https://wikidocs.net/192021
- https://docs.python.org/ko/3.13/tutorial/datastructures.html#list-comprehensions
- https://docs.python.org/ko/3.13/tutorial/classes.html#iterators
- https://docs.python.org/ko/3.13/tutorial/classes.html#generators