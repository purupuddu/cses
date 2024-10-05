#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int maxN = 100;
const ll MOD = 1e9+7;

int N, M, K, a, b;
ll X[maxN][maxN], Y[maxN][maxN];
#define rep(ind, st, end) for(int ind = st; ind<end; ind++)

ll C[maxN][maxN];
void mult(ll A[maxN][maxN], ll B[maxN][maxN]){
    rep(i, 0, N)
        rep(j, 0, N)
            C[i][j] = 1.1e18;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            for(int k = 0; k < N; k++){
                C[i][j] = min(C[i][j], A[i][k] + B[k][j]);
            }
        }
    }
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            A[i][j] = C[i][j];
}

int main(){
    cin >> N >> M >> K;
    rep(i, 0, N)
        rep(j, 0, N)
            X[i][j] = 1.1e18;
    for(int i = 0; i < M; i++){
        ll a, b, w;
        cin >> a >> b >> w;
        X[a-1][b-1] = min(X[a-1][b-1], w);
    }

    rep(i, 0, N)
        rep(j, 0, N)
            Y[i][j] = 1.1e18;
    rep(i, 0, N)
        Y[i][i] = 0;
    while(K){
        if(K&1)
            mult(Y, X);
        mult(X, X);
        K >>= 1;
    }

    if(Y[0][N-1] == 1.1e18)
        cout<<(-1)<<endl;
    else cout<<(Y[0][N-1])<<endl;
}