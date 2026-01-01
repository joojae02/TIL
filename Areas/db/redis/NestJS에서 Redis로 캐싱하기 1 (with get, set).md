
이전 포스트에서 Redis에 대해 알아봤고
[Redis란?? 그게 뭔데](https://blog.joojae.synology.me/what-is-redis/)

이제 실제 적용하는 방법.!

cache manager 사용 x
# Redis 설치하기
Redis 구축 환경은
Synology Nas - docker Ubuntu:22.04

요거 아니면 각자 맞게 설치
```bash
sudo apt-get update
sudo apt-get upgrade
```

```bash
sudo apt-get install redis-server
```

```bash
sudo vim /etc/redis/redis.conf
```

```
// 기본 설정
maxmemory 1g
maxmemory-policy allkeys-lru
```

외부 접속을 할거니까
로컬에서 redis를 설치했다면 할필요 x
```
bind 0.0.0.0
protected-mode no
port 6379 // 요건 바꿔도 되고 안바꿔도 되고..
requirepass <password>
```

```bash
sudo systemctl restart redis-server.service
// OR
sudo service redis-server restart

netstat -nlpt | grep 6379
tcp        0      0 0.0.0.0:6379            0.0.0.0:*               LISTEN      -
```
대충 이렇게 뜬다면 오케이

# NestJS Redis

## 패키지 설치

```bash
yarn add @liaoliaots/nestjs-redis ioredis
yarn add redis
yarn add -D @types/redis
```

## .env
각자 설정에 맞춰서 넣어주기
```
REDIS_HOST="서버 주소"
REDIS_PORT="포트 번호"
REDIS_PASSWORD="비밀번호"
```

## redis-cache.service.ts

여기가 실제 기능 구현하는 부분
```typescript
import { RedisService } from '@liaoliaots/nestjs-redis';
import { Injectable } from '@nestjs/common';
import { Redis } from 'ioredis';

@Injectable()

export class RedisCacheService {
	private readonly redisClient: Redis;
	
	constructor(private readonly redisService: RedisService) {
		this.redisClient = redisService.getClient();
	}
	async get(key: string): Promise<string> {
		return this.redisClient.get(key);
	}
	
	async set(key: string, value: string, expireTime?: number): Promise<'OK'> {
		return this.redisClient.set(key, value, 'EX', expireTime ?? 10);
	}
	
	async del(key: string): Promise<number> {
		return this.redisClient.del(key);
	}
```

대충 이렇게 짤 수 있다ㅏ

## redis-cache.module.ts
```typescript
import { RedisModule } from '@liaoliaots/nestjs-redis';
import { Module } from '@nestjs/common';
import { RedisCacheService } from './redis-cache.service';

@Module({
	imports: [RedisModule],
	providers: [RedisCacheService],
	exports: [RedisCacheService],
})

export class RedisCacheModule {}
```

## app.module.ts 에 추가
```typescript
imports: [
	RedisModule.forRootAsync({
		imports: [ConfigModule],
		useFactory: async (configService: ConfigService) => ({
			config: {
				host: configService.getOrThrow('REDIS_HOST'),
				port: configService.getOrThrow('REDIS_PORT'),
				password: configService.getOrThrow('REDIS_PASSWORD'),
			},
		}),
		inject: [ConfigService],
	}),
	RedisCacheModule,
]
```

요렇게 추가해주면??

기본적인 연동은 마무리다

근데 좀 아쉽
너무 단순한 코드..

## RedisCacheService 고도화
어떤거 할꺼냐면
- `set`,`get` 등등 제네릭을 사용하도록
- converter: 가져온 값을 원하는 형식으로 변환하는 함수
- finder: Redis에 값이 없을 경우 데이터를 찾아오는 함수
- `sets` 컬렉션
	- `sadd`, `smembers`구현

### `set`

```ts
async set<T>(key: string, value: T, converter: (value: T) => string): Promise<string> {
	return await this.redisClient.set(key, converter(value));
}
```

실제 사용하려면 가져오는 값을 변환해줘야함
`set<User>()` 뭐 이런식으로 사용한다하면
```ts
// set<User>()
const converter = (value: User) => JSON.stringify(value);
```
요런 식으로 사용하면 된다

### `get`
```ts
async get<T>(
	key: string,
	converter: (result: string) => T,
	finder?: (key: string) => Promise<string>,
): Promise<T | null> {
	let result = await this.redisClient.get(key);
	
	if (result == null || result == undefined) 
		if (!finder) {
			return null;
		}
		result = await finder(key);
		await this.redisClient.set(key, result);
	}
	
	return converter(result);
}
```
요렇게 해주면??

처음 Redis에서 가져오고 캐시된 내용이 없다면??
`finder`을 실행해 실제 디비에서 가져오는 등의 작업을 해준다

근데 내부에서 실행하기 어려운 경우도 있으니까 `finder`는 `nullable`하게

마지막으로 리턴은 원하는 타입으로 `converter`적용

예를들어 `Prisma` ORM을 쓴다하면

```ts
const finder = async (key: string) => await this.prisma.user.findUnique({ where: { uuid: key }});
```

대충 뭐 이런식으로???


## 결론

cache manager에서 사용할 수 없는 컬렉션들을 쓰기 위해서 직접 구현하기로 결정했는데

좀더 범용적이고 고도화된 코드를 작성하고 싶어서
기존에 있는 코드에서 좀 더 고도화하는 작업을 해줬다

우선은 간단한 `get`, `set`이고 다른 함수들은
다음 게시물에서 확인할 수 있다


참고 자료
- https://redis.io/docs/connect/
- https://redis.io/commands/
- https://redis.io/docs/data-types/
- https://github.com/liaoliaots/nestjs-redis/blob/ee3a2d4b6af9c3d2ede768373929f57c8e165e58/docs/latest/redis.md#configuration
- https://github.com/liaoliaots/nestjs-redis/blob/main/docs/latest/redis.md
- https://docs.nestjs.com/techniques/caching#different-stores
