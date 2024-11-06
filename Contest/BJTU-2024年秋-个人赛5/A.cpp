#include<bits/stdc++.h>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    std::string s;
    std::cin >> s;
    int n = s.size();

    const int T = 3;
    std::array<int, T> base = {31, 37, 41};
    std::array<int, T> mod = {19997, 1999997, (int)(1e9 + 7)};
    std::array<std::vector<int>, T> p {std::vector<int>(n), std::vector<int>(n), std::vector<int>(n)};
    std::array<std::vector<int>, T> f {std::vector<int>(n), std::vector<int>(n), std::vector<int>(n)};

    for (int t = 0; t < T; t++) {
        f[t][0] = s[0] - 'a' + 1;
        for (int i = 1; i < n; i++) {
            f[t][i] = (1LL * f[t][i - 1] * base[t] + s[i] - 'a' + 1) % mod[t];
        }

        p[t][0] = 1;
        for (int i = 1; i < n; i++) {
            p[t][i] = 1LL * p[t][i - 1] * base[t] % mod[t];
        }
    }

    int m;
    std::cin >> m;
    for (int i = 0; i < m; i++) {
        int L1, R1, L2, R2;
        std::cin >> L1 >> R1 >> L2 >> R2;

        L1 -= 1;
        R1 -= 1;
        L2 -= 1;
        R2 -= 1;

        if (R1 - L1 != R2 - L2) {
            std::cout << "No" << '\n';
            continue;
        }

        bool is_same = true;
        for (int t = 0; t < T; t++) {
            int v1 = 0, v2 = 0;

            v1 = f[t][R1];
            if (L1 > 0) v1 -= 1LL * f[t][L1 - 1] * p[t][R1 - L1 + 1] % mod[t];
            if (v1 < 0) v1 += mod[t];

            v2 = f[t][R2];
            if (L2 > 0) v2 -= 1LL * f[t][L2 - 1] * p[t][R2 - L2 + 1] % mod[t];
            if (v2 < 0) v2 += mod[t];

            // std::cout << t << ", " << v1 << ", " << v2 << '\n';

            if (v1 != v2) {
                is_same = false;
                break;
            }
        }

        if (is_same) {
            std::cout << "Yes" << '\n';
        } else {
            std::cout << "No" << '\n';
        }
    }

    return 0;
}
