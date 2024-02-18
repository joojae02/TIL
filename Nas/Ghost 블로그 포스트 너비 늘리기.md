
## 포스트 넓이..

기존에 블로그 포스트에서 글이 조금만 길어도 
![](https://i.imgur.com/S1ikjC8.png)

이런식으로 크롤로 바뀌는 점이 있었는데

내가 느끼기에 불편하고 포스트의 넓이가 너무 좁다고 느껴졌다

그래서! 늘리기로 결정

난 도커허브에서 바로 블로그를 띄웠기 때문에
코드 상으로 테마를 수정하거나 추가하는 일은 좀 귀찮다고 느껴져서
최대한 코드 인젝션으로 해결하려고 했다

그래서 찾은 내용는 `.gh-canvas`를 바꿔주면 된다
Code injection > Site Header 에 아래 내용을 추가해주면 된다
```html
<style type="text/css">
    .gh-canvas {
        display: grid;
        grid-template-columns: [full-start] minmax(max(4vmin,20px),auto) [wide-start] minmax(auto,240px) [main-start] min(1024px,calc(100% - max(8vmin, 40px))) [main-end] minmax(auto,240px) [wide-end] minmax(max(4vmin,20px),auto) [full-end];
    }
</style>
```

요기서 
```
[main-start] min(1024px,calc(100% - max(8vmin, 40px)))
```

요기 min 뒤의 1024를 원하는 값으로 바꿔주면 된다.

![](https://i.imgur.com/Wo6YZqb.png)

하면 이런식으로 넓이가 늘어난걸 확인할 수 있다

근데 넓이를 임의로 늘리면 가독성이 떨어질 수도 있으니
적당한 값으로 넣어줘야 될것 같다