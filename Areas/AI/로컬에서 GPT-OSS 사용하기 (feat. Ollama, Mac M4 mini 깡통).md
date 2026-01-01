
![](https://i.imgur.com/LBCSrOf.png)

최근 핫한 DeepSeek R1을 로컬에서 사용해보기
- Ollama

https://joojae.com/local-deepseek-r1-feat-ollama-8b-or-14b/

이전 글에서는 Open Web UI를 사용했지만 이번에는 Ollama에서 나온 App을 사용할 예정이다.
- https://ollama.com/blog/new-app

### PC 환경

- Mac Mini 2024 깡통
	- Apple M4 칩
	- 램 16GB

## Ollama  설치 및 실행

- https://ollama.com/blog/new-app
에서 APP을 다운받아 준다

- https://joojae.com/local-deepseek-r1-feat-ollama-8b-or-14b/
	- CLI로 이용할 예정이라면 brew를 사용해서 다운받아준다

## DeepSeek-R1 설치

[Ollama GPT-OSS](https://ollama.com/library/gpt-oss)

![](https://i.imgur.com/aj51NAS.png)

App 에서 다운받거나 CLI로 받아준다

```
$ ollama run gpt-oss:20b
```

명령어를 실행하게 되면 설치되어있지 않다면 설치 후 LLM이 실행이 된다.

![](https://i.imgur.com/9O3WL8n.png)

- ~~아.. 벌써 느린데..?~~
## 성능 테스트

성능 테스트는 [mactop](https://github.com/context-labs/mactop)를 이용했다.
```
$ brew install mactop
$ sudo mactop
```

간단한 질문 등을 해보면
![](https://i.imgur.com/3WsylBf.png)


![](https://i.imgur.com/q7sNN41.png)



![](https://i.imgur.com/87ZeuwC.png)

![](https://i.imgur.com/LFRvKMp.png)
 

![](https://i.imgur.com/on3MML3.png)
![](https://i.imgur.com/aOtFx7B.png)
