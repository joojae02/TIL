
고스트 블로그를 이용하면서Announcement Bar라는 기능이 있다.

지난 한달 정도 이 기능을 사용했었는데
Google Search Console 에 
![](https://i.imgur.com/fjiCc3F.png)

해당 문제가 모든 페이지에 발생하였다.

## CLS 문제란??

>  CLS(Cumulative Layout Shift)는 누적 레이아웃 변경이다.
>  웹페이지를 보는 사용자에게 예상치 못한 화면 변환이 나타나는 빈도를 수치로 정량화한 것이다.

사실상 레이아웃의 변경이 많이 일어난다는 것이다.
이는 사용자 경험에 부정적인 영향을 미칠 가능성이 높아진다.
예로 뭐 로드 되면서 특정 요소의 위치가 바뀐다던지 등등.

## 원인??

이런 이슈가 발생하고 검색 결과 상위권에 위치하던 게시물들이 아에 표시가 되지 않는 등.....
그래서 해당 문제를 해결하려고 서칭 중

[Can we talk about the announcement bar?](https://www.spectralwebservices.com/blog/announcement-bar-a-review/)

이런 글을 읽게 되었고

![](https://i.imgur.com/HAgNsNl.png)

Announcement bar가 CLS 문제의 직접적인 원인이라는 것을 확인했다.

### 대체 방법??

그래도 Announcement bar 기능은 꽤 멋있다고.. 생각해서
대체 방법등을 찾아봤는데 결국은 사용하는 테마의 코드를 수정하는 방법 정도 밖에는 없는것 같다.

## 다른 원인들??

Announcement bar 외에도 다른 원인들이 있을 수 있는데

[Fixing CLS and other Page Experience issues in Ghost](https://www.spectralwebservices.com/blog/fixing-cls-issues/)

해당 글을 읽어보면
- Portal button problems
- Announcements Bar
- Resize the images you can't fix
- Add aspect ratio, length, and/or width.
- Fix your logo
- Add CloudFlare
- "Page too wide" and other dimensions issues
- Final thought: Less above the fold

뭐 이런 문제들이 있을 수 있다고 한다.

보면 대체로 화면에 접속하고 후에 변경되는 요소들의 문제여서
가능한 사진도 사이즈를 정해주고 하면 정상 범위 내의 수치가 나오지 않을까 싶다.

내 블로그는 Announcements Bar 추가 이외에는 건들인게 없어서..
바로 수정해줬다.