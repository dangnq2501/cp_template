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
const int N = 4e5+5;
const int M = 8;
const ll mod = 998244353;
const ll base1 = 517;
const ll base2 = 311;
const ll inf = 5e18;

int n, m, k, q;
int a[N], b[N], cnt[N][2], dp[N], h[N], d[N][N], ans;
vector<int> vi;
vector<pii> adj[N];

void sol()
{
    cin >> n >> m >> q;
    while(m -- > 0){
        int x, y, w;
        cin >> x >> y >> w;
        adj[x].pb({w, y});
        adj[y].pb({w, x});
    }
    for(int i = 1; i <= n; i ++){
        fill_n(d[i], n+1, inf);
        d[i][i] = 0;
        priority_queue< pii, vector<pii>, greater<pii> > pq;
        pq.push({0, i});
        while(!pq.empty()){
            pii u = pq.top();
            pq.pop();
            for(pii v: adj[u.se]){
                if(d[i][v.se] > u.fi + d[i][u.se]){
                    d[i][v.se] = u.fi + d[i][u.se];
                }
            }
        }
    }
    while(q -- > 0){
        cin >> k;
        
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
