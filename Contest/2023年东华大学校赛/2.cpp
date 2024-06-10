#include <bits/stdc++.h>
using namespace std;
#define int long long


void work() {

    int n, k;
    cin >> n >> k;

    vector<int> a(n + 2);
    for(int i = 1; i <= n; i++) cin >> a[i];

    vector<int> s(n + 2);
    for(int i = 1; i <= n; i++) s[i] = s[i - 1] + a[i];

    const int INF = 1LL << 60;
    vector<int> f(n + 2, -INF);
    vector<int> g(n + 2);
    multiset<int> h;
    int ans = 0;

    k += 2;

    f[1] = 0;
    g[1] = f[1] - s[1];
    // h.insert(g[1]);
    for(int i = 2; i <= n; i++) {
        if(i >= 3) f[i] = max(0ll, s[i - 1] + *h.rbegin());
        // cout << "f[" << i << "] = " << s[i - 1] << " + " << *h.rbegin() <<  " = " << f[i] << endl;
        g[i] = f[i] - s[i];
        h.insert(g[i - 1]);

        if(i - k >= 1) {
            auto it = h.find(g[i - k]);
            h.erase(it);
        }
        // ans = max(ans, f[i]);
    }

    // for(int i = 1; i <= n; i++) cout << f[i] << " "; cout << endl;
    // for(int i = 1; i <= n; i++) cout << g[i] << " "; cout << endl;

    cout << f[n] << endl;

}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        work();
    }

    return 0;
}