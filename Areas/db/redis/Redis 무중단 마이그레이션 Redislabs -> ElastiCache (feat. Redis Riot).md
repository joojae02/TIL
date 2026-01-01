
## 배경

기존 Redislabs에서 사용중이던 Essentials를 사용하고 있었다.

월 20USD 정도로 매우 저렴해 서비스 초기에 선택했던것으로 보인다..
다만 서비스가 성장하면서 maintenance로 인한 잦은 중단 및 권장 사용량의 약 5배를 넘는 네트워크를 사용하게 되면서 안정성이 매우 떨어지고 있다고 판단했다.

대부분의 인프라를 AWS에서 사용하고 있는만큼 ElastiCache로 마이그레이션하기로 했다.

## AWS ElastiCache

현재 Redis 사용 워크로드는 적은 메모리, 높은 네트워크 IO를 필요로 한다.

따라서 cache.t4g.small를 선택했다.
- vCPU: 2
- Memory: 1.37 GiB
- Network Performance: Up to 5 Gigabit

2 인스턴스 x 0.047 USD 시간당 x (100 / 100 사용함/월) x 730 시간 1달 기준 = 68.6200 USD


## Migration 방법

기본적으로 무중단을 목표로 한다.
> 당근 중단 배포하면 Dump 뜨던지 해서 새로 띄우면 된다


### REPLICAOF을 이용한 Master/Slave 방식

가장 간단한 방법이다.
Redis에서 제공하는 replicaof 명령어를 통해 Master/Slave 형태를 설정 후 Slave를 승격시키면 된다.

