# None

## 언제 None을 반환할까

```python
def method_1():
    return

def method_2():
    return None

def method_3():
    a = 1

print(main_case_1())
print(main_case_2())
print(main_case_3())

# 결과 값

None
None
None

```
- return None / return / x
- 모두 결과는 None
- - -
## 어떤 값을 찾을 때 - return None
- 리턴 값을 None으로 명시
- 찾고자 하는 값이 없음을 표현
```python
    def find_something() :
        if a in list:
            return a
        return None
```
## 특정 상황이 벌어지면 종료 - return
```python
    def find_something() :
        if a in list:
            a = 1
            return
        return 
```

