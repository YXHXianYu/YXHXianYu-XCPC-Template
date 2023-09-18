#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;
const int MOD = 1e9 + 7;


void work() {

    int n;
    cin >> n;

    vector<int> a(n + 2);
    vector<int> b(n + 2);

    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = 1; i <= n; i++) cin >> b[i];

    sort(a.begin() + 1, a.begin() + n + 1);
    sort(b.begin() + 1, b.begin() + n + 1);

    int ans = 1;
    int L, R;

    for(L = 1, R = 0; L <= n; L++) {
        while(R < n && b[R + 1] < a[L]) {
            R++;
        }
        if(R - L + 1 <= 0) {
            cout << "0" << endl;
            return;
        }
        ans = ans * (R - L + 1) % MOD;
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