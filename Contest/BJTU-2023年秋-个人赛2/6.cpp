#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'

void work() {
    string s;
    cin >> s;
    int n = s.size();
    s = " " + s;

    string t;
    cin >> t;
    int m = t.size();
    t = " " + t;

    vector<vector<int>> a(n + 1, vector<int>(26));
    for(int i = n - 1; i >= 0; i--) {
        for(int j = 0; j <= 25; j++) a[i][j] = a[i + 1][j];
        a[i][s[i + 1] - 'a'] = i + 1;
    }

    int cnt = 1;
    int p = 0;
    for(int i = 1; i <= m; i++) {
        if(a[p][t[i] - 'a'] == 0) {
            if(p == 0) {
                cout << -1 << endl;
                return;
            } else {
                p = 0;
                cnt += 1;
                i--;
            }
        } else {
            p = a[p][t[i] - 'a'];
        }
    }

    cout << cnt << endl;
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