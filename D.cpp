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
const int M = 8;
const ll mod = 998244353;
const ll base1 = 517;
const ll base2 = 311;
const ll inf = 5e18;

struct IT{
    int n;
    vector<pii> st;
    vector<multiset<int>> value;
    IT(){};
    void init(int _n){
        n = _n;
        st.resize(n*4+4);
        value.resize(n*4+4);
    }

    void insert(int id, int l, int r, int pos, int val){
        if(l == r){
            value[id].insert(val);
            st[id].fi = l-value[id].size();
            st[id].se = l;
            return;
        }
        int mid = (l+r)>>1;
        if(pos <= mid)insert(id<<1, l, mid, pos, val);
        else insert(id<<1|1, mid+1, r, pos, val);
        st[id] = min(st[id<<1], st[id<<1|1]);
    }
    void insert(int pos, int val){
        insert(1, 1, n, pos, val);
    }

    void erase(int id, int l, int r, int pos, int val){
        if(l == r){
            value[id].erase(val);
            st[id].fi = l-value[id].size();
            return;
        }
        int mid = (l+r)>>1;
        if(pos <= mid)erase(id<<1, l, mid, pos, val);
        else erase(id<<1|1, mid+1, r, pos, val);
        st[id] = min(st[id<<1], st[id<<1|1]);
    }
    void erase(int pos, int val){
        erase(1, 1, n, pos, val);
    }

    void update(int id, int l, int r, int pos, pii v){
        if(l == r){
            st[id] = v;
            return;
        }
        int mid = (l+r)>>1;
        if(pos <= mid)update(id<<1, l, mid, pos, v);
        else update(id<<1|1, mid+1, r, pos, v);
        st[id] = (st[id<<1]+st[id<<1|1]);
    }
    void update(int pos, int v){
        update(1, 1, n, pos, v);
    }
    int get(int id, int l, int r, int u, int v){
        if(u <= l && r <= v)return st[id];
        if(u > r || l > v)return 0;
        int mid = (l+r)>>1;
        return (get(id<<1, l, mid, u, v)+ get(id<<1|1, mid+1, r, u, v));
    }
    int get(int l, int r){
        return get(1, 1, n, l, r);
    }
}it;

void add(int& x, int y){
    x += y;
    if(x >= mod)x -= mod;
}
int n, m, k;
int a[N], b[N], cnt[N][2], dp[N];
vector<pii> vi, adj[N];
void dfs(int u, int p = 0){
    b[u] = 1;
    for(pii v: adj[u]){
        if(!b[v.se])dfs(v.se, u);
        if(!v.fi)add(dp[u], cnt[u][1]);
        cnt[u][v.fi] += 1;
        add(dp[u], 1ll * cnt[u][1] * cnt[v.se][0] % mod);
        add(dp[u], dp[v.se]);
        add(cnt[u][0], cnt[v.se][0]);
        add(cnt[u][1], cnt[v.se][1]);
        // cout << u<<" "<<v.se<<" "<<v.fi <<" "<<cnt[u][0] << " " << cnt[u][1] <<" "<<dp[u] << '\n';
    }
    
}
void sol()
{
    cin >>  n;
    for(int i = 1; i <= n; i ++){
        cin >> m;
        int w, x;
        while(m -- > 0){
            cin >> x >> w;
            adj[i].pb({w ,x});
        }
    }
    dfs(1);
    cout << dp[1];
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
