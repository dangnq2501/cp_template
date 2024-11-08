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
const int N = 3e5+5;
const int M = 8;
const ll mod = 1e9+7;
const int base = 350;
const ll inf = 5e18;
struct BIT{
    vector<int> fe;
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
        for(; id <= n; id += id & -id){
            fe[id] += x;
            if(fe[id] >= mod)fe[id] -= mod;
            if(fe[id] < 0)fe[id] += mod;
        }
    }
    int get(int id){
        if(id < 0)return 0;
        int res = 0;
        for(; id; id -= id & -id){
            res += fe[id];
            if(res >= mod)res -= mod;
        }
        return res;
    }
    int get(int l, int r){
        return get(r)-get(l-1);
    }
}bit[2], dem[2];

struct query{
    int l, r, id;
    bool operator < (const query& q){
        return (l / base < q.l / base) || (l/base == q.l/base && r < q.r);
    }
}q[N];
int n, m, k, sub_sz, cen;
int a[N], b[N], dp[N], cnt[N], d[N];
ll res[N], ans, sum[N], dep[N];

vector<int> vi;
vector<pii> adj[N];
void dfs(int u, int p = 0){
    cnt[u] = 1;
    int mx = 0;
    for(pii v: adj[u]){
        if(b[v.se] || v.se == p)continue;
        dfs(v.se, u);
        cnt[u] += cnt[v.se];
        mx = max(mx, cnt[v.se]);
    }
    if(max(mx, sub_sz - cnt[u])*2 <= sub_sz)cen = u;
}

void cal(int id, int u, int pre_w, int p){
    
    if(d[u] > k)return;
    ans = (ans + bit[id].get(k-d[u]+1)+1ll*dem[id].get(k-d[u]+1)*dep[u]%mod)%mod;
    ans = (ans + bit[id^1].get(k-d[u])+1ll*dem[id^1].get(k-d[u])*dep[u]%mod)%mod;
    ans = (ans + dep[u])%mod;
    // cout << u <<" "<<dep[u]<<" "<<d[u]<<" "<<bit[id].get(k-d[u]+1)<<" "<<bit[id^1].get(k-d[u])<<'\n';
    for(pii v: adj[u]){
        if(b[v.se] || v.se == p)continue;
        d[v.se] = d[u];
        dep[v.se] = (dep[u]+a[v.se])%mod;
        if(v.fi != pre_w)++d[v.se];
        cal(id, v.se, v.fi, u);
    }
}

void update_sub(int id, int u, int p, int sig){
    if(d[u] > k)return;
    bit[id].add(d[u]+1, sig*dep[u]);
    dem[id].add(d[u]+1, sig*dep[u]);
    for(pii v: adj[u]){
        if(b[v.se] || v.se == p)continue;
        dep[v.se] = (dep[u]+a[v.se])%mod;
        update_sub(id, v.se, u, sig);
    }
}

void decomposite(int u, int sz){
    sub_sz = sz;
    dfs(u);
    
    u = cen;
    b[u] = 1;
    dep[u] = a[u];
    for(pii v: adj[u]){
        if(b[v.se])continue;
        // cout << "Track " << u <<" "<<v.se<<'\n';
        d[v.se] = 0;
        dep[v.se] = (dep[u]+a[v.se])%mod;
        cal(v.fi, v.se, v.fi, u);
        dep[v.se]=a[v.se];
        update_sub(v.fi, v.se, u, 1);
        // cout <<u <<" "<<v.se<<" "<<ans<<'\n';
    }
    for(pii v: adj[u]){
        if(b[v.se])continue;
        update_sub(v.fi, v.se, u, -1);
    }
    
    for(pii v: adj[u]){
        if(b[v.se])continue;
        if(cnt[v.se] < cnt[u])
            decomposite(v.se, cnt[v.se]);
        else
            decomposite(v.se, sz-cnt[u]);

    }
}

void sol()
{
    cin >> n >> k;
    for(int i = 1; i <= n; i ++){
        cin >> a[i];
        ans = (ans+a[i])%mod;
    }
    bit[0].init(n);
    bit[1].init(n);
    dem[0].init(n);
    dem[1].init(n);
    for(int i = 1; i < n; i ++){
        int x, y, w;
        cin >> x >> y >> w;
        adj[x].pb({w, y});
        adj[y].pb({w, x});
    }
    decomposite(1, n);
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
        freopen(task".out", "w", stdout);
    }
    int test = 1;
    // cin >> test;
    while(test -- > 0)sol();
    return 0;
}
