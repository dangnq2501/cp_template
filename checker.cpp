#include <bits/stdc++.h>
using namespace std;
// Tên chương trình
const string NAME = "test";
// Số test kiểm tra
const int NTEST = 10;

mt19937 rd(chrono::steady_clock::now().time_since_epoch().count());
#define rand rd

long long Rand(long long l, long long h) {
    assert(l <= h);
    return l + rd()  % (h - l + 1);
}

int main()
{
    srand(time(NULL));
    for (int iTest = 1; iTest <= NTEST; iTest++)
    {
        ofstream inp((NAME + ".inp").c_str());
        string s;
        int n = Rand(10, 30);
        int prim[5] = {2, 3, 5, 7, 11};
        int pr = prim[Rand(0, 4)];
        inp << pr << '\n';
        for(int i = 1; i <= n; i ++){
            s.push_back(char('0'+Rand(0, 9)));
        }
        inp << s << '\n' << n<<'\n';
        for(int i = 1; i <= n; i ++){
            int l = Rand(1, n/2), r = Rand(n/2+1, n);
            inp << l <<" "<<r<<'\n';
        }
        inp.close();
        system(("sudo -S ./"+NAME + ".cpp ").c_str());
        system(("sudo -S ./"+NAME + "_trau.cpp ").c_str());
        if (system(("diff " + NAME + ".out " + NAME + ".ans").c_str()) != 0)
        {
            cout << "Test " << iTest << ": WRONG!\n";
            return 0;
        }
        cout << "Test " << iTest << ": CORRECT!\n";
    }
    return 0;
}