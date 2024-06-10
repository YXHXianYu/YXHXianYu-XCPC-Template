#include<bits/stdc++.h>
using namespace std;
#define int long long

void work() {
    int n, m, K;
    cin >> n >> m >> K;

    vector<array<int, 7>> a(m);
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < 7; j++) cin >> a[i][j];
    }

    vector<int> q(n);

    int ans = 0;

    auto check = [&]() {
        int cnt = 0;
        for(int i = 0; i < m; i++) {
            int v = a[i][3] * q[a[i][0] - 1] + a[i][4] * q[a[i][1] - 1];
            if(a[i][2] == 0) {
                if(v <= a[i][5]) cnt += a[i][6];
            } else {
                if(v >= a[i][5]) cnt += a[i][6];
            }
        }
        ans = max(ans, cnt);
    };

    function<void(int)> dfs = [&](int k) {
        if(k >= n) {
            check();
            return;
        }

        for(int i = 0; i <= K; i++) {
            q[k] = i;
            dfs(k + 1);
        }
    };
    dfs(0);

    cout << ans << '\n';
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