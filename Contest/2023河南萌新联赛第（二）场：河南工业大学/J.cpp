/**
 * Created by YXH_XianYu on 2023.8.31
 * Blog: https://yxhxianyu.fun
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'


void work() {
	int n, m;
	cin >> n >> m;

	string s;
	cin >> s;
	s = " " + s;

	int cnt0 = 0;
	int cnt1 = 0;
	for(int i = 1; i <= n; i++) (s[i] == '1' ? cnt1++ : cnt0++);

	if(cnt0 == 0 || cnt1 == 0) {
		if(m == 1) {
			cout << "1 0" << endl;
		} else {
			cout << "0 1" << endl;
		}
		return;
	}

	const int MOD = 1e9 + 7;

	auto Pow = [&](int a, int n) {
		int ans = 1;
		while(n) {
			if(n & 1) ans = ans * a % MOD;
			a = a * a % MOD;
			n >>= 1;
		}
		return ans;
	};
	auto Inv = [&](int a) {
		return Pow(a, MOD - 2);
	};

	vector<int> fac(n + 1), inv(n + 1);
	fac[0] = 1;
	for(int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % MOD;
	inv[n] = Inv(fac[n]);
	for(int i = n - 1; i >= 0; i--) inv[i] = inv[i + 1] * (i + 1) % MOD;
	assert(inv[0] == 1);

	auto C = [&](int n, int m) {
		if(n < m) return 0ll;
		return fac[n] * inv[m] % MOD * inv[n - m] % MOD;
	};
	auto upd = [&](int& a, int b) {
		a += b;
		if(a >= MOD) a -= MOD;
	};


	int ans1 = 0;
	int ans2 = 0;
	int lim = min(cnt0 + 1, cnt1);
	for(int i = 1; i <= lim; i++) {
		int v1 = C(cnt0 - 1, i) * C(cnt1 - 1, i - 1) % MOD;
		if(2*i+1 == m) {
			upd(ans1, v1);
		} else {
			upd(ans2, v1);
		}

		int v2 = 2 * C(cnt0 - 1, i - 1) * C(cnt1 - 1, i - 1) % MOD;
		if(2*i == m) {
			upd(ans1, v2);
		} else {
			upd(ans2, v2);
		}

		if(i >= 2) {
			int v3 = C(cnt0 - 1, i - 2) * C(cnt1 - 1, i - 1) % MOD;
			if(2*i-1 == m) {
				upd(ans1, v3);
			} else {
				upd(ans2, v3);
			}
		}
	}

	cout << ans1 << " " << ans2 << endl;
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