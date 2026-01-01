
## N+1
Django ORM에서 외래 키 사용하게 되면
쉽게 볼 수 있는 N+1문제가 있다

```python
e = Entry.objects.get(id=5)

b = e.blog
```
 위와 같은 코드에서

처음 `e = Entry.objects.get(id=5)`에서 쿼리가 한번 날라가게 되고

`b = e.blog` 에서도 쿼리가 한번 날라가게된다

만양 `b = e.blog` 해당 코드를 루프에서 N번 사용하게 된다면??

쿼리가 N+1번 날라가게 된다.
당근 쿼리가 많은 것은 좋지 않다.

```python
e = Entry.objects.get(id=5).select_related("blog")

b = e.blog
```

이렇게 `select_related()`를 붙여준다면
처음 `e = Entry.objects.get(id=5).select_related("blog")` 때 `blog`를 join하여 쿼리를 날리고 캐시한다.

그러면 다음 `b = e.blog` 이때는 쿼리가 날라가지 않게 된다.

이를 이용해 쿼리의 수를 줄일 수 있지만
join 무조건 하게 되어 쿼리 성능이 저하될 수 있다.

## prefetch_related()

그래서 `select_related()` 대신 사용할 수 있는 방법이 `prefetch_related()`이다.

공식 문서에선
> Returns a `QuerySet` that will automatically retrieve, in a single batch, related objects for each of the specified lookups.

별도의 쿼리로 싱글 배치로 연관 객체들을 불러온다고 보면 된다.

`select_related()`가 Join을 통해 연관 객체를 가져온다면
`prefetch_related()` 는 쿼리를 하나 더 날려서 가져온다.

그래서 별도의 쿼리로 가져와서 Python에서 Join하게 된다.

```python
e = Entry.objects.get(id=5).prefetch_related("blog")

b = e.blog
```

이렇게 작성해도
`b = e.blog`에선 쿼리가 날라가지 않는다.

## 언제 쓰지.

기본적으로 둘다 N+1 문제의 경우 사용할 수 있다.

두 가지 중 어떤걸 사용할지 고민할때는
- Join을 해도 괜찮은지?
- 별도의 쿼리로 가져오는게 좋은지?
를 고려하자

최근엔 `select_related()`를 사용할 때
inner join order by filesort로 Slow 쿼리가 발생한 이슈가 있었다.

그래서 Join을 하지 않고 연관 테이블의 데이터를 가져올때
`prefetch_related()`로 변경하니 정상적으로 쿼리가 변경되었다.