![](https://i.imgur.com/Y05N5cn.png)


다만 ElastiCache에서는 REPLICAOF가 지원되지 않아 불가능하다.
- [AmazonElastiCache SupportedCommands Docs](https://docs.aws.amazon.com/AmazonElastiCache/latest/dg/SupportedCommands.html)

또한 이 경우 Slave Redis가 Read-only 에서 Master로 승격시키는 동안 downtime이 발생된다.

### Third-Party Tool

![](https://i.imgur.com/3jWhSo3.png)

다른 방법은 Third-Party Tool를 이용해 Sync 시켜주는 방법이다.
중간에서 기존 Redis의 값을 읽어와 신규 Redis에 입력하는 방식으로 동기화를 진행한다.

두가지 정도의 툴이 있는데
- Redis-Shake
- Redis Riot
이 있다.

#### Redis-Shake
- [Redis-Shake Github](https://github.com/tair-opensource/RedisShake?tab=readme-ov-file)
- [Redis-Shake Docs](https://tair-opensource.github.io/RedisShake/en/guide/getting-started.html)
- [Best Practice AlibabaCloud](https://www.alibabacloud.com/blog/best-practice-migrate-aws-elasticache-to-alibaba-cloud-tair-via-riot_600417)

AliCloud에서 만든 내/외부의 Redis간 Sync를 위한 툴이다.

```toml
// shake.toml
[sync_reader]
address = "127.0.0.1:6379"
[redis_writer]
address = "127.0.0.1:6380"

```

```
$ ./redis-shake shake.toml
```

다음과 같이 .toml를 이용해 reader, writer를 지정하고 실행하는 방식이다.

다만 Redis의 PSYNC 명령어를 사용하는데
해당 명령어는 ElastiCache에서 기본적으로는 사용이 불가능하고
별도의 Ticket을 제출해야 사용가능하다.

물론 Sync 대신 Scan 등의 방식으로 수행할 수도 있다.

#### Redis Riot

- [Redis Riot Docs](https://redis.io/docs/latest/integrate/riot/)
- [Redis Riot Github](https://github.com/redis/riot?tab=readme-ov-file)

![](https://i.imgur.com/luCNpIS.png)

다음과 같은 구조를 사용한다.

Riot은 cli로 작동한다.
```
$ ./riot \
	redis://{기존 Redis URL}:{PORT} \
	redis://{신규 Redis URL}:{PORT} \
	--mode live \
	--struct \
	--progress log
```

SCAN, LIVE 모드로 사용가능한데 동기화는 LIVE 모드로 실행시켜주면 된다.
다음과 같은 커맨드로 사용 가능합니다.

후에 다시 말하겠지만
--struct: data raw dump가 아닌 command기반으로 좀더 상위 level(heavier)에서 migrate
--mode live : 지속적 sync
를 의미한다.

나는 PSYNC 티켓 제출 보다는 Riot을 사용하는게 좋겠다고 판단하여 Riot을 선택헀다.
> Scan 하는 방식이 더 무겁기 때문에 선택했지만.. 결국 Riot에서도 --struct를 사용하게 되어서 Redis-Shake을 선택했어도 좋았을것 같다.

## 마이그레이션

![](https://i.imgur.com/J3pQJAY.png)

ElastiCache는 AWS VPC 내에서만 접속 가능하기 때문에
Bastion Server를 사용하여 Riot을 설치해준다

### EC2 생성 후 Riot 설치

EC2는 각자 자유롭게 생성해준다.

```
$ sudo apt update -y
$ sudo apt upgrade -y

$ wget https://github.com/redis/riot/releases/download/v4.1.2/riot-standalone-4.1.2-linux-x86_64.zip
$ unzip riot-standalone-4.1.2-linux-x86_64.zip
$ cd riot-standalone-4.1.2-linux-x86_64
$ ./bin/riot -V
------------------------------------------------------------
riot 4.1.2
------------------------------------------------------------
Build time:   2024-08-25 23:36:01Z
Revision:     ea6fefff47f8a51fccad3d2bcd045ab2830cc2ec
JVM:          17.0.11 (Azul Systems, Inc. 17.0.11+9-LTS)
------------------------------------------------------------
```

확인해보니 Riot 버전에 따라 CLI 명령어가 달라지기에 잘 확인해서 진행하자.

### Redis Ping Test

후 기존 Redis, 신규 Redis에 잘 접속되는지 확인해주자

```
// Riot Connection Test
$ ./bin/riot ping \
	-h {URL} \
	-p {PORT} \
	-a {PASSWORD} \
	--unit microseconds

// Riot Connection Test
$ ./bin/riot ping \
	-h {URL} \
	-p {PORT} \
	-a {PASSWORD} \
	--unit microseconds

```

각각 확인해주자

### Source Redis `notify-keyspace-events` 허용

Riot을 사용하기 위해서 `notify-keyspace-events`를 설정해줘야하는데
대충 이벤트를 발생시키도록 트리거해준다고 보면 된다.

```
// Source Redis
$ redis-cli \
	-h {URL} \
	-p {PORT} \
	-a {PASSWORD}

// ElastiCache
$ redis-cli \
	-h {URL} \
	-p {PORT} \
	-a {PASSWORD} 

// Migragte 전 Source Redis에 설정 필요
// 주의: Redis 부하 상승
CONFIG SET notify-keyspace-events KEA
// 해제
CONFIG SET notify-keyspace-events ""
// 확인
CONFIG GET notify-keyspace-events

```

해당 설정을 해주면 Redis에 부하가 증가하기 때문에 수치를 보면서 진행하면 좋다.

### Backup

진행하기 전에는 꼭 스냅샷이던 다른 백업 수단을 준비해주자.
난 스냅샷을 사용해줬다.

> 마이그레이션 하던 중 문제가 생겨 롤백해야할 경우 스냅샷을 찍은 이후의 데이터는 손실된다...
> (DEV 환경에서 꼭.. 테스트해보고 사용하자)


### Redis Migrate 시작

나는 Redis에 최대한 부하를 줄이고 진행하기 위해 Worker들도 잠시 중단해줬다.
- 테스트 해본 결과 Stream 데이터들을 마이그레이션할때 에러가 발생했다.
- “ERR The ID specified in XADD is equal or smaller than the target stream top item”

대충 stream을 전송하면서 사용한 XADD에서 ID 값이 일치하지 않아 생긴 문제로 보였다.


```
// Riot replicate live DEV
// riot replicate [OPTIONS] SOURCE TARGET
$ ./bin/riot replicate \
	redis://{기존 Redis URL}:{PORT} \
	redis://{신규 Redis URL}:{PORT} \
	--source-pass {기존 Redis PASSWORD} \
	--mode live \
	--struct \
	--progress log
Scanning/Listening 100% [====] 4696/4696 (0:00:36 / 0:00:00) 130.4/s | capacity: 10,000 | dropped: 0

```


> 두 Redis 버전이 다를 경우 `--struct` 추가해야 에러 발생 하지 않는다.
> 만약 버전이 같다면 해당 플래그 제외해도 된다. (추가 부하가 발생) 
> Redis 7 DUMP format is not backwards compatible with previous versions. To replicate between different Redis versions, use [Type-Based Replication](https://redis.github.io/riot/#_replication_type_struct "https://redis.github.io/riot/#_replication_type_struct").


해당 Cli가 실행중이라면 Source Redis의 값이 수정되면 Target Redis에도 반영된다.
- 트래픽이 많고 Ops가 높은 경우 Network, Latency 등의 이유로 유실되는 데이터가 존재할 수 있다.

### 서비스 Redis 주소 변경

신규 Redis 주소로 서비스의 환경 변수 등을 변경해준다.
난 EB를 사용하고 있어 환경 변수를 변경한 후 모두 재시작 해줬다.

### Validation

```
$ ./bin/riot compare \
	redis://{기존 Redis URL}:{PORT} \
	redis://{신규 Redis URL}:{PORT} \
	--source-pass {기존 Redis PASSWORD} \
    --show-diffs \
    --ttl-tolerance 100000 
```
그리고 정상적으로 데이터들이 마이그레이션 되었는지 검증해준다.
- ttl이 있는 경우가 있어서 어느정도 ttl까지 허용해줄지 확인하고 실행해주면 된다.


## 결론

Redis 인프라 변경을 하게 되면서
기존 잦은 중단과 느린 속도 등을 개선할 수 있었다.
- Latency 약 절반으로 감소
- Maintenance 설정

위 내용들만 보면 순조롭게 진행된것처럼 보이지만...
Dev/Live 환경에서 테스트할때 Docs의 내용과 실제 사용법, 인터넷에 있는 자료등이 서로 달라서 
대부분 Riot help를 사용해 확인했다.
> Redis Shake가 더 자료가 많이 보였다..

또한 마이그레이션까지 모두 성공했지만
서버 코드 중 const로 박힌 값을 미처 발견하지 못해 1분 가량의 중단이 발생했다..

환경변수에만 의존하고 있을것이라 너무 확신했던것 같다..
- 레거시 코드는.. 2번.. 3번 확인하자.....

이래저래 나름 성공적으로 마이그레이션을 진행했던것 같고
마이그레이션한 후로 약 3달 간 문제 없이 운영되고 있다~