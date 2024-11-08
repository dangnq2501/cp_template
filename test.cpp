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
const int N = 2e5+5;
const int M = 8;
const ll mod = 1e9+7;
const int base = 350;
const ll inf = 5e18;

struct BIT{
    vector<ll> fe;
    int n;
    BIT(){};
    void init(int _n){
        n = _n;
        fe.resize(n+1, 0);
    }
    void reset(){
        fill(fe.begin(), fe.end(), 0);
    }
    void add(int id, int x){
        for(; id <= n; id += id & -id)fe[id] += x;
    }
    void add(int l, int r, int x){
        add(l, x);
        add(r+1, -x);
    }
    ll get(int id){
        ll res = 0;
        for(; id; id -= id & -id)res += fe[id];
        return res;
    }
    ll get(int l, int r){
        return get(r)-get(l-1);
    }
}bit;
int n, m, k, sum;
ll a[N], h[N];
ll dp[N], d[N], ans, cnt[N];
vector<int> adj[N];
ll gcd(ll a){
    ll res = 0;
    for(ll x: adj[a]){
        res += dp[x];
        // cout << x <<" ";
    }

    return res;
}
void sol()
{
    
    for(int i = 1; i < N; i ++){
        dp[i] = i;
    }
    for(int i = 1; i < N; i ++){
        for(int j = i; j < N; j += i)adj[j].pb(i);
        
        if(d[i]==0 && i > 1){
            for(int j = i; j < N; j += i){
                dp[j] -= dp[j]/i;
                d[j] = 1;
                
            }
        }

    }
    // for(int i = 1; i <= 10 ; i++)cout << dp[i] <<" ";
    // cout << '\n';
    cin >> n;
    ll sum = 0;
    for(int i = 1; i <= n; i ++){
        cin >> a[i];
        // cout << gcd(a[i])<< "\n";
        
    }

    for(int i = 1; i <= n; i ++){

        for(int j = i; j <= n; j += i){
            for(int x: adj[a[j]]){
                ++cnt[x];
                ans = (ans + dp[i]*dp[x]%mod*(cnt[x]*cnt[x]-(cnt[x]-1)*(cnt[x]-1))%mod)%mod;
            }
        }      
        for(int j = i; j <= n; j += i){
            for(int x: adj[a[j]]){
                cnt[x] = 0;
            }
        }   

    }
    cout << ans;
   
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
        freopen(task".ans", "w", stdout);
    }
    int test = 1;
    // cin >> test;
    while(test -- > 0)sol();
    return 0;
}
