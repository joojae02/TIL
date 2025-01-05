
Go 설치부터 Fiber 설치, 가장 기본적인 Hello World 까지 찍어보기

Mac 기준으로 설명

## Go 설치
우선 Mac에 Go 설치

```shell
brew install go
```

설치가 완료되었다면
```shell
go version
```
버전 확인해주기

Fiber 프레임워크는 Go 1.21 버전 이상을 설치해야함


```shell
go mod init (원하는 프로젝트 명)
```
원하는 디렉토리에서  원하는 프로젝트 명을 적어준다
그러면 `go.mod` 파일 생성

## Fiber 설치

```shell
go get github.com/gofiber/fiber/v3
```
위 명령어를 통해 fiber 다운로드
go get 명령어에 대해 잘 모른다면 [go get](https://pkg.go.dev/cmd/go#hdr-Add_dependencies_to_current_module_and_install_them) 링크 참고

그럼  `go.mod` `go.sum` 두 파일이 수정 및 생성됨
위 두 파일 모두 깃허브에 올리는 것이 좋음

아무 `server.go`같은 파일 생성해주고

```go
package main

import "github.com/gofiber/fiber/v3"

func main() {
	app := fiber.New()

	app.Get("/", func(c fiber.Ctx) error {
		return c.SendString("Hello, World!")
	})

	app.Listen(":3000")
}
```

가장 베이직한 Hello, World!를 찍어주는 코드이다ㅏ

```shell
go run server.go
```

요렇게 실행해주면 http://localhost:3000 여기서 정상작동하는지 확인해주자ㅏ

![](https://i.imgur.com/jfaBXsv.png)
나온다면 완료

이후 라우팅, 정적 파일들 등등에 관련된 내용은
[공식 문서](https://docs.gofiber.io/)를 참고하자

## 참고
- https://docs.gofiber.io/
- https://github.com/gofiber/fiber/blob/main/docs/intro.md
- https://github.com/gofiber/fiber/tree/main
- https://go-tour-ko.appspot.com/