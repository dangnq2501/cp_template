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
}bit;
int n, m;
int a[N], b[N], dp[N];
string s[N];
vector<pii> vi;
void sol()
{
    cin >>  n >> m;
    Dinic dinic(2*n*m+10+m, 0, 2*n*m+m+1);
    int sum = 0, ans = 0;
    for(int i = 0; i < n; i ++){
        cin >> s[i];
        for(int j = 0; j < m; j ++){
            if(j < m-1 && s[i][j] == '#' && s[i][j] == s[i][j+1]){
                dinic.add_edge(0, i*m*2+j+1, 1);
                ans ++;
            }
            if(i && s[i][j] == '#' && s[i-1][j] == s[i][j]){
                dinic.add_edge(i*m*2-m+j+1, 2*n*m+m+1, 1);
                ans ++;
            }
        }
    }
        
    for(int i = 0; i < n; i ++){
        for(int j = 0; j < m; j ++){
            if(s[i][j] == '#'){
                sum += 1;
                if(i < n-1 && s[i+1][j] == '#'){
                    if(j < m-1 && s[i][j+1] == '#'){
                        dinic.add_edge(i*2*m+j+1, i*m*2+m+j+1, 1);
                    }   
                    if(j && s[i][j-1] == '#'){
                        dinic.add_edge(i*2*m+j, i*m*2+m+j+1, 1);
                    }   
                }
                if(i && s[i-1][j] == '#'){
                    if(j < m-1 && s[i][j+1] == '#'){
                        dinic.add_edge(i*2*m+j+1, i*m*2-m+j+1, 1);
                    }   
                    if(j && s[i][j-1] == '#'){
                        dinic.add_edge(i*2*m+j, i*m*2-m+j+1, 1);
                    }   
                }

            }
            
        }
    }
    cout << sum -ans+ dinic.flow();
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