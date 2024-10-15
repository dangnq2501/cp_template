#include <bits/stdc++.h>
#define fi first 
#define se second
#define pb push_back
#define pll pair<long long, long long>
#define pii pair<int, int>
using namespace std;
using ll = long long;
const int base = 317;
const int base1 = 113;
const ll mod = 998244353;
const int mod1= 1e9+7;
const int N = 5e3+5;
const int inf = 1e9;

struct Matrix{
    int n;
    vector<vector<int>> c;
    Matrix(){};
    Matrix(int _n){
        n = _n;
        c.assign(n, vector<int>(n, 0));
    };
    void init(int _n){
        n = _n;
        c.assign(n, vector<int>(n, 0));
    }
    int add(int x, int y){
        int res = x+y;
        if(res >= mod)x -= mod;
        return res;
    }
    Matrix operator * (const Matrix& other){
        Matrix res(n);
        for(int i = 0; i < n; i ++){
            for(int j = 0; j < n; j ++){
                for(int k = 0; k < n; k ++){
                    res.c[i][j] = add(res.c[i][j], 1ll*c[i][k]*other.c[k][j]%mod);
                }
                
            }
        }
        return res;
    }


};
Matrix nhan ( Matrix x,  Matrix y){
    Matrix res(x.n);
    for(int i = 0; i < x.n; i ++){
        for(int j = 0; j < x.n; j ++){
            for(int k = 0; k < x.n; k ++){
                res.c[i][j] = (res.c[i][j] + 1ll*x.c[i][k]*y.c[k][j])%mod1;
            }
            
        }
    }
    return res;
}
ll pw(ll k, ll n){
    ll res = 1;
    for(; n; n >>= 1){
        if(n&1)res = res * k % mod;
        k = k * k % mod;
    }
    return res;
}


Matrix pw(Matrix a, ll n){
    Matrix res(a.n);
    for(int i = 0; i < a.n; i ++)res.c[i][i] = 1;
    for(; n; n >>= 1){
        if(n&1)res = res * a;
        a = a * a;
    }
    return res;
}

Matrix pw1(Matrix a, ll n){
    Matrix res(a.n);
    for(int i = 0; i < a.n; i ++)res.c[i][i] = 1;
    for(; n; n >>= 1){
        if(n&1)res = nhan(res, a);
        a = nhan(a, a);
    }
    return res;
}

void sol(){
 

}
int main(){
    #define task "test"
    if(fopen(task".inp", "r")){
        freopen(task".inp", "r", stdin);
        freopen(task".out", "w", stdout);
    }
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int ntest = 1;
    // cin >> ntest;
    while(ntest -- > 0)
    sol();
 
}