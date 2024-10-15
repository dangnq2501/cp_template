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
const int N = 5e3+5;
const int inf = 1e9;
struct IT{
    int n;
    vector<int> st;
    IT(){};
    void init(int _n){
        n = _n;
        st.resize(n*4+4, 0);
    }
    void reset(){
        fill(st.begin(), st.end(), 0);
    }
    void update(int id, int l, int r, int pos, int v){
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
}ity;
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
        for(; id <= n; id += id & -id)fe[id] += x;
    }
    int get(int id){
        int res = 0;
        for(; id; id -= id & -id)res += fe[id];
        return res;
    }
    int get(int l, int r){
        return get(r)-get(l-1);
    }
}bit;
struct Node{
    int x, y, w;
    Node(){};
    Node(int _x, int _y, int _w){
        x = _x;
        y = _y;
        w = _w;
    }
};
Node res[N];
int n, m, t, a[N], child[N], chain_u[N], nchain, sz[N], in[N], out[N], h[N], P[N][20], top[N], ql[N], qr[N];
vector<int> adj[N], del_y, del_z, q[N];
long long ans, sum[N], k;
void dfs(int u, int p = 0){
    sz[u] = 1;
    for(int v: adj[u]){
        if(v == p)continue;
        h[v] = h[u]+1;
        P[v][0] = u;
        for(int i = 1; i <= 18; i ++)P[v][i] = P[P[v][i-1]][i-1];
        dfs(v, u);
        sz[u] += sz[v];

        if(sz[v] > sz[child[u]])child[u] = v;
    }
}

void hld(int u, int p = 0){
    chain_u[u] = nchain;
    if(!top[nchain])top[nchain] = u;
    in[u] = ++t;
    ity.update(t, u);
    if(child[u])hld(child[u], u);
    for(int v: adj[u]){
        if(v == p || v == child[u])continue;
        ++nchain;
        hld(v, u);
    }
    out[u] = t;
}

int binary_jump(int u, int height){
    for(int i = 18; i >= 0; i --){
        if(height >> i & 1)u = P[u][i];
    }
    return u;
}

long long get_chain(int u, int v){
    long long cnt = 0;
    while(chain_u[u] != chain_u[v]){
        int par = top[chain_u[u]];
        cnt += ity.get(in[par], in[u]);
        u = P[u][0];
    }
    return cnt + ity.get(in[v], in[u]);

    
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