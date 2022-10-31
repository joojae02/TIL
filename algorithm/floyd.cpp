#include <iostream>
#include <algorithm>

using namespace std;
#define INF 100
int P[6][6];
void floyd2(int n, const int W[6][6], int D[6][6], int P[6][6]);
void path(int q, int r);

int main(void) {
    int W[6][6] = {     
        {0,0,0,0,0,0}, 
        {0,0,2,INF,1,INF},
        {0,5,0,INF,3,INF},
        {0,3,INF,0,2,INF},
        {0,INF,INF,9,0,4},
        {0,INF,3,INF,1,0},
        };
    int D[6][6];
    floyd2(5, W, D, P);
    
    path(5,1);

}


void floyd2(int n, const int W[6][6], int D[6][6], int P[6][6]){
    int i, j, k;
    for(i=1; i <=n; i++)
        for(j=1; j <= n; j++)
            P[i][j] = 0;

    for(k=1; k<= n; k++)
        for(i=1; i <= n; i++)     
            D[k][i] = W[k][i];
    // cout << "0번째 D " << endl;
    // for(int k=1; k<= 5; k++){
    //     for(int i=1; i <= 5; i++){
    //         if(D[k][i] == INF)
    //             cout << "INF ";
    //         else
    //             cout << D[k][i] << " ";
    //     }     
    // cout << endl;
    // }
    cout << endl;
    for(k=1; k<=n; k++){
        for(i=1; i<=n; i++)
            for(j=1; j<=n; j++)
            if (D[i][k] + D[k][j] < D[i][j]) {                
                P[i][j] = k;
                D[i][j] = D[i][k] + D[k][j];
            }
        // cout << k << "번째 D " << endl;
        // for(int k=1; k<= 5; k++){
        //     for(int i=1; i <= 5; i++){
        //         if(D[k][i] == INF)
        //             cout << "INF ";
        //         else
        //             cout << D[k][i] << " ";
        //     }     
        //     cout << endl;
        // }
        // cout << endl;

        // cout << k << "번째 P " << endl;
        // for(int k=1; k<= 5; k++){
        //     for(int i=1; i <= 5; i++)     
        //         cout << P[k][i] << " ";
        // cout << endl;
        // }
        // cout << endl;
    }   
}

void path(int q, int r) {
    
    if (P[q][r] != 0) {
        path(q,P[q][r]);
        cout << " v" << P[q][r];
        path(P[q][r],r);
    }
}