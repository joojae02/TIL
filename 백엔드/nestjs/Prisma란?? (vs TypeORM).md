
이번 nestjs 프로젝트를 진행하면서 ORM으로 Prisma를 선택했습니다.
왜 Prisma를 선택했는지에 대한 포스팅입니다.

# Prisma란??
Prisma는 자바스크립트와 타입스크립트 커뮤니티에서 주목받고 있는 차세대 ORM(Object Relational Mapping) 프레임워크이다

## ORM이란??
**ORM**은 **DB 데이터** 즉 **Schema**를 **객체(Object)**로 매핑해 주는 역할을 하는 것이다
모델링 된 객체와 관계를 바탕으로 SQL을 자동으로 생성해 주는 도구이다
> 데이터베이스 데이터 <- 매핑 -> Object 필드

Node 진영에서는 주로 Sequelize, TypeORM을 사용한다

데이터베이스와 상호작용을 하는 응용 애플리케이션을 개발할 때 프로그래머가 직접 SQL을 작성하지 않아도 되어 개발 생산성을 높여준다는 측면에서는 기존 ORM과 비슷하다

Prisma는 기존 ORM과 달리 자체적인 스키마 문법을 제공하고 이 스키마를 통해서 DB 마이그레이션과 클라이언트 코드 생성을 완전히 자동으로 생성해준다

# 왜 Prisma?

아까 위에서 말한 `스키마를 통해서 DB 마이그레이션과 클라이언트 코드 생성을 완전히 자동으로 생성해준다` 
> 이게 좋은 점이 기존 TypeORM에서 런타임시에 터지던 에러를 컴파일 타임에 잡아줄수 있다.

주로 많이 쓰는 TypeORM과 차이를 써보면
## Schema 선언

Prisma Schema는 `직관적` `낮은 러닝커브`가 장점이라고 생각했다
훨씬 직관적이고 한눈에 알아보기 편한 구조이다

```ts
model User {
  id Int @id @default(autoincrement())
  name String? 
  email String @unique 
  posts Post[] 
}

model Post {
  id Int @id @default(autoincrement())
  title String
  content String?
  published Boolean @default(false)
  authorId Int?
  author User? @relation(fields: [authorId], references: [id]) }
```

```ts
import {
  Entity,
  PrimaryGeneratedColumn,
  Column,
  OneToMany,
  ManyToOne,
} from 'typeorm'

@Entity()
export class User {

  @PrimaryGeneratedColumn()
  id : number

  @Column({ nullable: true })
  name: string

  @Column({ unique: true })
  email: string

  @OneToMany((type) => Post, (post) => post.author)
  posts: Post[]
}

@Entity()
export class Post {

  @PrimaryGeneratedColumn()
  id: number

  @Column()
  title: string

  @Column({ nullable: true })
  content: string

  @Column({ default: false })
  published: boolean

  @ManyToOne((type) => User, (user) => user.posts)
  author: User

}
```

## Prisma Migrate + Prisma Introspection
- Prisma Migrate는 schema.prisma를 토대로 DB schema를 만들어 준다.

- Prisma Introspection은 Prisma Migrate와 반대 기능이다.
- 만약 기존 서비스의 ORM을 Prisma로 바꾸는 경우 DB schema는 있는데 schema.prisma는 없을때 사용하면 만들어준다.

```bash
$ npx prisma migrate dev

$ npx prisma migrate deploy
```

[공식문서](https://www.prisma.io/docs/concepts/components/prisma-migrate/migrate-development-production#create-and-apply-migrations)

## 타입 안전성

**TypeORM:** `typescript` 런타임 위에서 존재하므로, `Complie Time`에서 검사하기 때에 오류가 많이 뜬다...

```ts
const postRepository = getManager().getRepository(Post)

const publishedPosts: Post[] = await postRepository.find({
  where: { published: true },
  select: ['id', 'title'],
})

const post = publishedPosts[0] 
// The TypeScript compiler has no issue with this 

if (post.content.length > 0) { 
  console.log(`This post has some content.`) 
}
```

- `Typescript` 레벨의 문법 오류 및 체크는 가능하지만 `SQL Code`(?) 는 검사할 수 없다.
	-  그니까 위에 `select`에서 없는 `content` 칼럼을 출력했지만, `TS Complier`는 이를 체크하지 못한다.
	- 결국 런타임에서 에러가 나오게 된다

하지만 `Prisma`는 `key` 형태로 볼 수 있어 검사가 가능해진다
```ts
const publishedPosts = await prisma.post.findMany({
  where: { published: true },
  select: {
    id: true,
    title: true,
  },
})

const post = publishedPosts[0]

// The TypeScript compiler will not allow this
if (post.content.length > 0) {
  console.log(`This post has some content.`) 
}
```
TypeORM과 달리 Prisma는 타입의 안전을 보장해준다.
`createdPosts`변수는 `id`와 `title` 두개의 키값을 가지는 객체인 것이다



# 결론

제가 Prisma를 사용하기로 선택한 주요 3가지를 정리해봤는데

물론 단점들도 있습니다
- 성능 이슈가 발생할 수 있다.
- Prisma가 자동으로 생성하는 SQL 쿼리가 효율적이지 않을 때가 있다.
- 다른 프레임워크에 비해 부족한 정보
- 아쉬운 호환성
- 등등

이슈들이 있지만

그래도 실제로 사용해보니 생각보다 더 편했습니다
컴파일 딴에서 에러들을 잡아주는게 좋더라구요

글고 공식문서가 정말 잘 작성되어 있습니다.
그냥 공식문서 보면서 어떤거 써야할지만 정하면 될 정도

고민하시는 분들은 Prisma 써보시는거 강추 드립니다!!

## 참고 자료
- [What is Prisma?](https://www.prisma.io/docs/concepts/overview/what-is-prisma)
- [Why Prisma?](https://www.prisma.io/docs/concepts/overview/why-prisma)
- [Prisma vs TypeORM](https://www.prisma.io/docs/concepts/more/comparisons/prisma-and-typeorm?query=&page=1)
- [Prisma Schema](https://www.prisma.io/docs/concepts/components/prisma-schema)
- [MySQL](https://www.prisma.io/docs/concepts/database-connectors/mysql)
- [Prisma, 넌 누구니?](https://velog.io/@ltnscp9028/Prisma-%EB%84%8C-%EB%88%84%EA%B5%AC%EB%8B%88-gr0ecme3)
- [Prisma란? (feat. 사용해야 되는 이유)](https://fomaios.tistory.com/entry/Nodejs-Prisma%EB%9E%80-feat-%EC%82%AC%EC%9A%A9%ED%95%B4%EC%95%BC-%EB%90%98%EB%8A%94-%EC%9D%B4%EC%9C%A0)