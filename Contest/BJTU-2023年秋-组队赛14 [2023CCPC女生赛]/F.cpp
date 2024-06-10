#include<bits/stdc++.h>
using namespace std;
#define int long long

int read() {
    int ans = 0; char ch = getchar();
    while(ch < '0' || '9' < ch) ch = getchar();
    while('0' <= ch && ch <= '9') ans = ans * 10 + ch - '0', ch = getchar();
    return ans;
}

void work() {
    int n;
    cin >> n;

    vector<int> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];

    int lim = 0;
    for(int i = 0; i < n; i++) lim = max(lim, a[i]);

    vector<vector<int>> b(lim + 1, vector<int>());
    for(int i = 0; i < n; i++) {
        b[a[i]].push_back(i);
    }

    int mn = n + 1;
    if(b[1].size() == 0) {
        cout << -1 << '\n';
        return;
    }
    for(auto j: b[1]) mn = min(mn, j);
    for(int i = 2; i <= lim; i++) {
        if(b[i].size() == 0) {
            cout << -1 << endl;
            return;
        }
        for(auto j: b[i]) {
            if(j < mn) {
                cout << -1 << '\n';
                return;
            }
        }
        mn = n + 1;
        for(auto j: b[i]) {
            mn = min(mn, j);
        }
    }

    vector<int> ans(n);
    int cnt = 0;
    for(int i = 1; i <= lim; i++) {
        for(int j = b[i].size() - 1; j >= 0; j--) {
            ans[b[i][j]] = ++cnt;
        }
    }

    for(auto x: ans) cout << x << " ";
    cout << '\n';
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