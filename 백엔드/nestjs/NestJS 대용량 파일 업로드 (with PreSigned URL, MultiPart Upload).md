
오늘 해볼껀 대용량 파일 업로드~

# 대용량 파일 업로드

## 기존 업로드 방식
기존 파일 업로드 흐름은
1. 프론트에서 백으로 `multipart/form-data`으로 파일 담아서 전송
2. 백은 S3로 SDK를 이용해 저장
3. 저장한 파일의 url 반환

요런 흐름으로 파일 업로드를 진행했다
그리고 NestJS 파일 업로드 [공식 문서](https://docs.nestjs.com/techniques/file-upload)에 있는 `multer`를 사용해서 구현했다
### 문제점
만약? 엄청 큰 무거운 파일을 업로드하게된다면?? 
잘못하면 `OOM`이 일어날것이다

`multer`를 보면
> **WARNING**: Uploading very large files, or relatively small files in large numbers very quickly, can cause your application to run out of memory when memory storage is used.

## 다른 방법들??

지금 Storage로 S3를 사용하고 있기 때문에
- Stream 업로드
- S3 MultiPart 업로드
가 있다

### Stream 업로드
여기서 Stream 업로드는 스트림을 pipe 시켜서 s3에 다이렉트로 저장하는 방식이다

요게 업로드하는 파일 전체를 서버에 저장하지 않아서 OOM의 위험이 거의 없어진다
그래서 사실상 저장하는 파일의 크기가 무한대라고 볼 수 있다

근데 문제는 네트워크 환경, 뭐 등등에 의해서 속도가 많이 차이난다..
너무 오래걸림
사실상 파일 사이즈 제한이 필요해진다
또 중간에 업로드가 끊긴다면 처음부터 다시 업로드를 해줘야한다.....

### S3 MultiPart 업로드

사실상 요거 할라고 위에서 막 말했던 건데
[공식 문서](https://docs.aws.amazon.com/AmazonS3/latest/userguide/mpuoverview.html)

![](https://i.imgur.com/Uel75bc.png)

고냥 S3에서 제공해주는 업로드 방식 중 하나이다

대충 파일을 여러 작은 Part들로 나눈담에 하나씩 업로드한다
- 요기서 포인트는 클라이언트에서 바로 S3에 저장하는 것

그리고 모든 파일이 업로드 되면 S3에서 조립해 하나의 파일로 만들어준다

와 너무 간단하다.

요래 하면 서버에 파일이 아에 오지 않으니 부하가 거의 없다!!

## 그래서 어떻게 구현하는데

대충 4가지?? 5가지??로 구현한다

1. Multipart 업로드 시작
2. PreSignedURL 발급
3. PreSignedURL로 Part 전송
4. Multipart 업로드 완료
	- 혹은 취소

### Multipart 업로드 시작

대충 코드를 보면서 말하면

```ts
async createMultipartUpload(bucket: string, key: string, contentType: string) {
	return this.bucket
		.createMultipartUpload({
			Bucket: bucket,
			Key: key,
			ContentType: contentType,
			ACL: 'public-read',
		})
		.promise();
	}
```

그니까 
`Key`: 저장할 파일의 key값
`ContentType`: 전송할 파일의 ContentType
`ACL`: 저장하는 파일의 ACL
등등 param이 있는데 요건 각자 맞는걸로 선택해주면 된다

이걸 실행하고 받는 데이터 중에
```ts
/**
* Object key for which the multipart upload was initiated.
*/
Key?: ObjectKey;

/**
* ID for the initiated multipart upload.
*/
UploadId?: MultipartUploadId;
```
요거 2개는 프론트 쪽으로 보내줘야한다

### PreSignedURL 발급

```ts
async getPresignedUrl(bucket: string, key: string, uploadId: string, partNumber: number) {
	return this.bucket.getSignedUrl('uploadPart', {
		Bucket: bucket,
		Key: key,
		UploadId: uploadId,
		PartNumber: partNumber,
	});
}
```

아까 위에서 발급받은 `Key`, `UploadId`
그리고 1 ~ 10000 사이의 정수인 `PartNumber`를 받아와준다
현재 분할해 보내는 part의 순서 번호라 생각하면 된다

만약 이전에 업로드한 부분과 동일한 `PartNumber`로 업로드할 경우
이전에 업로드한 부분을 덮어쓴다

이래 하면 리턴값으로 string을 받게 되는데

그걸 프론트로 보내준다

### PreSignedURL로 Part 전송

그럼 프론트에서 아까 받은 `PresignedURL`에 `PUT` 요청으로 바이너리를 넣어 요청한다
보내는 바이너리의 용량은 5MB~5GB라는데 마지막 Part는 그 이하도 상관없다

그래서 사실 그냥 5MB 이상이다 싶으면 5MB씩 보내줘도 된다
더 작다면 그냥 한번만 보내주면 된다

이렇게 전송하면 Response로 Header에 `ETag`가 있을 텐데 요걸 또 저장해놔야한다
`ETag`는 Entity Tag이다

### 원하는 만큼 반복

- 파일을 분할한 개수만큼 
	- PreSignedURL 발급
	- PreSignedURL로 Part 전송

여기서 `PartNumber`, `ETag`는 다 들고 있자

아 그리고 하다가 PUT이 안되는 경우가 있을텐데 버킷에서 CORS도 설정해줘야한다
### Multipart 업로드 완료

```ts
async completeMultipartUpload(bucket: string, key: string, uploadId: string, parts: Part[]) {
	return this.bucket
		.completeMultipartUpload({
		Bucket: bucket,
		Key: key,
		UploadId: uploadId,
		MultipartUpload: {
			Parts: parts,
		},
	})
		.promise();
}
```

여기서 위에 사용했던 값들과 모두 똑같고
다른것은 
```ts
MultipartUpload: {
	Parts: parts,
},
```

요부분인데 
```ts
MultipartUpload: {
	Parts: [
		{
			ETag: 'testValue',
			PartNumber: 1,
		}
	],
},
```

대충 이런 형태??

그래서 난 이런 형태로 하나 만들어서 사용했다
```ts
export class Part {
	PartNumber: number;
	ETag: string;
}
```

이전까지 업로드 후 받았던 `PartNumber`, `ETag`를 배열 형태로 받아서 사용하면 된다

여기서 중요한 점은 이 완료를 수행하지 않으면 실제 버킷에 파일이 보이지 않는다.

근데 문제는 이게 용량은 먹어서 비용이 나온다..
그래서 해야되는게 
#### Multipart 업로드 취소
하나 이상을 업로드 했다면 취소를 해야 스토리지 용량을 먹지 않는다

```ts
async abortMultipartUpload(bucket: string, key: string, uploadId: string) {
	return this.bucket
		.abortMultipartUpload({
			Bucket: bucket,
			Key: key,
			UploadId: uploadId,
		})
	.promise();
}
```

`Key`, `UploadId`를 이용해서 취소할 수 있다
예외가 터진다면 가능한 취소를 해주자..

### 번외

#### 현재 업로드된 Part 리스트
```ts
async listParts(bucket: string, key: string, uploadId: string) {
return this.bucket
	.listParts({
		Bucket: bucket,
		Key: key,
		UploadId: uploadId,
	})
	.promise();
}

```

이런식으로 하면 현재 업로드한 리스트를 받을 수 있다
만약 업로드가 끝난 경우 에러를 뱉는다

#### 버킷에 완료 또는 취소 되지 않은 업로드 리스트

```ts
async listMultipartUploads(bucket: string) {
	return this.bucket
	.listMultipartUploads({
		Bucket: bucket,
	})
	.promise();
}
```
 버킷에 완료 또는 취소 되지 않은 업로드 들을 반환해준다


## 결론
이렇게 s3의 `MultipartUpload`를 구현해봤는데

사실 url 발급받을 때 다른 값들을 넣어줘서 보안을 강하게 하거나 파일 사이즈를 지정해주는 등의 작업을 해줄 수 있다

아무튼 서버의 리소스를 쓰지 않고 파일 업로드를 구현해줬는데
프론트 쪽에서 할일이 늘긴한다
그래도 현재 업로드 되는 퍼센트?? 현황?? 등을 유저에게도 보여줄 수 있어서
구현만 한다면 꽤 좋다고 생각한다

다른 분의 글을 읽었는데
당근 작은 파일을 업로드 하는데 사용하는건 오버 엔지니어링일 것이다
~~솔직히 좀 찔ㄹ.~~

큼큼... 

### 참고자료
- [Spring Boot에서 S3에 파일을 업로드하는 세 가지 방법](https://techblog.woowahan.com/11392/)
- https://github.com/expressjs/multer
- https://docs.nestjs.com/techniques/file-upload
- https://docs.aws.amazon.com/ko_kr/AmazonS3/latest/userguide/mpuoverview.html
- [멀티파트 업로드 생성](https://docs.aws.amazon.com/AmazonS3/latest/API/API_CreateMultipartUpload.html)
- [부분 업로드](https://docs.aws.amazon.com/AmazonS3/latest/API/API_UploadPart.html)
- [부분 업로드(복사)](https://docs.aws.amazon.com/AmazonS3/latest/API/API_UploadPartCopy.html)
- [멀티파트 업로드 완료](https://docs.aws.amazon.com/AmazonS3/latest/API/API_CompleteMultipartUpload.html)
- [멀티파트 업로드 중단](https://docs.aws.amazon.com/AmazonS3/latest/API/API_AbortMultipartUpload.html)
- https://docs.aws.amazon.com/ko_kr/AmazonS3/latest/userguide/mpu-abort-incomplete-mpu-lifecycle-config.html