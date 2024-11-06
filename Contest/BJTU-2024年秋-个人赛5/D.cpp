#include<bits/stdc++.h>
using i64 = long long;

void work() {
    int n = 13;
    int m = 4;

    std::vector<std::vector<int>> a(n, std::vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char ch;
            std::cin >> ch;
            if (ch == '0') {
                a[i][j] = 10;
            } else if ('2' <= ch && ch <= '9') {
                a[i][j] = ch - '0';
            } else if (ch == 'A') {
                a[i][j] = 1;
            } else if (ch == 'J') {
                a[i][j] = 11;
            } else if (ch == 'Q') {
                a[i][j] = 12;
            } else if (ch == 'K') {
                a[i][j] = 13;
            } else {
                assert(false);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            a[i][j] -= 1;
        }
    }

    std::vector<int> cnt(n);
    int p = n - 1;

    while(true) {
        if (p == n - 1 && cnt[p] == m) {
            break;
        }
        cnt[p] += 1;
        p = a[p][m - cnt[p]];
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (cnt[i] == m) {
            ans += 1;
        }
    }
    ans -= 1;
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
