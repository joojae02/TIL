# Selenium

Selenium는 주로 웹앱을 테스트하는데 이용하는 프레임워크임
- webdriver라는 API를 통해 운영체제에 설치된 Chrome등의 브라우저를 제어
- JavaScript를 이용해 비동기적으로 혹은 뒤늦게 불러와지는 컨텐츠들을 가져올 수 있음

## 설치

개발을 리눅스 환경으로 진행할 예정

설치법 
```
pip install selenium
```
Selenium은 webdriver라는 것을 통해 디바이스에 설치된 브라우저들을 제어할 수 있다.  

### Chrome WebDriver
https://sites.google.com/a/chromium.org/chromedriver/downloads

예시
```
from selenium import webdriver

driver = webdriver.Chrome('/Users/beomi/Downloads/chromedriver')
driver.implicitly_wait(3)
// url에 접근한다.
driver.get('https://google.com')
```
사용되는 메소드   

- find_element_by_name('HTML_name')
- find_element_by_id('HTML_id')
- find_element_by_xpath('/html/body/some/xpath')
- find_element_by_css_selector('#css > div.selector')
- find_element_by_class_name('some_class_name')
- find_element_by_tag_name('h1')
- 등등

스크래핑해서 DB에 저장 후 사용하는 것도 좋아보임  
