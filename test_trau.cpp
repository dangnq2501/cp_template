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
const int N = 2e6+5;
const int M = 8;
const ll mod = 998244353;
const int base = 350;
const ll inf = 5e18;
struct IT{
    int n;
    vector<ll> st, lazy;
    IT(){};
    void init(int _n){
        n = _n;
        st.resize(n*4+4, inf);
        lazy.resize(n*4+4, 0);
    }
    void reset(){
        fill(st.begin(), st.end(), inf);
    }
    void push(int id){
        if(!lazy[id])return;
        st[id*2] += lazy[id];
        st[id*2+1] += lazy[id];
        lazy[id*2+1] += lazy[id];
        lazy[id*2] += lazy[id];
        lazy[id] = 0;
    }
    void set_value(int id, int l, int r, int pos, ll v){
        if(l == r){
            st[id] = v;
            return;
        }
        int mid = (l+r)>>1;
        push(id);
        if(pos <= mid)set_value(id<<1, l, mid, pos, v);
        else set_value(id<<1|1, mid+1, r, pos, v);
        st[id] = min(st[id<<1], st[id<<1|1]);
    }
    void set_value(int pos, ll v){
        set_value(1, 0, n, pos, v);
    }
    void update(int id, int l, int r, int u, int v, ll x){
        if(u <= l && r <= v){
            st[id] += x;
            lazy[id] += x;
            return;
        }
        int mid = (l+r)>>1;
        push(id);
        update(id<<1, l, mid, u, v, x);
        update(id<<1|1, mid+1, r, u, v, x);
        st[id] = min(st[id<<1],st[id<<1|1]);
    }
    void update(int u, int v, ll x){
        update(1, 0, n, u, v, x);
    }
    ll get(int id, int l, int r, int u, int v){
        if(u <= l && r <= v)return st[id];
        if(u > r || l > v)return inf;
        int mid = (l+r)>>1;
        push(id);
        return min(get(id<<1, l, mid, u, v), get(id<<1|1, mid+1, r, u, v));
    }
    ll get(int l, int r){
        return get(1, 0, n, l, r);
    }
};
int n, m, k ,ans;
int cnt[N];
ll a[N],  b[N], sum, dis;
vector<int> adj[N];
void dfs(int u, int p = 0){
    ll total = 0;
    for(int v: adj[u]){
        if(v == p)continue;
        cnt[v] = sum-(a[v]-a[u]);
        if(cnt[v]%2!=0)ans = 1;
        cnt[v] /= 2;
        dfs(v, u);
        dis += cnt[v];
        total += cnt[v];
    }
    if(cnt[u] > total+1 || cnt[u] < 0 || total >cnt[u])ans = 1;
    if(total < cnt[u])b[u] = 1;
    else b[u] = 0;
    if(p && adj[u].size() == 1 && cnt[u] > 1)ans = 1;
    
}

bool valid_graph(int r){
    ans = 0;
    dis = 0;
    dfs(r);
    // cout << a[r] <<" df "<<dis<<'\n';
    // for(int j = 1; j <= n; j ++){
    //     cout << b[j] <<" ";
    // }
    // // for(int v: adj[r])cout << v <<" ";
    // cout << '\n';
    

    return !ans && (a[r] == dis);
    
}
void sol()
{
    cin >> n;
    for(int i =1 ; i <= n; i ++){
        cin >> a[i];
        adj[i].clear();
    }
    for(int i = 1; i < n; i ++){
        int x, y;
        cin >> x >> y;
        adj[x].pb(y);
        adj[y].pb(x);
    }
    k = 0;
   for(int i = 1; i <= n; i ++){
        if(adj[i].size() == 1){
            k = i;
            break;
        }
   }
    sum = a[k]-a[adj[k][0]];

    // cout << k <<'\n';
    for(int i = 0; i <= 2; i += 2){
        sum += i;
        cnt[k] = sum;
        

        if(valid_graph(k) && i/2 == b[k]){
            cout << "YES\n";
            for(int j =1; j <= n; j ++)cout << b[j] <<" ";
            cout << '\n';
            return;
        }

    }
    cout << "NO\n";
    
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
    cin >> test;
    while(test -- > 0)sol();
    return 0;
}
