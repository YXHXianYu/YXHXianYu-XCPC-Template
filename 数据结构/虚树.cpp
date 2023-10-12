/**
 * Created by YXH_XianYu in 2023.10
 * Blog: https://yxhxianyu.fun
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'


void work() {
	int n;
	cin >> n;

	vector<vector<array<int, 2>>> e(n + 1, vector<array<int, 2>>());
	for(int i = 1; i < n; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		e[u].push_back({v, w});
		e[v].push_back({u, w});
	}

	/* 树链剖分 LCA */
	const int INF = 1LL << 30;
	vector<int> sz(n + 1), fa(n + 1), son(n + 1), dep(n + 1);
	vector<int> dfn(n + 1), dfnR(n + 1), rk(n + 1), top(n + 1);
	vector<int> dis(n + 1);

	function<void(int)> dfs1 = [&](int x) {
		dep[x] = dep[fa[x]] + 1;
		sz[x] = 1;
		for(auto [y, w]: e[x]) {
			if(y == fa[x]) continue;
			fa[y] = x;
			dis[y] = min(dis[x], w);
			dfs1(y);
			sz[x] += sz[y];
			if(sz[son[x]] < sz[y]) son[x] = y;
		}
	};
	function<void(int)> dfs2 = [&](int x) {
		dfn[x] = ++dfn[0];
		rk[dfn[0]] = x;
		if(!top[x]) top[x] = x;
		if(son[x]) top[son[x]] = top[x], dfs2(son[x]);
		for(auto [y, w]: e[x]) if(y != fa[x] && y != son[x]) dfs2(y);
		dfnR[x] = dfn[0];
	};

	dis[1] = INF;
	dfs1(1);
	dfs2(1);

	auto getLca = [&](int x, int y) {
		while(top[x] != top[y]) {
			if(dep[top[x]] > dep[top[y]]) swap(x, y);
			y = fa[top[y]];
		}
		if(dep[x] > dep[y]) swap(x, y);
		return x;
	};

	// 虚树

	vector<int> mp(n + 1);
	vector<int> tag(n + 1);

	int m;
	cin >> m;

	for(int i = 1; i <= m; i++) {
		int N;
		cin >> N;
		vector<int> b(N);
		for(int j = 0; j < N; j++) cin >> b[j];

		auto a = b;
		for(auto x: a) tag[x] = 1;

		// build 虚树

		sort(b.begin(), b.end(), [&](int u, int v) {
			return dfn[u] < dfn[v];
		});
		b.push_back(1);
		for(int j = 1; j < N; j++) b.push_back(getLca(b[j - 1], b[j]));
		sort(b.begin(), b.end(), [&](int u, int v) {
			return dfn[u] < dfn[v];
		});

		b.erase(unique(b.begin(), b.end()), b.end());
		N = b.size();
		vector<vector<array<int, 2>>> E(N + 1, vector<array<int, 2>>());

		for(int i = 0; i < N; i++) mp[b[i]] = i + 1;

		// for(int i = 0; i < N; i++) cout << b[i] << " "; cout << endl;

		for(int i = 1; i < N; i++) {
			int u = b[i - 1];
			int v = b[i];
			int lca = getLca(u, v);
			if(lca == v) continue;
			E[mp[lca]].push_back({mp[v], dis[v]});
			E[mp[v]].push_back({mp[lca], dis[v]});
		}

		// solve

		vector<int> f(N + 1);
		function<void(int, int)> dfs = [&](int x, int fa) {
			for(auto [y, w]: E[x]) {
				if(y == fa) continue;
				if(tag[b[y - 1]]) {
					f[x] += w;
				} else {
					dfs(y, x);
					f[x] += min(w, f[y]);
				}
			}
		};

		dfs(1, 0);
		cout << f[1] << endl;

		for(auto x: a) tag[x] = 0;
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