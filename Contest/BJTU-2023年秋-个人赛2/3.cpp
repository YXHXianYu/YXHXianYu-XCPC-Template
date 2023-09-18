#include<bits/stdc++.h>
using namespace std;
#define int long long

void work() {
    int n;
    cin >> n;

    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];

    vector<int> cnt(n + 1);
    int mx = 0;
    int cnt0 = 0;
    for(int i = 1; i <= n; i++) {
        if(cnt[a[i]] == 0) cnt0++;
        cnt[a[i]] += 1;
        mx = max(mx, cnt[a[i]]);
    }

    cout << max(min(cnt0 - 1, mx), min(cnt0, mx - 1)) << endl;
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