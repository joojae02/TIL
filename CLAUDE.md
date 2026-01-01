# CLAUDE.md

This file provides guidance to Claude Code when working with this repository.

## Repository Overview

PARA + 제텔카스텐 방식으로 관리하는 Obsidian Vault (개인 지식 베이스).
소프트웨어 프로젝트가 아니므로 빌드/테스트 명령어 없음.

## Directory Structure

```
Projects/           # 진행 중인 프로젝트 (블로그 초안 등)
├── 개발블로그/
└── 취미블로그/

Areas/              # 지속 관리 영역 (학습 주제별)
├── AI/
├── algorithm/
├── db/
├── network/
├── 백엔드/
├── 언어/
├── 운영체제/
├── 클라우드/
└── 프론트/

Resources/          # 참고 자료
├── Zettelkasten/   # 원자적 개념 노트 (핵심!)
├── Attachments/
├── Excalidraw/
├── References/
├── Templates/
└── 책/

Archives/           # 완료/비활성 자료
├── 개발블로그/     # 발행된 글
└── 취미블로그/

Private/            # 개인 노트
```

## Custom Skills

| Skill | Purpose |
|-------|---------|
| `/zettel` | Resources/Zettelkasten/에 원자적 개념 노트 생성 |
| `/blog` | Projects/블로그/에 블로그 초안 생성 |
| `/publish` | 블로그 글을 Archives/로 이동 (발행 처리) |

## Workflow Rules

### 공부 정리 시
1. `Resources/Zettelkasten/`에 개념별 노트 생성
2. `[[링크]]`로 관련 개념 연결
3. 파일명: 짧고 명확하게 (예: `Redis TTL.md`)

### 블로그 작성 시
1. `Projects/개발블로그/` 또는 `Projects/취미블로그/`에 초안 생성
2. 파일명: `초안-제목.md`
3. 발행 후: `Archives/블로그/YYYY-MM-제목.md`로 이동

## Note Format

- 한국어 마크다운
- `[[옵시디언 링크]]` 적극 활용
- 코드 예시 포함
- Excalidraw 다이어그램 가능

## Obsidian Plugins

- **obsidian-excalidraw-plugin** - 다이어그램
- **obsidian-imgur-plugin** - 이미지 호스팅
- **remotely-save** - 클라우드 동기화
