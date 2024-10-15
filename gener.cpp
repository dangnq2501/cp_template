#include <bits/stdc++.h>
#include "testlib.h"
#define fi first
#define se second
#define pii pair<int, int>
#define pb push_back
using ll = long long;
using namespace std;
const int infx = 1e7;
const int N = 3e5 + 5;
const int M = 1e7;

bool snt(int x)
{
    if (x < 2)
        return false;
    for (int i = 2; i <= x / i; i++)
        if (x % i == 0)
            return false;
    return true;
}
 
struct Point{
    ll x, y;
    Point(){}
    Point(ll _x, ll _y){
        x = _x;
        y = _y;
    }
    bool operator == (Point& other){
        return (x == other.x)  && (y == other.y) ;
    }
};
 
struct Line{
    ll a, b, c;
    // a*x+b*y+c == 0
    Line(){}
    Line(ll _a, ll _b, ll _c){
        a = _a;
        b = _b;
        c = _c;
    }
    ll getY(ll x){
        return (-c -a*x)/b;
    }
    ll get(Point p, ll d){
        return a*p.x + b*p.y + c*d;
    }
 
};
 
Line Point2Line(Point l, Point r){
    return Line(l.y - r.y, r.x - l.x, -l.x*(l.y - r.y) - l.y*(r.x - l.x));
}
 
int a[N], b[N];
bool check[N];

int main(int argc, char *argv[])
{
    registerGen(argc, argv, 1);
    int ln = atoi(argv[1]), rn = atoi(argv[2]);
    int n = rnd.next(ln, rn);
    int t = n;

    cout << t << '\n';
    while(t -- > 0){
        cout << n-t << '\n';
        
    }
    

}
