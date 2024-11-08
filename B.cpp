#include <bits/stdc++.h>
#define ll long long
#define ld long double
#define ull unsigned long long
#define pb push_back
#define pll pair<ll, ll>
#define pii pair<int, int>
#define fi first
#define se second
#define pb push_back
using namespace std;
const int N = 2e6+5;
const int M = 8;
const ll mod = 1e9+7;
const int BLOCK = 300;
const ll inf = 5e18;

int n, m;
int a[N], b[N], c[N];
int t;
vector<pii> vi;
vector<int> adj[N], gr[N];
ll k, dp[N], cur;
void sol()
{
    cin >>  n >> k;
    for(int i = 1; i <= n; i ++)cin >> a[i];
    for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= n; j ++){
            ++dp[a[i]&a[j]];
        }
    }
    m = 20;
    for(int i = 0; i < 20; i ++){
        for(int mask = 0; mask < (1<<m); mask ++){
            if(mask >> i & 1){
                dp[mask] += dp[mask^(1<<i)];
            }
        }
    }
    for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= n; j ++){
            int mask = a[i]&a[j];
            mask ^= ((1<<m)-1);
            cur += dp[mask];
            if(cur >= k){
                cur -= dp[mask];
                for(int l = 1; l <= n; l ++){
                    for(int r = 1; r <= n; r ++){
                        if((a[i]&a[j]&a[l]&a[r]) == 0){
                            cur ++;
                            if(cur == k){
                                cout << i <<" "<<j<<" "<<l<<" "<<r; 
                                return;
                            }
                        }
                    }
                }
                 
            }
            
        }
    }
    cout << -1;
}

int main()
{
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(0);
    #define task "test"
    if(fopen(task".inp", "r"))
    {
        freopen(task".inp", "r", stdin);
        freopen(task".out", "w", stdout);
    }
    int test = 1;
    // cin >> test;
    while(test -- > 0)sol();
    return 0;
}
