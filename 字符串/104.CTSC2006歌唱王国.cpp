/**
 * Created by YXH_XianYu on 2023.9
 * Blog: https://yxhxianyu.fun
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'


void work() {
	int m, t;
	cin >> m >> t;

	const int MOD = 1e4;
	auto Pow = [&](int a, int n) {
		int ans = 1;
		while(n) {
			if(n & 1) ans = ans * a % MOD;
			a = a * a % MOD;
			n >>= 1;
		}
		return ans;
	};
	auto upd = [&](int& a, int b) {
		a += b;
		if(a >= MOD) a -= MOD;
	};

	while(t--) {
		int n;
		cin >> n;

		vector<int> a(n + 1);
		for(int i = 1; i <= n; i++) cin >> a[i];

		vector<int> pi(n + 1);
		for(int i = 2, j = 0; i <= n; i++) {
			while(j && a[j + 1] != a[i]) j = pi[j];
			if(a[j + 1] == a[i]) j += 1;
			pi[i] = j;
		}

		int ans = 0;
		for(int i = n; i; i = pi[i]) {
			upd(ans, Pow(m, i));
		}
		int dig = 0;
		for(int x = ans; x; x /= 10, dig += 1);
		for(int i = dig + 1; i <= 4; i++) cout << 0;
		cout << ans << endl;
	}
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