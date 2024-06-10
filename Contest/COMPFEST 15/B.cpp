/**
 * Created by YXH_XianYu on 2023.9
 * Blog: https://yxhxianyu.fun
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'


void work() {
	int n;
	cin >> n;

	vector<int> a(n + 1), b(n + 1);
	for(int i = 1; i <= n; i++) cin >> a[i];
	for(int i = 1; i <= n; i++) cin >> b[i];

	int m;
	cin >> m;

	vector<int> c(m + 1), d(m + 1);
	for(int i = 1; i <= m; i++) cin >> c[i];
	for(int i = 1; i <= m; i++) cin >> d[i];

	const int MOD = 998244353;

	vector<int> f(n + 1);
	int j = 1;
	for(int i = 1; i <= n && j <= m; i++) {
		if(a[i] == c[j]) {
			f[i] = d[j];
			j++;
		}
	}

	if(j <= m) {
		cout << 0 << endl;
		return;
	}

	int ans = 1;
	for(int i = 1; i <= n; i++) {
		if(b[i] < f[i]) {
			cout << 0 << endl;
			return;
		} else if(b[i] > f[i]) {
			ans <<= 1;
			if(ans >= MOD) ans -= MOD;
		}
	}

	cout << ans << endl;
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