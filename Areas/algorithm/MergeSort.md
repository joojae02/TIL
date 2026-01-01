# MergeSort
> Mergesort – 합병정렬

Sort n keys in nondecreasing sequence
- Inputs: positive integer n, array of keys S indexed from 1 to n
- Outputs: the array S containing the keys in nondecreasing order

```c
void mergesort (int n, keytype S[]) {
    if (n > 1) {
        const int h = |n/2|, m = n - h;
        keytype U[1..h], V[1..m];
        copy S[1] through S[h] to U[1] through U[h];
        copy S[h+1] through S[n] to V[1] through V[m];
        //여기까지 divide

        mergesort(h, U); //절반 sort
        mergesort(m, V); //절반 sort

        merge(h, m, U, V, S); // <- 비교
    }
}
```

```c
void merge(int h, int m, const keytype U[], const keytype V[], 
keytype S[]) {
    index i, j, k;
    i = 1; j = 1; k = 1;
    while (i <= h && j <= m) {
        if (U[i] < V[j]) { // 비교
            S[k] = U[i];
            i++;
        }
        else {
            S[k] = V[j];
            j++;
        }
        k++;
    }
    if (i > h)
        copy V[j] through V[m] to S[k] through S[h+m];
    else
        copy U[i] through U[h] to S[k] through S[h+m];
}

```

## 시간 복잡도
### merge만의 worst-case
1 3 5 7 / 2 4 6 8
- 1 2 3 4 5 6 7 8 (비교 7회)  
- W(h + m) = 7  //  `W(h + m) = h + m - 1`  

1 2 3 4 / 5 6 7 8 
- 1 2 3 4 5 6 7 8 (비교 4회) 
- B(h + m) = 4

### worst-case
```
W(h + m) = W(h) + W(m) + h + m - 1  

W(n) = W(h) + W(m) + (n - 1)  
W(1) = 0  

(n = 2^k , k>= 0) 일때  
W(n) = W(n/2) + W(n/2) + (n - 1)  
W(n) = 2W(n/2) + (n - 1)  

W(2^k) = 2 W(2^(k-1)) + 2^k -1

...

2^k * t0 + k*2^k - sig i=0 to i=k-1 (2^i)
k*2^k - (2^k - 1)

nlogn - (n - 1) -> O(nlgn)
```
## 공간복잡도가 향상된 합병 (Merge) 알고리즘

```c
void mergesort2 (index low, index high) {
    index mid; 
    if (low < high) {
        mid = (low + high)/2;
        mergesort2(low, mid);
        mergesort2(mid+1, high);
        merge2(low, mid, high);
    }
}
...
... 
mergesort2(1, n);

```
