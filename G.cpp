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
const int N = 2e3+5;
const int M = 8;
const ll mod = 1e9+7;
const ll mod1 = 1e9+6;
const ll base1 = 517;
const ll base2 = 311;
const int inf = 1e9;

struct edge{
    int u, v, pu, pv;
    edge(int _u ,int _v, int _pu, int _pv){
        u = _u;
        v = _v;
        pu = _pu;
        pv = _pv;
    }
};
struct DSU{
    int n;
    vector<int> lab, x_mx, x_mn, y_mn, y_mx;
    DSU(){}
    void init(int _n){
        n = _n;
        lab.assign(n+1, -1);
        x_mx.assign(n+1, 0);
        y_mx.assign(n+1, 0);
        x_mn.assign(n+1, n+1);
        y_mn.assign(n+1, n+1);
    }
    int findp(int u){
        return lab[u] < 0 ? u : lab[u]= findp(lab[u]);
    }
    void hop(int u, int v){
        u = findp(u);
        v = findp(v);
        if(u == v)return;
        if(lab[u] > lab[v])swap(u, v);
        lab[u] += lab[v];
        lab[v] = u;
        x_mx[u] = max(x_mx[u], x_mx[v]);
        x_mn[u] = min(x_mn[u], x_mn[v]);
        y_mx[u] = max(y_mx[u], y_mx[v]);
        y_mn[u] = min(y_mn[u], y_mn[v]);
        
    }
};

struct Node{
    int nxt[2], cnt;
    Node(){
        nxt[0] = nxt[1] = cnt = 0;
    }
    Node(int _cnt){
        nxt[0] = nxt[1] = 0;
        cnt = _cnt;
    }
};
struct Trie{
    vector<Node> trie;
    Trie(){
        trie.pb(Node(0));
    }
    void add(int x, int v){
        int id = 0, d;
        for(int i = 30; i >= 0; i --){
            d = (x >> i & 1);
            if(trie[id].nxt[d] == 0){
                trie[id].nxt[d] = trie.size();
                trie.pb(Node(0));
            }
            id = trie[id].nxt[d];
            trie[id].cnt = max(v, trie[id].cnt);
        }
        
    }
    int get(int x, int v){
        int res = 0;
        int id = 0, d;
        for(int i = 30; i >= 0; i --){
            d = (x >> i & 1);
            if(v >> i & 1){
                res = max(res, trie[trie[id].nxt[d]].cnt);
                id = trie[id].nxt[d^1];
            }
            else{
                id = trie[id].nxt[d];
            }
            
            if(id == 0)break;
        }
        return max(res, trie[id].cnt);
    }

};
struct FlowEdge {
    int v, u;
    long long cap, flow = 0;
    FlowEdge(int v, int u, long long cap) : v(v), u(u), cap(cap) {}
};

struct Dinic {
    const long long flow_inf = 1e18;
    vector<FlowEdge> edges;
    vector<vector<int>> adj;
    int n, m = 0;
    int s, t;
    vector<int> level, ptr;
    queue<int> q;

    Dinic(int n, int s, int t) : n(n), s(s), t(t) {
        adj.resize(n);
        level.resize(n);
        ptr.resize(n);
    }

    void add_edge(int v, int u, long long cap) {
        edges.emplace_back(v, u, cap);
        edges.emplace_back(u, v, 0);
        adj[v].push_back(m);
        adj[u].push_back(m + 1);
        m += 2;
    }

    bool bfs() {
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int id : adj[v]) {
                if (edges[id].cap - edges[id].flow < 1)
                    continue;
                if (level[edges[id].u] != -1)
                    continue;
                level[edges[id].u] = level[v] + 1;
                q.push(edges[id].u);
            }
        }
        return level[t] != -1;
    }

    long long dfs(int v, long long pushed) {
        if (pushed == 0)
            return 0;
        if (v == t)
            return pushed;
        for (int& cid = ptr[v]; cid < (int)adj[v].size(); cid++) {
            int id = adj[v][cid];
            int u = edges[id].u;
            if (level[v] + 1 != level[u] || edges[id].cap - edges[id].flow < 1)
                continue;
            long long tr = dfs(u, min(pushed, edges[id].cap - edges[id].flow));
            if (tr == 0)
                continue;
            edges[id].flow += tr;
            edges[id ^ 1].flow -= tr;
            return tr;
        }
        return 0;
    }

    long long flow() {
        long long f = 0;
        while (true) {
            fill(level.begin(), level.end(), -1);
            level[s] = 0;
            q.push(s);
            if (!bfs())
                break;
            fill(ptr.begin(), ptr.end(), 0);
            while (long long pushed = dfs(s, flow_inf)) {
                f += pushed;
            }
        }
        return f;
    }
};

