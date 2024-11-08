#include <bits/stdc++.h>
#define ll long long
#define ld long double
#define ull unsigned long long
#define pb push_back
#define pll pair<ll, ll>
#define pii pair<int, int>
#define fi first
#define se second
using namespace std;
const int N = 1e5+5;
const int M = 1e6+5;
const ll mod = 1e9+7;
const ll base1 = 517;
const ll base2 = 311;
const ll inf = 5e18;

void add(int& x, int y){
    x += y;
    if(x >= mod)x -= mod;
}
int n, m, k;
int a[N], b[N], cnt[N];
vector<int> adj[N];
ll ans, sum, d[N], dp[N];

void sol()
{
    cin >>  n;
    fill_n(cnt, 505, 0);
    for(int i = 1; i <= n; i ++){
        cin >> a[i];
        cnt[a[i]] += 1;
    }
    ans = 0;
    for(int i = 1; i <= 5000000; i ++){
        dp[i] = 0;
        int cur = cnt[i];
        for(int j: adj[i]){
            dp[i] += dp[j];
            cur += cnt[j];
            if(dp[i] >= mod)dp[i] -= mod;
        }
        
        dp[i] = (d[cur]-1-dp[i]+2*mod)%mod;
        // cout << i <<" "<<cur <<" "<<dp[i]<<'\n';
        ans = (ans + dp[i] * i % mod) %mod;
    }
    cout << ans<< '\n';
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
    d[0] = 1;
    for(int i = 1; i < M; i ++){
        d[i] = d[i-1] * 2 % mod;
        for(int j = i*2; j < M; j += i)adj[j].pb(i);
    }
    cin >> test;
    while(test -- > 0)sol();
    return 0;
}
