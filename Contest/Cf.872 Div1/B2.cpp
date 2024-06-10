#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;
const int MOD = 1e9 + 7;

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

int fac[maxn];
int invfac[maxn];
int C(int n, int m) {
	if(n < m) return 0;
	return fac[n] * invfac[m] % MOD * invfac[n - m] % MOD;
}

void work() {
	
	int n, k;
	cin >> n >> k;
	
	std::vector<std::vector<int>> e(n);
	for(int i = 1; i < n; i++) {
		int u, v;
		cin >> u >> v;
		u--, v--;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	
	fac[0] = 1;
	for(int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % MOD;
	invfac[n] = Inv(fac[n]);
	for(int i = n - 1; i >= 0; i--) invfac[i] = invfac[i + 1] * (i + 1) % MOD;
	
	if(k&1) {
		cout << 1 << endl;
		return;
	}
	
	int ans = 0;
	
	vector<int> sz(n);
	
	function<void(int, int)> dfs = [&](int x, int fa) {
		sz[x] = 1;
		for(auto y: e[x]) {
			if(y == fa) continue;
			dfs(y, x);
			sz[x] += sz[y];
			ans = (ans + C(sz[y], k / 2) * C(n - sz[y], k / 2) % MOD) % MOD;
		}
	};
	
	dfs(0, -1);
	
	int cnk = C(n, k);
	
	ans = (ans + cnk) * Inv(cnk) % MOD;
	
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
