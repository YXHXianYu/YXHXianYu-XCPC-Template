#include<bits/stdc++.h>
using namespace std;
#define int long long

void work() {
    int n = 9;
    int m = 12;

    vector<vector<int>> a(n);
    a[1].push_back(1);
    a[2].push_back(2);
    a[3].push_back(3);

    auto move = [&](int fm, int col, int to) {
        vector<int> t0;
        vector<int> t1;
        for(auto x: a[fm]) {
            if(t1.size() == 0 && x != col) {
                t0.push_back(x);
            } else {
                t1.push_back(x);
            }
        }
        a[fm] = t0;
        for(auto x: t1) {
            a[to].push_back(x);
        }
    };

    auto find = [&](int col) {
        for(int i = 0; i < n; i++) {
            for(auto x: a[i]) {
                if(x == col) {
                    return i;
                }
            }
        }
        assert(false);
    };

    for(int i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y;

        int pos = find(x);
        move(pos, x, pos + y);
    }

    for(int i = 1; i <= 3; i++) {
        int pos = find(i);
        if(pos != n - 1) {
            cout << "N" << '\n';
            return;
        }
    }
    cout << "Y" << '\n';
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        work();
    }

    return 0;
}