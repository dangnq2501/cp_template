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
const int N = 5e2+2;
const int M = 8;
const ll mod = 1e9+7;
const ll base1 = 517;
const ll base2 = 311;
const int inf = 1e9;

int n, m, k;
int  b[N], cnt[N], par[N] , ans, dp[2][N][N*2], a[N], kmp[N][2];
vector<pii> vi;
vector<int> adj[N];
void add(int &x, int y){
    if(x == -1 || x > y)x = y;
}
void sol()
{
    cin >> n >> m;
    string s, t;
    cin >> s >> t;
    s = " " + s;
    t = " " + t;
    memset(dp, -1, sizeof(dp));
    for(int i = 2; i <= m; i ++){
        k = kmp[i-1][0];
        while(k && t[i] != t[k+1])k = kmp[k][0];
        if(t[i] == t[k+1])kmp[i][0] = k+1;

        k = kmp[i-1][0];
        while(k && t[i] == t[k+1])k = kmp[k][0];
        if(t[i] != t[k+1])kmp[i][1] = k+1;
        // cout << kmp[i][0] <<" "<<kmp[i][1] << '\n';
    }
    dp[0][0][0] = 0;
    for(int i = 0; i < n; i ++){
        int id = (i&1);
        memset(dp[id^1], -1, sizeof(dp[id^1]));
        for(int j = 0; j < m; j ++){
            
            for(int k = 0; k <= n-m+1; k ++){
                if(dp[id&1][j][k] == -1)continue;
                // cout << i <<" "<<j<<" "<<k<<" "<<dp[i][j][k]<<'\n';

                if(s[i+1] == t[j+1]){
                    if(j+1 == m){
                        // if(k == 3 && i == 8)cout << kmp[m][0] << '\n';
                        add(dp[id^1][kmp[m][0]][k+1], dp[id][j][k]);
                        
                    }
                    else{
                        add(dp[id^1][j+1][k], dp[id][j][k]);
                    }
                    add(dp[id^1][kmp[j+1][1]][k], dp[id][j][k]+1);
                        
                }
                else{
                    if(j+1 == m){
                        add(dp[id^1][kmp[m][0]][k+1], dp[id][j][k]+1);
                    }
                    else{
                        add(dp[id^1][j+1][k], dp[id][j][k]+1);
                    }
                    add(dp[id^1][kmp[j+1][1]][k], dp[id][j][k]);
                }
            }
        }
    }
    // cout << dp[n][1][4] << '\n';
    for(int i = 0; i <= n-m+1; i ++){
        ans = -1;
        for(int j = 0; j < m; j ++){
            if(dp[n&1][j][i] == -1)continue;
            add(ans, dp[n&1][j][i]);
            // if(i == 4)cout << dp[n][j][i] <<" ";
            // if(i == 4)cout << ans <<" "<<dp[n][j][i]<<"\n";
        }
        cout << ans <<" ";
    }
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
