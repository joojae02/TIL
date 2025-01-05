## Django란?
> **The web framework for perfectionists with deadlines.**

장고 홈페이지 메인에 적혀있는 문구이다.

간단하게 파이썬 기반 웹 프레임워크이다.
다른 프레임워크들에 비해 입문하기 쉬운 파이썬과 높은 생산성으로 유명하다.

## 특징??

다른 프레임워크들과의 차이점으로
- MTV 패턴
- 자체 ORM
- Admin 제공

다른 프레임워크에서 많이 사용하는 MVC 패턴과 비교하면
![](https://developer.mozilla.org/ko/docs/Learn/Server-side/Django/Introduction/basic-django.png)
Model(Model)
- 똑같이 데이터, DB관련 매핑을 해준다고 생각하면 된다.

View(Template)
- 실제로 화면을 보여주는 인터페이스

Controller(View)
- Model과 View를 이어주는 동작되는 함수들이 정의된다.

간단하게 이렇게 매칭된다고 보면 된다.

## DRF(Django Rest Framework)란?

> RESTful API 서버를 쉽게 구축할 수 있도록 도와주는 오픈소스 라이브러리

Django는 프론트, 백 모두 할 수 있는 형태의 프레임워크이다.
그치만 DRF를 이용하면 간단하게 api 서버 형태로 구현이 가능하다.

기본적으로 View를 컨트롤러처럼 url에 등록시켜 사용하는 방식이다.

### Serializer
![](https://i.imgur.com/VRGLtcB.png)


여기서 중요한 것이 직렬화인데
객체를 바이트 스트림으로 바꿔주는 것이다.

간단하게 객체를 JSON형태로 바꿔준다고 생각해도 좋다.

DRF는 이를 모델별 Serializer를 구현할 수 있게 지원한다.


## 설치

우선 파이썬 가상 환경을 만들어준다.
```bash
$ python3 -m venv venv
또는
$ virtualenv venv -p python3.11
```
윗 명령어는 현재 사용하는 파이썬 버전에 맞게 생성이된다.
아래 명령어는 특정 버전의 파이썬으로 생성할 수 있다.

다음으로는 해당 가상환경을 켜준다.
```bash
$ source venv/bin/activate
```

Django, DRF를 설치해준다.
```bash
$ pip install Django
$ pip install djangorestframework
```

기본적인 Django 프로젝트를 생성한다.
```bash
$ django-admin startproject <프로젝트명> .
$ cd <프로젝트명>
```

이렇게 들어와주면 기본적인 Django 프로젝트가 생성이 된다.

실행은
```
$ python manage.py migrate
$ python manage.py runserver
```
요런식으로 실행해주면 된다.

이후로 간단한 예제는 [공식문서](https://www.django-rest-framework.org/tutorial/quickstart/)에 나와있다.

## 다른 프레임워크와 비교

다른 프레임워크에 비교해 Django
- 장점
	- 기본적으로 제공해주는 기능이 많다.
		- 강력한 로그인, 회원가입 ex) dj-rest-auth
	- 그만큼 빠르게 개발이 가능하다.
	- 파이썬이다.
		- 다양하고 강력한 라이브러리
	- 기본 ORM 지원
		- 모델로 코드를 짜면 DB에 반영이 된다.
			- DB 작업을 적게 만들어줌 
- 단점
	- 기본적으로 제공해주는 기능외에 커스텀을 하려면 살짝 복잡해진다.
		- NestJS에 비해 닫혀있는 느낌??
	- 파이썬이다.
		- 느림
		- 런타임 에러 발생
	-  기존 MVC와는 살짝 다른 느낌

그치만 장고만의 매력이 있고
빠른 개발이 필요하고 파이썬에 익숙하다면 충분히 좋은 선택이 될것 같다.

## 참고 자료
- https://www.djangoproject.com/
- https://docs.djangoproject.com/ko/5.0/
- https://www.django-rest-framework.org/
- https://wikidocs.net/197569
- https://modulabs.co.kr/blog/about_drf/
- https://developer.mozilla.org/ko/docs/Learn/Server-side/Django/Introduction