struct BIT{
    int n;
    vector<ll> fe;
    BIT(int _n){
        n = _n;
        fe.resize(n+1, 0);
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
        if(l == 1)return get(r);
        return get(r) - get(l-1);
    }
};
struct BIT3D{
    int n;
    ll fe[101][101][101];
    BIT3D(){}
    void init(int _n){
        n = _n;
        memset(fe, 0, sizeof(fe));
    }
    void add(int x, int y, int z, int v){
        for(; x <= n; x += x & -x){
            for(int ny = y; ny <= n; ny += ny & -ny){
                for(int nz =z; nz <= n; nz += nz & -nz){
                    fe[x][ny][nz] += v;
                }
            }
        }
    }
    ll get(int x, int y, int z){
        ll res = 0;
        for(; x > 0; x -= x & -x){
            for(int ny = y; ny > 0; ny -= ny & -ny){
                for(int nz = z; nz > 0; nz -= nz & -nz){
                    res += fe[x][ny][nz];
                }
            }
        }
        return res;
    }
    ll get(int x1, int y1, int z1, int x2, int y2, int z2){
        ll total = get(x2, y2, z2);
        total -= get(x1-1, y2, z2);
        total -= get(x2, y1-1, z2);
        total -= get(x2, y2, z1-1);

        total += get(x2, y1-1, z1-1);
        total += get(x1-1, y2, z1-1);
        total += get(x1-1, y1-1, z2);
        
        total -= get(x1-1, y1-1, z1-1);
        return total;
    }
};
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
int n, m;
ll clen(ll x, ll y){
    return x * pw(2, y-1) % mod;
}
Matrix coff[30], coff1[30];
void sol()
{
    cin >> n;
    if(n == 0){
        cout << 0 << '\n';
        return;
    }
    if(n == 1){
        cout << 1 << '\n';
        return ;
    }
     
    Matrix  len_base(2), len_base_1(2), one_base(2);
    /*
        coff = [f, ones, len, 2^len]
       index = [0, 1, 2, 3, 4]
    */
    len_base.c[0][0] = 1;
    len_base.c[0][1] = 1;

    len_base_1.c[0][0] = 1;
    len_base_1.c[0][1] = 1;

    one_base.c[0][0] = 0;
    one_base.c[0][1] = 1;

    for(int i = 0; i < 30; i ++){
        if((n-1) >> i & 1){
            len_base = len_base * coff[i];
            one_base = one_base * coff[i];
            len_base_1 = nhan(len_base_1, coff1[i]);
        }
    }

    // cout << one.c[0][1] <<" "<<len.c[0][1]<<" "<<len1.c[0][1] << '\n';
    cout << 1ll * one_base.c[0][1] * ( clen(len_base.c[0][1], len_base_1.c[0][1])- clen(len_base.c[0][1]-1, len_base_1.c[0][1]-1) + mod) % mod << '\n'; 
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
    for(int i = 0; i < 30; i ++){
        coff[i].init(2);
        coff1[i].init(2);
    }
    coff[0].c[1][0] = 1;
    coff[0].c[1][1] = 1;
    coff[0].c[0][1] = 1;
    coff1[0].c[1][0] = 1;
    coff1[0].c[1][1] = 1;
    coff1[0].c[0][1] = 1;
    for(int i = 1; i < 30; i ++)coff[i] = coff[i-1] * coff[i-1];
    for(int i = 1; i < 30; i ++)coff1[i] = nhan(coff1[i-1], coff1[i-1]);
    int test = 1;
    cin >> test;
    while(test -- > 0)sol();
    return 0;
}
