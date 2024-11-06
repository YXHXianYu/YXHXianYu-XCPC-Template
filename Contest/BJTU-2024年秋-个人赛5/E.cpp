#include<bits/stdc++.h>
using i64 = long long;

void work() {

    int n;
    std::cin >> n;
    std::vector<std::vector<int>> a(n, std::vector<int>(n));
    std::vector<std::vector<int>> s(n, std::vector<int>(n));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cin >> a[i][j];
            s[i][j] = a[i][j];
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 1; j < n; j++) {
            s[i][j] += s[i][j - 1];
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 1; j < n; j++) {
            s[j][i] += s[j - 1][i];
        }
    }

    auto get = [&](int i, int j, int i1, int j1) {
        int ans = s[i1][j1];
        if (i > 0) {
            ans -= s[i - 1][j1];
        }
        if (j > 0) {
            ans -= s[i1][j - 1];
        }
        if (i > 0 && j > 0) {
            ans += s[i - 1][j - 1];
        }
        return ans;
    };

    const int INF = 1 << 30;
    int ans = -INF;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int i1 = i; i1 < n; i1++) {
                for (int j1 = j; j1 < n; j1++) {
                    ans = std::max(ans, get(i, j, i1, j1));
                }
            }
        }
    }

    std::cout << ans << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    int t = 1;
    // std::cin >> t;
    while (t--) {
        work();
    }

    return 0;
}
