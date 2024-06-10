#include <bits/stdc++.h>
 
using i64 = long long;
 
void solve() {
    int n;
    std::cin >> n;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    int lim = 300000*20;
    
    std::vector<bool> e(lim);
    
    std::vector<int> l;
    for (int i = 0; i < n; i++) {
        std::vector<int> nl;
        if (a[i] < lim) {
            nl.push_back(a[i]);
        }
        for (auto x : l) {
            i64 v = std::lcm(1LL * x, 1LL * a[i]);
            if (v < lim) {
                nl.push_back(v);
            }
        }
        std::sort(nl.begin(), nl.end());
        nl.erase(std::unique(nl.begin(), nl.end()), nl.end());
        l = nl;
        std::cout << i << ": ";
        for(auto x: l) std::cout << x << " ";
        std::cout << std::endl;
        for (auto x : l) {
            e[x] = true;
        }
    }
    
    int ans = 1;
    while (e[ans]) {
        ans++;
    }
    
    std::cout << ans << "\n";
}
 
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int t;
    std::cin >> t;
    
    while (t--) {
        solve();
    }
    
    return 0;
}