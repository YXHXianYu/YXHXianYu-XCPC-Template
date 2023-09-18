#include<bits/stdc++.h>
using namespace std;
#define int long long

void work() {
    int n, k, s;
    cin >> n >> k >> s;

    const int INF = 1LL << 60;

    int mna1 = INF;
    int mnsum = INF;
    int s_mod_k1 = s % (k + 1);

    for(int a1 = 0; a1 <= k; a1++) {
        int sum = 0;

        int p1 = n / (k + 1);
        int p2 = n % (k + 1);
        
        sum += p1 * k * (k + 1) / 2;

        if(p2 <= k - a1 + 1) {
            sum += (a1 + a1 + p2 - 1) * p2 / 2;
        } else {
            sum += (a1 + k) * (k - a1 + 1) / 2;
            p2 -= k - a1 + 1;
            sum += (p2 - 1) * p2 / 2;
        }

        if(sum % (k + 1) != s_mod_k1) continue;
        if(sum > s) continue;
        mna1 = a1;
        mnsum = sum;
        break;
    }

    if(mna1 == INF) {
        cout << -1 << endl;
        return;
    }

    // cout << mna1 << ", " << mnsum << endl;
    
    vector<int> ans(n + 1);
    ans[1] = mna1;
    for(int i = 2; i <= n; i++) {
        ans[i] = (ans[i - 1] + 1) % (k + 1);
    }

    // mnsum <= s
    int v1 = mnsum / (k + 1);
    int v2 = s / (k + 1);

    v2 -= v1;

    if(v2 >= n) {
        int t = v2 / n;
        for(int i = 1; i <= n; i++) ans[i] += (k + 1) * t;
        v2 -= n * t;
    }
    
    vector<array<int, 2>> b(n + 1);
    for(int i=  1; i <= n; i++) {
        b[i] = {ans[i], i};
    }
    sort(b.begin() + 1, b.end());
    for(int i = 1; i <= v2; i++) {
        ans[b[i][1]] += k + 1;
    }

    for(int i = 1; i <= n; i++) cout << ans[i] << " ";
    cout << endl;

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
