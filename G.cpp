#include <bits/stdc++.h>
#define ll long long
#define ld long double
#define ull unsigned long long
#define pll pair<ll, ll>
#define pii pair<int, int>
#define fi first
#define se second
using namespace std;
const int N = 2e5+5;
const int M = 305;
const ll mod = 1e9+7;

const ll inf = 1e15;

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

ll pw(ll k, ll n){
    ll res = 1;
    for(; n; n >>= 1){
        if(n&1)res = res * k % mod;
        k = k * k % mod;
    }
    return res;
}

struct IT{
    int n;
    vector<pll> st;
    IT(){};
    void init(int _n){
        n = _n;
        st.resize(n*4+4);
    }
    // void reset(){
    //     fill(st.begin(), st.end(), 0);
    // }
    pll merg(pll x, pll y){
        if(x.fi < 0)return x;
        return min(x, y);
    }
    void update(int id, int l, int r, int pos, pll v){
        if(l == r){
            st[id] = v;
            return;
        }
        int mid = (l+r)>>1;
        if(pos <= mid)update(id<<1, l, mid, pos, v);
        else update(id<<1|1, mid+1, r, pos, v);
        st[id] = merg(st[id<<1], st[id<<1|1]);
    }
    void update(int pos, pll v){
        update(1, 1, n, pos, v);
    }
    pll get(int id, int l, int r, int u, int v){
        if(u <= l && r <= v)return st[id];
        if(u > r || l > v)return {inf, 0};
        int mid = (l+r)>>1;
        return merg(get(id<<1, l, mid, u, v), get(id<<1|1, mid+1, r, u, v));
    }
    pll get(int l, int r){
        return get(1, 1, n, l, r);
    }
};
int n, m, a[N], d[N], k, rmq[N][20];
ll ans, sum[N];
vector<int> adj[N], rv[N];
void sol()
{
    cin >> n;
    for(int i = 1; i <= n; i ++){
        cin >> a[i];
        ans = (ans + 1ll*i*a[i])%mod;
    }
    m = 1e5;
    for(int i = 1; i <= m; i ++){
        for(int j = i; j <= m; j += i){
            adj[j].push_back(i);
        }
    }
    map<pii, ll> mp;
    for(int i = n; i > 0; i --){
        for(int u: adj[i]){
            if(u > n/2)continue;
            for(int v: adj[a[i]]){
                ++mp[{u, v}];
                // cout << i <<" "<< u <<" "<<v<<'\n';
            }
        }
    }
    for (auto it = mp.rbegin(); it != mp.rend(); ++it) {
        pii x = it->first;
        ll y = it->second;
        mp[x] = y*(y-1)/2;
    }    
    for (auto it = mp.rbegin(); it != mp.rend(); ++it) {
        pii x = it->first;
        ll y = it->second;

        for(int u: adj[x.first]){
            for(int v: adj[x.second]){
                if(u == (x.first) && v == x.second)continue;
                mp[{u, v}] -= y;
            }
        }
        // cout << x.fi <<" "<<x.se<<" "<<y<<'\n';
        ans = (ans + 2ll*y*x.fi*x.se)%mod;
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
