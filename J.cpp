#include<bits/stdc++.h>
using namespace std;

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
using ll = long long;
const int N = 2e5+5;
const ll inf = 1e15;
struct clothing{
    int x, y, z, w;
}item[N];
int n, m, h, c[N], t[N], check[N], cnt[N], b[N], a[N];
int pos(int i, int j){
    return m+(i-1)*h+j+1;
}
long long dis(int x1, int y1, int x2, int y2){
    return 1ll * (x1-x2)* (x1-x2)+1ll * (y1-y2)* (y1-y2);
}
int main(){
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(0);
    #define task "test"
    if(fopen(task".inp", "r"))
    {
        freopen(task".inp", "r", stdin);
        freopen(task".out", "w", stdout);
    }
    int w, h;
    cin >> w >> h >> n;
    int src = 0, tgt = 2*n+2;
    Dinic dinic(tgt+1, src, tgt);
    int inf = 1e9;
    for(int i = 1; i <= n; i ++){
        cin >> a[i] >> b[i];
        if(dis(a[i], b[i], a[i], 0) <= 100*100)dinic.add_edge(0, i*2, inf);
        if(dis(a[i], b[i], a[i], h) <= 100*100)dinic.add_edge(i*2+1, n*2+2,inf);
        dinic.add_edge(i*2, i*2+1, 1);
        for(int j = 1; j < i; j ++){
            if(dis(a[i], b[i], a[j], b[j]) <= 200*200){
                dinic.add_edge(i*2+1, j*2, inf);
                dinic.add_edge(j*2+1, i*2, inf);
            }
        }
    }
    
    cout << dinic.flow();
}