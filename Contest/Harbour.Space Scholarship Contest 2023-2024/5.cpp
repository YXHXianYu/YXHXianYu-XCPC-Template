#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'

const int MOD = 998244353;

int Pow(int a, int n) {
	int ans = 1;
	while(n) {
		if(n & 1) ans = ans * a % MOD;
		a = a * a % MOD;
		n >>= 1;
	}
	return ans;
}
int Inv(int a) {
	return Pow(a, MOD - 2);
}

// const int MAXN = 100;
// vector<int> fac(MAXN + 1);
// vector<int> inv(MAXN + 1);

// int P(int n, int m) {
// 	assert(n >= m);
// 	return fac[n] * inv[n - m] % MOD;
// }

void work() {
	int n;
	cin >> n;

	vector<int> a(n + 1);
	for(int i = 1; i <= n; i++) cin >> a[i];

	vector<array<int, 2>> t(n * 31 + 1);
	vector<int> sz(n * 31 + 1);
	int tot = 1;

	for(int i = 1; i <= n; i++) {
		int x = a[i];
		int p = 1;
		for(int j = 29; j >= 0; j--) {
			int e = x >> j & 1;
			if(t[p][e] == 0) {
				t[p][e] = ++tot;
				if(tot >= t.size()) {
					t.resize(t.size() * 2);
				}
			}
			p = t[p][e];
		}
		sz[p] += 1;
	}

	int ans = 0;
	function<void(int, int, int)> dfs = [&](int x, int k, int cnt) {
		if(k == 0) {
			int va = ((cnt + 1 >> 1) << 1) + 1;
			int vb = ((cnt >> 1) << 1) + 2;
			ans = (ans + (va < vb ? va : vb) % MOD * sz[x] % MOD * sz[x] % MOD) % MOD;
			return;
		}

		if(t[x][0]) dfs(t[x][0], k - 1, cnt);
		if(t[x][1]) dfs(t[x][1], k - 1, cnt + 1);
		if(t[x][0] && t[x][1]) {
			int va = ((cnt + 1 >> 1) << 1) + 1;
			int vb = ((cnt >> 1) << 1) + 2;
			ans = (ans + (va + vb) % MOD * sz[t[x][0]] % MOD * sz[t[x][1]] % MOD) % MOD;
		}
		sz[x] = (sz[x] + sz[t[x][0]] + sz[t[x][1]]) % MOD;
	};

	dfs(1, 30, 0);

	ans = ans * Inv(n * n % MOD) % MOD;

	cout << ans << endl;
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	// fac[0] = 1;
	// for(int i = 1; i <= MAXN; i++) fac[i] = fac[i - 1] * i % MOD;
	// inv[MAXN] = Inv(fac[MAXN]);
	// for(int i = MAXN - 1; i >= 0; i--) inv[i] = inv[i + 1] * (i + 1) % MOD;
	// assert(inv[0] == 1);
	
	int t = 1;
	cin >> t;
	while(t--) {
		work();
	}
	
	return 0;
}
