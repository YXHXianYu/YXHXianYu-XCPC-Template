#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'

void work() {
    int n, x;
    cin >> n >> x;

    string s;
    cin >> s;
    s = " " + s;

    int cnt = 0;
    for(int i = 1; i <= n; i++) {
        cnt += (s[i] == '0' ? 1 : -1);
    }

    if(cnt == 0) {
        for(int i = 1; i <= n; i++) {
            cnt += (s[i] == '0' ? 1 : -1);
            if(cnt == x) {
                cout << -1 << endl;
                return;
            }
        }
        cout << 0 << endl;
        return;
    }

    int cnt2 = 0;
    int ans = (x == 0);
    for(int i = 1; i <= n; i++) {
        cnt2 += (s[i] == '0' ? 1 : -1);
        int d = x - cnt2;
        if(d == 0) {
            ans += 1;
        } else if(d > 0) {
            if(cnt > 0 && d % cnt == 0) ans += 1;
        } else if(d < 0) {
            if(cnt < 0 && (-d) % (-cnt) == 0) ans += 1;
        }
    }
    cout << ans << endl;
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