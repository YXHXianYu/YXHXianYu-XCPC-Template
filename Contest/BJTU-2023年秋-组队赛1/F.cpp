#include<bits/stdc++.h>
using namespace std;
// #define int long long

void work() {
    int n;
    cin >> n;

    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];

    vector<vector<int>> e(n + 1, vector<int>());
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }

    int lim = log2(n);
    
    vector<long long> ans(100);
    vector<map<int, array<array<int, 2>, 17>>> g(n + 1);
    vector<int> f(n + 1);
    vector<int> sz(n + 1);
    for(int i = 1; i <= n; i++) f[i] = i;
    
    function<void(int, int)> dfs = [&](int x, int fa) {
        
        vector<array<int, 2>> b;
        for(auto y: e[x]) {
            if(y == fa) continue;
            dfs(y, x);
            b.push_back({sz[y], y});
        }
        if(b.size() == 0) {
            sz[x] = 1;
            for(int i = 0; i <= lim; i++)
                g[f[x]][a[x]][i][x>>i&1] += 1;
            return;
        }

        sort(b.begin(), b.end());

        sz[x] = sz[b.back()[1]];
        f[x] = f[b.back()[1]];

        for(int i = b.size() - 2; i >= 0; i--) {
            int y = b[i][1];
            for(auto [v, pr]: g[f[y]]) {
                if(g[f[x]].count(a[x] ^ v)) {
                    auto pr2 = g[f[x]][a[x] ^ v];
                    for(int i = 0; i <= lim; i++) {
                        ans[i] += 1ll * pr[i][0] * pr2[i][1];
                        ans[i] += 1ll * pr[i][1] * pr2[i][0];
                    }
                }
            }
            sz[x] += sz[y];
            for(auto [v, pr]: g[f[y]]) {
                auto pr2 = g[f[x]][v];
                for(int i = 0; i <= lim; i++) {
                    pr2[i][0] += pr[i][0];
                    pr2[i][1] += pr[i][1];
                }
                g[f[x]][v] = pr2;
            }
        }

        sz[x] += 1;
        for(int i = 0; i <= lim; i++)
            g[f[x]][a[x]][i][x>>i&1] += 1;
    };

    dfs(1, 0);

    long long ansT = 0;
    for(int i = 0; i <= lim; i++) ansT += ans[i] * (1 << i);

    cout << ansT << endl;
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