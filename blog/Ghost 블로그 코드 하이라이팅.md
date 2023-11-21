
## 코드 하이라이팅 넣기
> **우선 모든 설정은 Code injection에서!!**

간단하게만 설명하면

Code injection > Site Header 에
```html
<link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/prism/1.29.0/themes/prism-tomorrow.min.css" integrity="sha512-vswe+cgvic/XBoF1OcM/TeJ2FW0OofqAVdCZiEYkd6dwGXthvkSFWOoGGJgS2CW70VK5dQM5Oh+7ne47s74VTg==" crossorigin="anonymous" referrerpolicy="no-referrer" />
```
Code injection > Site Footer 에
```html
<script src="https://cdnjs.cloudflare.com/ajax/libs/prism/1.29.0/components/prism-core.min.js" integrity="sha512-9khQRAUBYEJDCDVP2yw3LRUQvjJ0Pjx0EShmaQjcHa6AXiOv6qHQu9lCAIR8O+/D8FtaCoJ2c0Tf9Xo7hYH01Q==" crossorigin="anonymous" referrerpolicy="no-referrer"></script>
<script src="https://cdnjs.cloudflare.com/ajax/libs/prism/1.29.0/plugins/autoloader/prism-autoloader.min.js" integrity="sha512-SkmBfuA2hqjzEVpmnMt/LINrjop3GKWqsuLSSB3e7iBmYK7JuWw4ldmmxwD9mdm2IRTTi0OxSAfEGvgEi0i2Kw==" crossorigin="anonymous" referrerpolicy="no-referrer"></script>
```

이렇게만 넣어주면 된다

## 부연 설명..

우선 사용한 것은 `Prism`으로 다양한 Syntax highlighter 중 하나이다

대충 여러 장점이 있는데
1. 용량이 굉장히 작다.
2. class를 상속받기 때문에 body에 class를 지정하는 식으로 기본 언어를 지정할 수 있다.
3. 지원하는 언어가 많아서 티스토리 코드블럭에서 지원하지 않는 언어들도 사용할 수 있다.
4. 정규 표현식만 안다면 새로운 언어를 만들거나, 기존 언어를 수정할 수도 있다.
5. 플러그인을 통해 다양한 기능들을 지원한다.

이걸 적용하는 방법에는 
[다운로드 페이지](https://prismjs.com/download.html)
여기에서 직접 다운받아서 넣는 방법이 있고

오토 로더를 사용해서 자동으로 넣어주는 방법이 있다

당근 후자가 편하다

그리고 `cdnjs`,  `jsDelivr`, `UNPKG` 뭐 이런 PrismJS를 제공해주는 것들이 있는데 그냥 취향껏 사용하면 된다

난 cdnjs를 이용해서
[cdnjs/prism](https://cdnjs.com/libraries/prism)
여기서 최신 버전을확인한다음 
```html
<link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/prism/1.29.0/themes/prism-tomorrow.min.css" integrity="sha512-vswe+cgvic/XBoF1OcM/TeJ2FW0OofqAVdCZiEYkd6dwGXthvkSFWOoGGJgS2CW70VK5dQM5Oh+7ne47s74VTg==" crossorigin="anonymous" referrerpolicy="no-referrer" />
```
해당 버전에 맞는 `prism-tomorrow.min.css`를 찾아서 바꿔주면된다~

현재 1.29.0 버전이 최신이여서 요걸로 설정해줬다


### 사실 모든 설명은 여기에.. 잘 나와있다
[code-snippets-in-ghost](https://ghost.org/tutorials/code-snippets-in-ghost/)