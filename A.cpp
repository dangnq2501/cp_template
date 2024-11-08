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
const int N = 1e6+5;
const int M = 1e5+5;
const ll mod = 1e9+7;
const ll base1 = 517;
const ll base2 = 311;
const ll inf = 1e16;

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
int n, k, ans;
int a[N], b[N];
vector<pii> vi;
void sol()
{
    cin >> n ;
    for(int i = 1; i <= n; i ++)cin >> a[i];
    for(int i = 1; i <= n; i ++){
        int j = i, k = a[i];//gcd cua doan lien tiep [i, j];
        while(j+1 <= n&& __gcd(a[j+1], k) > 1){
            ++j;
            k = __gcd(k, a[j]);
        }
        ans = max(ans, j-i+1);
        
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
        freopen(task".out", "w", stdout);
    }
    int test = 1;
    // cin >> test;
    while(test -- > 0)sol();
    return 0;
}
