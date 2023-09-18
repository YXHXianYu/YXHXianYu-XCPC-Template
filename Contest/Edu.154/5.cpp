/**
 * Created by YXH_XianYu on 2023.8.31
 * Blog: https://yxhxianyu.fun
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'


void work() {
	int n, k;
	cin >> n >> k;

	const int MOD = 998244353;

	vector<vector<int>> f(2, vector<int>(k + 1));

	auto upd = [&](int &a, int b) {
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

	int ans = 0;
	int S = 0;
	f[S][0] = 1;
	for(int i = 1; i <= n; i++) {
		int T = S ^ 1;
		for(int j = 0; j <= k; j++) f[T][j] = 0;

		// j == 0
		upd(f[T][1], f[S][0] * k % MOD);
		// j >= 1 && j < k
		for(int j = 1; j < k; j++) upd(f[T][j], f[S][j]);
		for(int j = k - 1; j >= 2; j--) upd(f[T][j - 1], f[T][j]);
		for(int j = 1; j < k; j++) upd(f[T][j + 1], f[S][j] * (k - j) % MOD);
		// j == k
		upd(f[T][1], f[S][k] * k % MOD);

		S = T;

		upd(ans, f[S][k] * Pow(k, n - i) % MOD);
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