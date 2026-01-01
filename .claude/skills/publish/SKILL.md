---
name: publish
description: 작성 완료된 블로그 글을 발행 처리합니다. 블로그 글 발행, 아카이브 이동, 글 완료 처리할 때 사용하세요.
allowed-tools: Read, Write, Bash, Glob, AskUserQuestion
---

# 블로그 글 발행

## 개요

`Projects/개발블로그/` 또는 `Projects/취미블로그/`의 초안을 발행 처리하고 `Archives/`로 이동합니다.

## 절차

1. **발행할 글 확인**: Projects 폴더에서 발행할 초안 확인
2. **글 검토**: 내용이 완성되었는지 확인
3. **메타데이터 업데이트**: status를 published로 변경, 발행일 추가
4. **파일명 변경**: `초안-` 접두사 제거, 날짜 추가
5. **Archives로 이동**: 해당 블로그 폴더로 이동

## 발행 후 메타데이터

```markdown
---
status: published
created: {생성일}
published: {YYYY-MM-DD}
tags: []
---
```

## 파일 이동 규칙

```
발행 전:
Projects/개발블로그/초안-Redis 캐시 전략.md

발행 후:
Archives/개발블로그/2026-01-Redis 캐시 전략.md
```

## 폴더 구조

```
Archives/
├── 개발블로그/     ← 발행된 개발 글
│   └── 2026-01-제목.md
└── 취미블로그/     ← 발행된 취미 글
    └── 2026-01-제목.md
```

## 명령어

```bash
# 파일 이동 예시
mv "Projects/개발블로그/초안-제목.md" "Archives/개발블로그/2026-01-제목.md"
```

## 예시

사용자: "Redis 캐시 전략 글 발행해줘"

1. `Projects/개발블로그/초안-Redis 캐시 전략.md` 확인
2. status: published, published: 2026-01-01 추가
3. `Archives/개발블로그/` 폴더 없으면 생성
4. `Archives/개발블로그/2026-01-Redis 캐시 전략.md`로 이동
5. 완료 메시지 출력
