#include<bits/stdc++.h>

void work() {
    int mod;
    std::cin >> mod;

    int n;
    std::cin >> n;

    std::vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i] >> b[i];
    }

    int ans = 0;

    auto Pow = [&](int a, int n) {
        int ans = 1;
        while(n) {
            if (n & 1) ans = 1LL * ans * a % mod;
            a = 1LL * a * a % mod;
            n >>= 1;
        }
        return ans;
    };

    for (int i = 0; i < n; i++) {
        ans = (ans + Pow(a[i], b[i])) % mod;
    }

    std::cout << ans << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    int t = 1;
    std::cin >> t;
    while (t--) {
        work();
    }

    return 0;
}
