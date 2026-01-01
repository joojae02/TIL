## csim.c

adress 정보 
```c
typedef struct {
  int tag;
  bool valid;
  int time; 
} line_t;

typedef struct {
  line_t *lines;
} set_t;

typedef struct {
  set_t *sets;
  size_t set_num;  
  size_t line_num;
} cache_t; 
```

먼저 cache hit가 발생하는지 확인  
현재 라인의 valid 확인 
정보가 있다면 tag 확인  
tag가 같다면 hit count 증가 후 업데이트 

hit 되지 않았다면 miss  
이후 LRU에 따라서 time 확인으로 가장 오래된 장소 확인 후 교체  

## trans.c
 
가장 기본적인 전치 방법에서  
cache의 지역성을 고려해 변경  

c 배열은 한 행에 있는 순서들을 순차적으로 접근  
행 단위로 루프 도는 것이 효율적임  
cache size 는 32bytes  
한번에 8개의 integer을 처리 가능함  

lab 에서는 (32, 32) (64, 64) (61, 67) 3개의 행렬을 전치시킴  

32 32, 61 67은 8개씩 처리한다 

64 64는 4등분하여 8x8로 만들어 처리한다

 

