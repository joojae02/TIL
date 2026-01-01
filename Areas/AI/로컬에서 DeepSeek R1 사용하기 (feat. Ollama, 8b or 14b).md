brew services
![](https://i.imgur.com/LBCSrOf.png)

최근 핫한 DeepSeek R1을 로컬에서 사용해보기
- Ollama, Open Web UI를 사용
기본적으로 설치는 brew를 사용한다.

### PC 환경

- Mac Mini 2024 깡통
	- Apple M4 칩
	- 램 16GB

## Ollama  설치 및 실행

우선 Ollama는 오픈소스 LLM을 로컬 PC에서 쉽게 실행할 수 있게 해주는 툴이다.
Llama 3, DeepSeek 등 여러 LLM을 쉽게 로컬에서 돌릴 수 있다.

Ollama는 쉽게 말해서 백엔드 서버이다.
UI를 기본적으로는 제공하지 않아 별도의 UI 툴을 사용하여 Ollama와 연결시켜야한다.

```
$ brew install --cask ollama

$ ollama serve
```
다음 명령어로 설치, 실행이 가능하다.

## DeepSeek-R1 설치

[Ollama DeepSeek-R1](https://ollama.com/library/deepseek-r1)
해당 링크에서 딥시크 R1에 관련된 명령어 및 정보를 볼 수 있다.

![](https://i.imgur.com/oPlZH7y.png)

지금은 DeepSeek-r1:14b 모델을 사용한다.

```
$ ollama run deepseek-r1:14b
```

명령어를 실행하게 되면 설치되어있지 않다면 설치 후 LLM이 실행이 된다.


![](https://i.imgur.com/Xoblj5z.png)


### Open Web UI 설치

Pip를 이용해서 설치하는 방법이 Docs에는 나와있지만 Docker를 이용하면 더 쉽다.
- [OpenWebUI](https://docs.openwebui.com/)  
- [OpenWebUI github](https://github.com/open-webui/open-webui)


```
$ docker run -d -p 3000:8080 --add-host=host.docker.internal:host-gateway -v open-webui:/app/backend/data --name open-webui --restart always ghcr.io/open-webui/open-webui:main
```

후 http://127.0.0.1:3000/ 로 접속해준다.

회원가입, 로그인 등을 진행해주고

![](https://i.imgur.com/ynGP1v8.png)

다음과 같은 UI가 나오면 성공이다.~

## 성능 테스트

성능 테스트는 [mactop](https://github.com/context-labs/mactop)를 이용했다.
```
$ brew install mactop
$ sudo mactop
```

간단한 질문 등을 해보면

![](https://i.imgur.com/Y0edaXS.png)

CPU는 거의 사용하지 않고 GPU, Memory를 거의 풀로 사용하는것을 볼 수 있다.


![](https://i.imgur.com/MrKiTSH.png)

![](https://i.imgur.com/TXogrdR.png)

대략 1분~2분 사이의 속도가 걸렸다.


생각보다 응답 속도가 느려서
8b를 사용해도 좋을것 같다.

## 8b or 14b

DeepSeek github에 벤치마크 데이터가 나와있는데
- [distilled-model-evaluation](https://github.com/deepseek-ai/DeepSeek-R1?tab=readme-ov-file#distilled-model-evaluation)

또한 다른 글들을 보면
- [DeepSeek-R1 (Reasoning Models/ Open Source) 8B vs 14B | A Side-by-Side Comparison (Local - Ollama)](https://www.linkedin.com/pulse/deepseek-r1-reasoning-models-open-source-8b-vs-14b-hapuarachchi-svpzc/)


요약해보자면
- 가벼운 모델, 간단하고 실용적인 솔루션 -> 8b
- 좀 더 무거운 모델, 추상적이고 복잡한 아이디어 -> 14b
가 될것 같다.


```
$ ollama run deepseek-r1:8b
```

로 바로 설치도 가능하니 필요한 상황에 따라 선택하면 좋을것 같다.

![](https://i.imgur.com/DpK9Zse.png)


![](https://i.imgur.com/2gG9F3s.png)

![](https://i.imgur.com/gydEnX3.png)

사용하는 리소스 자체엔 큰 차이는 없지만 (약간 메모리 덜쓰는??)
응답 속도는 체감될 정도로 확 빨라진게 보인다!

Mac Mini 깡통이면 8b가 딱 현실적인 사이즈로 보인다!
