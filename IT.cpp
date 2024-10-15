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