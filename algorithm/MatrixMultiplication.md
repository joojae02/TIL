# Matrix Multiplication

Simple Matrix Multiplication Algorithm
- Problem: Determine the product of 2 n x n matrices
    - Inputs: an integer n, and 2 n x n matrices A and B
    - Outputs: the product C of A and B

```c
void matrixmult (int n, const number A[][],
const number B[][], number& C[][]) {
    index i, j, k;
    for (i = 1; i <= n; i++)
    for (j = 1; j <= n; j++) {
        C[i][j] = 0;
        for (k = 1; k <= n; k++)
            C[i][j] = C[i][j] + A[i][k] * B[k][j];
    }
}

```
총 곱셈
- O(n^3)

총 덧셈
- O(n^3)
    

