
지난 포스트에선 
[NestJS에서 Redis로 캐싱하기 (feat 고도화)](https://blog.joojae.synology.me/nestjs-redis-caching-advance/)

`get`, `set`을 구현했다

이번 포스트에서는 `get`, `set`을 여러개씩 해주는
- `mget`, `mset`

sets 컬렉션을 사용하는
- `sadd`, `smembers`
를 구현해보자ㅏ

# `mget`, `mset`


## `mset`
### 설명
```
MSET key value [key value ...]
```
실제 cli에 사용할때는 이런식으로 사용한다

```
MSET key1 "Hello" key2 "World"
```
이런식으로 찾길 원하는 key, value 값을 뒤로 쭉 보내주면 된다

시간 복잡도는 O(N) N은 설정할 키의 개수이다

리턴은 항상 `OK`

### 구현
코도화를 시켜주기 위해 
기본적으로 제네릭 타입을 사용해줬고
```ts
async mset<T>(
	keys: string[],
	values: T[],
	expiretime: number,
	converter: (value: T) => string
): Promise<string>
```
`expiretime`, `converter()` 를 받아주는데
- `expiretime`: key 만료 시간
- `converter` :  T -> string으로 바꿔주는 함수, 레디스에 저장하기 위함
으로 이뤄져있다 

```ts
async mset<T>(
	keys: string[],
	values: T[],
	expiretime: number,
	converter: (value: T) => string
): Promise<string> {
	const keyValue: string[] = [];

	// 요건 개인 선택 키 벨류의 쌍이 맞아야 되도록
	// if (keys.length !== values.length) { }
	const convertedValues = values.map((value) => converter(value));

	// key, value를 하나의 배열로 만들어 준다
	keys.forEach((key, index) => keyValue.push(key, convertedValues[index]));

	// 실제 mset
	const result = await this.redisClient.mset(...keyValue);

	// 모든 key expire 걸어주기
	keys.map(async (key) => {
		await this.redisClient.expire(key, expiretime);
	});
	
	return result;
}
```

## `mget`

### 설명
```
MGET key [key ...]
```
실제 cli에 사용할때는 이런식으로 사용한다

```
MGET key1, key2, key3, key4 ...
```
이런식으로 찾길 원하는 key값을 뒤로 쭉 보내주면된다

시간 복잡도는 O(N) N은 검색할 키 수이다

리턴은 배열 형태인데 실제 key값에 해당하는 값이 없는 경우 `null`을 리턴한다

그래서 
```
MGET key1 key2 nonexisting
// 라면
return [ 'value1', 'value2', null ]
// 이런 식의 리턴이라고 생각하면 된다
```

### 구현
```ts
/**
*
* @param key Redis Key
* @param converter 가져온 문자열 값을 원하는 형식으로 변환하는 함수
* @param finder Redis에 값이 없을 경우 데이터를 찾아오는 비동기 함수
* @returns
*/
async mget<T>(
	keys: string[],
	converter: (result: string) => T,
	finder: (keys: string[]) => Promise<T[]>,
): Promise<T[]> {
	const redisResults = await this.redisClient.mget(...keys);
	const nonCachedKeys: string[] = [];
	const results: T[] = [];
	
	redisResults.forEach((value, index) => {
		if (value === null) {
			nonCachedKeys.push(keys[index]);
		} else {
			results.push(converter(value));
		}
	});
	
	if (nonCachedKeys.length !== 0) {
		const finderResults = await finder(nonCachedKeys);
		if (finderResults.length > 0) {
			await this.mset<T>(nonCachedKeys, finderResults, 30, (value) => JSON.stringify(value));
		}
		results.push(...finderResults);
	}
	return results;
}
```

코도화를 시켜주기 위해 
기본적으로 제네릭 타입을 사용해줬고
```ts
async mget<T>(
	keys: string[],
	converter: (result: string) => T,
	finder?: (keys: string[]) => Promise<T[]>,
): Promise<T[] | null> 
```
`converter()`, `finder()`를 받아주는데
- `converter` :  레디스에서 가져오는 값을 원하는 타입으로 바꿔주는 함수
- `finder` : 레디스에 캐싱된 값이 없는 경우 값을 가져오는 함수 (예: 실제 디비에서 가져오는 로직)
으로 이뤄져있다 

#### 레디스에서 가져오는 부분

```ts
	// 레디스에 접근해 키들에 해당하는 값 가져오기
	const redisResults = await this.redisClient.mget(...keys);

	// 레디스에 값이 존재하지 않아 null이 반환된 key들
	// 다음 finder로 이 값들 가져와줄거임
	const nonCachedKeys: string[] = [];

	// 받은 key들에 해당하는 결과들
	// 반환하는 배열
	const results: T[] = [];

	// 레디스에서 가져온 값을 검사해 null 서치
	redisResults.forEach((value, index) => {
		if (value === null) {
			// null인 경우 nonCachedKeys에 삽입
			nonCachedKeys.push(keys[index]);
		} else {
			// 값이 존재하는 경우 results에 원하는 type으로 convert 후 삽입
			results.push(converter(value));
		}
	});
```

#### `finder()`로 레디스에 존재하지 않는 값 가져오기
```ts
	// 레디스에서 반환한 값들 중 null 인 값이 하나라도 있다면
	if (nonCachedKeys.length !== 0) {
		// finder을 이용해서 값 가져오기
		const finderResults = await finder(nonCachedKeys);

		// 사실 여긴 각자 다르게 작성해도 괜찮을듯..
		// 일단 난 캐시되지 않은 key들에 대한 값들이 다 와야 정상이라고 판단했다
		if (finderResults.length !== nonCachedKeys.length) {
			throw new NotFoundException('존재하지 않는 key가 포함되어 있습니다.')
		}
		// 가져온 값들이 있다면??
		if (finderResults.length > 0) {
			// 캐싱해주기
			await this.mset<T>(nonCachedKeys, finderResults, 30, (value) => JSON.stringify(value));
		}
		results.push(...finderResults);
	}
	return results;
```
이 구현에서 알아둬야 할 점은
우선 넣은 key값의 순서와 반환받는 key에 대한 value의 순서가 일치하지 않습니다

key1, key2, key3, key4, key5 를 넣었고
캐싱이 된것들이 1, 2, 5 였다면
value1, value2, null, null, value5 이런 식이다

근데 난 디비 접근을 배치로 해주고 싶었기 때문에

null인 key들만 분리해서 별도의 요청을 보내줬다

그래서 리턴은
- 넣은 key 배열 `[key1, key2, key3, key4, key5]`
- 캐싱된 값들 `[value1, value2, null, null, value5]`
- 최종 반환 값들 `[value1, value2, value5, value3, value4]`

대충 이런식이 된다

난 순서는 상관 없는 작업이라 일단 이렇게 구현해줬는데
순서가 중요한 경우는 다르게 구현해야 될것 같다


## `sadd`

### 설명
```
SADD key member [member ...]
```
실제 cli에 사용할때는 이런식으로 사용한다
```
MGET key1, value1, value2, value3 ...
```
이런식으로 key 뒤로 저장할 값들을 쭉 주면 된다

시간 복잡도는 각 값당 O(1)이라 벨류 값들 개수에 따라서 O(N)이 된다

그래서 
```
MGET key1 key2 nonexisting
// 라면
return [ 'value1', 'value2', null ]
// 이런 식의 리턴이라고 생각하면 된다
```
### 구현
```ts
async sadd<T>(key: string, value: T[], expiretime: number, converter: (value: T) => string): Promise<void> {
	const convertedList = valueList.map((v: T) => converter(v));
	
	if (convertedList.length <= 0) {
		return;
	}
	
	await this.redisClient.sadd(key, ...convertedList);
	await this.redisClient.expire(key, expiretime);
}
```
`expiretime`, `converter()` 를 받아주는데
- `expiretime`: key 만료 시간
- `converter` :  T -> string으로 바꿔주는 함수, 레디스에 저장하기 위함
으로 이뤄져있다 

요건 이전 게시물에 `set`과 거의 동일한 로직이라..

근데 여기서 `value`를 배열로 받고 있는데
무조건 배열 형태로 받고 있다

다른 방법 써서 바꿔도 좋을듯..
요소 하나도 받을 수 있도록??

## `smembers`

### 설명
```
SMEMBERS key
```
key의 모든 멤버를 반환한다

```
SMEMBERS myset
```

시간 복잡도는 안에 모든 값들을 가져오기 때문에 O(N)이다
### 구현

```ts
async smembers<T>(
	key: string,
	converter: (result: string) => T,
	finder?: (key: string) => Promise<T[]>,
): Promise<T[] | null> {
	const members = await this.redisClient.smembers(key);
	
	if (members.length <= 0 || !members) {
		if (!finder) {
			return null;
		}
		
		const finderMembers = await finder(key);
		
		if (finderMembers.length <= 0) {
			return finderMembers;
		}
		
		const stringMembers = finderMembers.map((value) => JSON.stringify(value));
		await this.redisClient.sadd(key, ...stringMembers);
		await this.redisClient.expire(key, 30);
		
		return finderMembers;
	}
	return members.map((value: string) => converter(value));
}
```

음 이거도 위의 `mget`과 비슷한 맥락이다

`converter()`, `finder()`를 받아주는데
- `converter` :  레디스에서 가져오는 값을 원하는 타입으로 바꿔주는 함수
- `finder` : 레디스에 캐싱된 값이 없는 경우 값을 가져오는 함수 (예: 실제 디비에서 가져오는 로직)
으로 이뤄져있다 


## 결론

필요한 함수들을 그냥 쓰지 않고
랩핑해서 고도화 시키는 작업을 했는데

생각보다 깔끔하지는 않고 특정 시점에 문제가 생길만 한 부분들이 보이는 것 같다...
일단 사용해야해서 사용하는데
추후 리펙토링 필요해 보임....

그래도 이렇게 사용하는게 그냥 `redis`로 가져다 쓰는것보단 코드도 깔끔해지고 사용성도 좋아지는것 같다

### 참고자료
- https://redis.io/commands/mset/
- https://redis.io/commands/mget/
- https://redis.io/commands/sadd/
- https://redis.io/commands/smembers/
- https://redis.io/commands/sinter/
- https://redis.io/docs/data-types/sets/
- https://redis.io/docs/data-types/strings/