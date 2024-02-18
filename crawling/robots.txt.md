# robots.txt

robots.txt 파일은 크롤러가 사이트에서 액세스할 수 있는 URL을 검색엔진 크롤러에 알려 준다.

## robots.txt 위치
반드시 루트 디렉터리에 위치해야하며 텍스트 파일로 접근이 가능해야 함.
- https://kbland.kr/robots.txt

## robots.txt 규칙

### user-agent 
- 규칙이 적용된느 검색엔진 크롤러의 이름 지정
```
//Googlebot에 규칙 적용
User-agent: Googlebot
Disallow: /

//모든 크롤러에 규칙 적용
User-agent: *
Disallow: /
```
### disallow 
- 크롤링하지 않도록 하려는 루트 도메인 관련 디렉터리 또는 페이지
### allow 
- 크롤링할 수 있는 루트 도메인 관련 디렉터리 또는 페이지
### sitemap
- 웹사이트의 사이트맵 위치
- 사이트맵 URL은 정규화된 URL
- 사이트의 파일 구조를 쉽게 파악 가능
```
Sitemap: https://kbland.kr/sitemap_index.xml
User-agent: *
Allow: /
```