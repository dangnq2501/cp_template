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
        int n = Rand(5, 10);
        for(int i = 1; i <= n; i ++){
            s.push_back(char('a'+Rand(0, 2)));
        }
        inp << n << '\n' << s;
        inp.close();
        return 0;
        system(("sudo -S ./"+NAME + ".cpp 1111").c_str());
        system(("sudo -S ./"+NAME + "_trau.cpp 1111").c_str());
        if (system(("diff " + NAME + ".out " + NAME + ".ans").c_str()) != 0)
        {
            cout << "Test " << iTest << ": WRONG!\n";
            return 0;
        }
        cout << "Test " << iTest << ": CORRECT!\n";
    }
    return 0;
}