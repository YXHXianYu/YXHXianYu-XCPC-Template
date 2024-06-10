#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'

/*
a * b = lcm * gcd

9 = 1 * 3 * 3

10 = 2 * 5
5, 7, 9,

30 = 2 * 3 * 5

*/

void work() {
    int a, m;
    cin >> a >> m;

    int g = __gcd(a, m);
    a /= g;
    m /= g;

    int x = m;
    vector<int> b;
    for(int i = 2, lim = sqrt(x); i <= lim && x > 1; i++) {
        if(x % i == 0) {
            int cnt = 0;
            do {
                x /= i;
                cnt += 1;
            } while(x % i == 0);
            // b.push_back({i, cnt});
            b.push_back(i);
        }
    }
    if(x > 1) b.push_back(x);

    int ans = 0;
    int lim = (1LL << b.size()) - 1;
    for(int i = 0; i <= lim; i++) {
        int v = 1;
        for(int j = 0; j < b.size(); j++) {
            if(i >> j & 1) v *= b[j];
        }
        ans += (m / v) * (__builtin_popcount(i) & 1 ? -1 : 1);
    }
    
    cout << ans << endl;
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