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
struct LCP{
    int n, k;
    vector<int> lcp, p, cnt;
    vector<vector<int>> pos;
    LCP(){}
    void init(string s, int sz){
        n = s.length()+1;
        s = " " + s + "$";
        k = 20;
        lcp.resize(n+2);
        p.resize(max(n, sz)+2, 0);
        cnt.resize(max(n, sz)+2, 0);
        pos.assign(n+2, vector<int>(k, 0));
        for(int i = 1; i <= n; i ++)cnt[s[i]] += 1;
        for(int i = cnt.size()-2; i > 0; i -= 1)cnt[i] += cnt[i+1];
        for(int i = 1; i <= n; i ++){
            ++p[s[i]];
            pos[i][0] = n-cnt[s[i]+1]+p[s[i]];
        }
        for(int j = 1; j < k; j ++){
            fill(cnt.begin(), cnt.end(), 0);
            fill(p.begin(), p.end(), 0);
            
        }
    }
    void process(){

    }
};

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