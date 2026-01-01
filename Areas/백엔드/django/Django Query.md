
Django에서 데이터 모델을 생성한 후
객체의 CRUD에 대한 추상화 API를 제공한다.

공식 문서의 예시
```python
from datetime import date

from django.db import models

class Blog(models.Model):
    name = models.CharField(max_length=100)
    tagline = models.TextField()

    def __str__(self):
        return self.name

class Author(models.Model):
    name = models.CharField(max_length=200)
    email = models.EmailField()

    def __str__(self):
        return self.name

class Entry(models.Model):
    blog = models.ForeignKey(Blog, on_delete=models.CASCADE)
    headline = models.CharField(max_length=255)
    body_text = models.TextField()
    pub_date = models.DateField()
    mod_date = models.DateField(default=date.today)
    authors = models.ManyToManyField(Author)
    number_of_comments = models.IntegerField(default=0)
    number_of_pingbacks = models.IntegerField(default=0)
    rating = models.IntegerField(default=5)

    def __str__(self):
		return self.headline
```

## 객체 생성

Django의 모델은 데이터베이스의 테이블을 나타내고
해당 클래스의 인스턴스는 데이터베이스 테이블의 레코드가 된다.

따라서 객체를 생성해 데이터베이스에 실제로 저장하려면

```python
test_blog = Blog(name="Test Blog", tagline="test test.")
test_blog.save()
```

위와 같이 객체를 생성한 후 `save()`를 사용하여 저장할 수 있다.

또한 한번에 객체를 생성 저장하기 위해선
```python
test_blog = Blog.objects.create(name="Test Blog", tagline="test test.")
```
위와 같이 사용한다.

## 객체 업데이트

```python
test_blog.name = "New Test"
test_blog.save()
```

업데이트는 객체의 필드를 바꿔준뒤 `save()`해주면 된다.

## 객체 검색
```python
Blog.objects.filter(name="Test Blog")
```

해당 Select가 이뤄지는 과정엔
QuerySet 객체가 존재한다.

QuerySet이란 간단하게 말해 모델의 객체 목록이다.

보통 `filter()`, `all()`, `get()` 등의 메서드들과 같이 사용하게 된다.

`filter()`는 SQL의 WHERE 절을 생각하면 편한다.

### 체인 필터

그래서 원하는 값을 가져오기 위해 여러번의 체이닝을 통해 원하는 SQL과 같은 효과를 낼 수 있다.

```python
Blog.objects.filter(name="Test Blog").exclude(tagline="Test Tagline")
```

데이터베이스의 항목중 `name`이 Test Blog이고 `tagLine`이 Test Tagline이 아닌 값을 가져오게 된다.


### Lazy QuerySet

```python
blog = Blog.objects.filter(name="Test Blog")
blog = Blog.objects.filter(name="Test")
blog = Blog.objects.filter(name="Blog")

print(blog)
```

위와 같은 코드를 작성하게 된다면
쿼리가 3번 날라갈것 같지만 print 되는 시점에 한번 날라가게 된다

해당 쿼리셋에 대한 여러 메서드들은 공식문서를 확인하자

## Field lookups

lookups는 SQL `WHERE` 절 의 조건을 설정할 수 있게 해준다
`field__lookuptype=value`
필드 뒤의 언더바 `__` 2개를 추가해서 사용한다.

```python
Entry.objects.filter(pub_date__lte="2006-01-01")
```

```sql
SELECT * FROM blog_entry WHERE pub_date <= '2006-01-01';
```

다음과 같이 대응된다.

### Foreign key Lookups

필드로 Foreign key를 등록한 경우
join 을 통한 Select가 필요하게 된다.

```python
Entry.objects.filter(blog__name="Beatles Blog")
```
위와 같이 사용하면

`Entry`들 중 `Entry.blog`의 `name`이 특정 값인 `Entry`를 가져온다.
실제 쿼리를 보면 `Blog`테이블을 join하여 값을 찾게 된다

## 객체 삭제

```python
blog.delete()
```

위 코드 처럼 삭제하고 싶은 객체에 `delete()` 메서드를 실행하면 된다.

## 정리하자면.

Django 에서는 모델을 정의해 데이터베이스의 테이블을 만들고
추상화 API를 이용해 쿼리문을 작성할 수 있다.

따라서 간단하게 SQL문을 사용할 수 있다.

하지만 Foreign Key Lookups를 사용하다보면
유명한 N+1 문제 등이 생길 수 있고

실제 SQL문을 작성하는 것만큼 자유롭게 SQL문을 작성할 수 없다.


### 참고
- https://docs.djangoproject.com/en/5.0/topics/db/queries/
- https://docs.djangoproject.com/en/5.0/ref/models/querysets/#django.db.models.query.QuerySet

