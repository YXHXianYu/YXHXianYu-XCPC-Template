#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
const int maxn = 2e5 + 10;


void work() {
	int n, q;
	cin >> n >> q;

	vector<vector<array<int, 2>>> e(n + 1, vector<array<int, 2>>());
	for(int i = 1; i < n; i++) {
		int u, v, w;
		cin >> u >> v >> w;

		e[u].push_back({v, w});
		e[v].push_back({u, w});
	}

	int lim = __lg(n);

	vector<int> dep(n + 1);
	vector<vector<int>> fa(lim + 1, vector<int>(n + 1));
	vector<vector<int>> mndis(lim + 1, vector<int>(n + 1));

	function<void(int)> dfs = [&](int x) {
		for(auto pr: e[x]) {
			int y = pr[0];
			if(y == fa[0][x]) continue;

			dep[y] = dep[x] + 1;
			fa[0][y] = x;
			mndis[0][y] = pr[1];
			
			dfs(y);
		}
	};

	dep[1] = 1;
	fa[0][1] = 0;
	mndis[0][1] = 0;
	dfs(1);

	for(int k = 1; k <= lim; k++) {
		for(int x = 1; x <= n; x++) {
			fa[k][x] = fa[k-1][fa[k-1][x]];
			mndis[k][x] = min(mndis[k-1][x], mndis[k-1][fa[k-1][x]]);
		}
	}

	auto query = [&](int u, int v) {
		int ans = 1LL << 60;
		if(dep[u] > dep[v]) swap(u, v);
		// dep[u] <= dep[v]
		int d = dep[v] - dep[u];
		for(int j = lim; j >= 0; j--) if(d >> j & 1) {
			ans = min(ans, mndis[j][v]);
			v = fa[j][v];
		}
		if(u == v) return ans;
		for(int j = lim; j >= 0; j--) if(fa[j][u] != fa[j][v]) {
			ans = min(ans, mndis[j][u]);
			ans = min(ans, mndis[j][v]);
			u = fa[j][u];
			v = fa[j][v];
		}
		ans = min(ans, mndis[0][u]);
		ans = min(ans, mndis[0][v]);
		return ans;
	};
	
	for(int i = 1; i <= q; i++) {
		int u, v;
		cin >> u >> v;
		cout << query(u, v) << endl;
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
