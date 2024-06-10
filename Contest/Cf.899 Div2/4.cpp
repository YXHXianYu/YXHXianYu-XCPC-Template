/**
 * Created by YXH_XianYu in 2023.9
 * Blog: https://yxhxianyu.fun
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'


void work() {
	int n;
	cin >> n;

	vector<int> a(n + 1);
	for(int i = 1; i <= n; i++) cin >> a[i];

	vector<vector<int>> e(n + 1, vector<int>());
	for(int i = 1; i < n; i++) {
		int u, v;
		cin >> u >> v;
		e[u].push_back(v);
		e[v].push_back(u);
	}

	vector<int> ans(n + 1);
	for(int B = 0; B <= 19; B++) {
		vector<int> b(n + 1);
		for(int i = 1; i <= n; i++) b[i] = a[i] >> B & 1;
		
		vector<int> sz(n + 1);
		vector<int> f(n + 1);
		function<void(int, int)> dfs1 = [&](int x, int fa) {
			sz[x] = 1;
			for(auto y: e[x]) {
				if(y == fa) continue;
				dfs1(y, x);
				sz[x] += sz[y];
				f[x] += f[y];
				if(b[y] ^ b[x]) f[x] += sz[y];
			}
		};
		dfs1(1, 0);

		// if(B == 0) for(int i = 1; i <= n; i++) {
		// 	cout << i << ": " << sz[i] << ", " << f[i] << endl;
		// }

		vector<int> g(n + 1);
		g[1] = f[1];

		function<void(int, int, int)> dfs2 = [&](int x, int fa, int v) {
			if(fa != 0) {
				g[x] += v;
				if(b[fa] ^ b[x]) g[x] += n - sz[x];
				for(auto y: e[x]) {
					if(y == fa) continue;
					g[x] += f[y];
					if(b[y] ^ b[x]) g[x] += sz[y];
				}
			}
			for(auto y: e[x]) {
				if(y == fa) continue;
				dfs2(y, x, g[x] - f[y] - (b[y] ^ b[x]) * sz[y]);
			}
		};
		dfs2(1, 0, 0);

		for(int i = 1; i <= n; i++) {
			ans[i] += g[i] * (1LL << B);
		}
	}

	for(int i = 1; i <= n; i++) cout << ans[i] << " "; cout << endl;
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