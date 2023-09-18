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

	if(n == 2) {
		cout << 0 << endl;
		return;
	}

	const int MOD = 998244353;

	int ans = 0;

	auto upd = [&](int& a, int b) {
		a += b;
		if(a >= MOD) a -= MOD;
	};

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

	int N = max(n, m);
	vector<int> fac(N + 1), inv(N + 1);
	fac[0] = 1;
	for(int i = 1; i <= N; i++) fac[i] = fac[i - 1] * i % MOD;
	inv[N] = Inv(fac[N]);
	for(int i = N - 1; i >= 0; i--) inv[i] = inv[i + 1] * (i + 1) % MOD;

	auto C = [&](int n, int m) {
		if(n < m) return 0ll;
		return fac[n] * inv[m] % MOD * inv[n - m] % MOD;
	};

	int cnt = 0;
	for(int i = 0; i <= n - 3; i++) {
		upd(cnt, C(n - 3, i));
	}

	for(int i = n - 1; i <= m; i++) {
		int v = cnt * (i - 1) % MOD * C(i - 2, n - 3) % MOD;
		upd(ans, v);
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