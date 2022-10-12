# QuickSort
>“Partition Exchange Sort (분할교환정렬)”라고 부르는 게 타당  

Problem: Sort n keys in nondecreasing order 
- Inputs: positive integer n, array of keys S[1..n]
- Outputs: the array S containing the keys in nondecreasing order
```c
void quicksort (index low, index high) {
    index pivotpoint;
    if (high > low) {
        partition(low, high, pivotpoint);
        quicksort(low, pivotpoint-1);
        quicksort(pivotpoint+1, high);
    }
}

```

Problem: Partition the array S for Quicksort
- Inputs: (1) 2 indices, low & high, (2) subarray of S[low..high]
- Outputs: pivotpoints, the pivot point for the subarray indexed from low to high

```c
void partition (index low, index high, index& pivotpoint) {
    index i, j;
    keytype pivotitem;
    pivotitem = S[low]; //pivotitem을 위한 첫번째 항목을 고른다
    j = low;
    for(i = low + 1; i <= high; i++)
        if (S[i] < pivotitem) { // 비교!!
            j++;
            exchange S[i] and S[j];
        }
    pivotpoint = j;
    exchange S[low] and S[pivotpoint]; // pivotitem 값을 pivotpoint에
}

```

## worst-case

### quicksort
- input : high - low + 1
```c
1 <= p <= n (피벗의 위치)
W(n) = W(p - 1) + W(n - 1) + partition(n - 1)
W(0) = 0

// worst-case
// 한쪽은 0 한쪽으로 몰릴때
W(n) = W(0) + W(n - 1) + (n - 1)

W(n) = n(n-1)/2 -> O(n^2)
```
### partition
- every-case : (n - 1) 회 