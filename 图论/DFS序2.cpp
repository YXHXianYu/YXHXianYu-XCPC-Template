#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'

/**
 * DFS序2：单点修改、查询子树和、换根
 * DFS序的换根分三种情况考虑：① root=x，整颗树；
 * ② root在x的子树中，
*/
void work() {
	int n, q;
	cin >> n >> q;

	vector<vector<int>> e(n + 1, vector<int>());
	for(int i = 1; i < n; i++) {
		int u, v;
		cin >> u >> v;
		e[u].push_back(v);
		e[v].push_back(u);
	}

	// dfn & fa

	int lim = __lg(n);
	vector<int> dfn(n + 1), dfnR(n + 1), dep(n + 1);
	vector<vector<int>> fa(lim + 1, vector<int>(n + 1));

	function<void(int)> dfs = [&](int x) {
		dfn[x] = ++dfn[0];
		for(auto y: e[x]) {
			if(y == fa[0][x]) continue;

			dep[y] = dep[x] + 1;
			fa[0][y] = x;
			dfs(y);
		}
		dfnR[x] = dfn[0];
	};

	dep[1] = 1;
	dfs(1);

	for(int k = 1; k <= lim; k++) {
		for(int i = 1; i <= n; i++) {
			fa[k][i] = fa[k-1][fa[k-1][i]];
		}
	}

	// bit
	
	vector<int> bit(n + 1);
	#define lowbit(x) (x&-x)
	auto add = [&](int x, int v) {
		for(; x <= n; x += lowbit(x)) bit[x] += v;
	};
	auto query = [&](int x) {
		int ans = 0; for(; x; x -= lowbit(x)) ans += bit[x]; return ans;
	};

	// solve

	vector<int> a(n + 1);
	for(int i = 1; i <= n; i++) {
		cin >> a[i];
		add(dfn[i], a[i]);
	}

	int root = 1;

	for(int i = 1; i <= q; i++) {
		int opt;
		cin >> opt;
		if(opt == 1) {
			int x, y;
			cin >> x >> y;
			add(dfn[x], -a[x]);
			a[x] = y;
			add(dfn[x], a[x]);

		} else if(opt == 2) {
			int x;
			cin >> x;
			int ans;
			if(x == root) {
				ans = query(n);
			} else if(dfn[x] <= dfn[root] && dfn[root] <= dfnR[x]) {
				// root在x的子树内
				int p = root;
				for(int j = lim; j >= 0; j--) {
					if(dep[fa[j][p]] > dep[x])
						p = fa[j][p];
				}
				ans = query(n) - (query(dfnR[p]) - query(dfn[p] - 1));
			} else {
				ans = query(dfnR[x]) - query(dfn[x] - 1);
			}
			cout << ans << endl;

		} else if(opt == 3) {
			cin >> root;

		} else assert(false);
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
