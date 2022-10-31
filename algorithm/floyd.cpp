#include <iostream>
#include <algorithm>

using namespace std;
#define INF 100
int P[6][6];
void floyd2(int n, const int W[6][6], int D[6][6], int P[6][6]);
void path(int q, int r);

int main(void) {
    int W[6][6] = {{0,0,0,0,0,0}, 
						{0,0,1,INF,1,5},
						{0,9,0,3,2,INF},
						{0,INF,INF,0,4,INF},
						{0,INF,INF,2,0,3},
						{0,3,INF,INF,INF,0},
        };
    int D[6][6];
    floyd2(5, W, D, P);
    for(int k=1; k<= 5; k++){
        for(int i=1; i <= 5; i++)     
            cout << P[k][i] << " ";
        cout << endl;
    }
    path(5,3);

}


void floyd2(int n, const int W[6][6], int D[6][6], int P[6][6]){
    int i, j, k;
    for(i=1; i <=n; i++)
        for(j=1; j <= n; j++)
            P[i][j] = 0;
    for(k=1; k<= n; k++)
        for(i=1; i <= n; i++)     
            D[k][i] = W[k][i];
    for(k=1; k<=n; k++)
        for(i=1; i<=n; i++)
            for(j=1; j<=n; j++)
            if (D[i][k] + D[k][j] < D[i][j]) {                
                P[i][j] = k;
                D[i][j] = D[i][k] + D[k][j];
            }  
}

void path(int q, int r) {
    
    if (P[q][r] != 0) {
        path(q,P[q][r]);
        cout << " v" << P[q][r];
        path(P[q][r],r);
    }
}