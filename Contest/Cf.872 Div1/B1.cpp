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
int invf[maxn];

int C(int n, int m) {
	return fac[n] * invf[m] % MOD * invf[n - m] % MOD;
}


int n, k;
vector<int> e[maxn];

int ans = 0;

int sz[maxn];
int f[maxn];
void dfs(int x, int fa) {
	sz[x] = 1;
	f[x] = 0;
	for(auto y: e[x]) {
		if(y == fa) continue;
		
		
		dfs(y, x);
		sz[x] = (sz[x] + sz[y]) % MOD;
		f[x] = (f[x] + f[y] + sz[y]) % MOD;
	}
	ans = (ans + f[x]) % MOD;
//	cout << x << ": " << f[x] << ", " << sz[x] << endl;
}

void dfs2(int x, int fa, int v) {
	ans = (ans + v) % MOD;
	
//	cout << " - " << x << ": " << v << endl;
	
	int g = v;
	for(auto y: e[x]) {
		if(y == fa) continue;
		g = (g + f[y] + sz[y]) % MOD;
	}
	for(auto y: e[x]) {
		if(y == fa) continue;
		int t = (g - f[y] - sz[y] + MOD + MOD) % MOD;
		dfs2(y, x, (t + n - sz[y]) % MOD);
	}
	
}

void work() {
	
	cin >> n >> k;
	for(int i = 1; i < n; i++) {
		int u, v;
		cin >> u >> v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	
	if(k == 1 || k == 3) {
		cout << 1 << endl;
		return;
	}
	
	if(n == 1) {
		cout << 1 << endl;
		return;
	}
	
	dfs(1, 0);
	
	fac[0] = 1;
	for(int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % MOD;
	invf[n] = Inv(fac[n]);
	for(int i = n - 1; i >= 0; i--) invf[i] = invf[i + 1] * (i + 1) % MOD;
	
	dfs2(1, 0, 0);
	
	ans = ans * Inv(2) % MOD;
	
	int cn2 = C(n, 2);
	
//	cout << ans << ", " << cn2 << endl;
	
	ans = (ans + cn2) % MOD;
	
	ans = ans * Inv(cn2) % MOD;
	
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
