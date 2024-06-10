#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'

void work() {
	const int MOD = 998244353;
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
	auto upd = [&](int& a, int b) {
		a += b;
		if(a >= MOD) a -= MOD;
	};
	
	int n;
	cin >> n;
	
	vector<int> inv(n + 1);
	inv[1] = 1;
	for(int i = 2; i <= n; ++i) {
		inv[i] = (MOD - MOD/i*inv[MOD % i] % MOD);
	}
	
	vector<array<int, 2>> a(n + 1);
	for(int i = 1; i < n; i++) {
		cin >> a[i][0] >> a[i][1];
	}
	
	vector<vector<int>> e(n + 1, vector<int>());
	for(int i = 1; i < n; i++) {
		int u, v;
		cin >> u >> v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	
	vector<int> f(n + 1);
	for(int i = 1; i <= n; i++) f[i] = i;
	
	vector<int> sz(n + 1), deg(n + 1);
	for(int i = 1; i <= n; i++) sz[i] = 1;
	for(int i = 1; i <= n; i++) deg[i] = e[i].size();
	
	function<int(int)> find = [&](int x) {
		return (f[x] == x ? x : f[x] = find(f[x]));
	};
	auto merge = [&](int x, int y) {
		f[y] = x;
		sz[x] += sz[y];
		deg[x] += deg[y];
	};
	
	int ans = 1;
	for(int i = 1; i < n; i++) {
		int u = find(a[i][0]);
		int v = find(a[i][1]);
		
		if(deg[u] > deg[v]) swap(u, v);
		// deg[u] <= deg[v]
		
		int flag = 0;
		
		for(auto x: e[u]) {
			if(find(x) == v) {
				flag = 1;
			} else {
				e[v].push_back(x);
			}
		}
		
		if(flag == 0) {
			cout << 0 << endl;
			return;
		}
		
		ans = ans * inv[sz[u]] % MOD * inv[sz[v]] % MOD;
		
		merge(v, u);
	}
	
	cout << ans << endl;
//	cout << ans<<" "<<Inv(80)  << endl;
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
