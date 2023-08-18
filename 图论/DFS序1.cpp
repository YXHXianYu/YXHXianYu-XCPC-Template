#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'

/**
 * DFS序1：单点修改、查询子树和、查询根到任意点路径权值之和
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

	vector<int> dfn(n + 1), dfnR(n + 1);

	function<void(int, int)> dfs = [&](int x, int fa) {
		dfn[x] = ++dfn[0];
		for(auto y: e[x]) {
			if(y == fa) continue;
			dfs(y, x);
		}
		dfnR[x] = dfn[0];
	};
	dfs(1, 0);

	// bit
	vector<int> bit1(n + 1);
	#define lowbit(x) (x&-x)
	auto add1 = [&](int x, int v) {
		for(; x <= n; x += lowbit(x)) bit1[x] += v;
	};
	auto query1 = [&](int x) {
		int ans = 0; for(; x; x -= lowbit(x)) ans += bit1[x]; return ans;
	};
	// bit2
	vector<int> bit2(n + 1);
	#define lowbit(x) (x&-x)
	auto add2 = [&](int x, int v) {
		for(; x <= n; x += lowbit(x)) bit2[x] += v;
	};
	auto query2 = [&](int x) {
		int ans = 0; for(; x; x -= lowbit(x)) ans += bit2[x]; return ans;
	};

	// for(int i = 1; i <= n; i++)
	// 	cout << i << ": " << dfn[i] << ", " << dfnR[i] << endl;

	vector<int> a(n + 1);
	for(int i = 1; i <= n; i++) {
		cin >> a[i];
		add1(dfn[i], a[i]);
		add2(dfn[i], a[i]);
		add2(dfnR[i] + 1, -a[i]);
	}

	for(int i = 1; i <= q; i++) {
		int opt;
		cin >> opt;
		if(opt == 1) {
			int x, y;
			cin >> x >> y;
			add1(dfn[x], -a[x]);
			add2(dfn[x], -a[x]);
			add2(dfnR[x] + 1, a[x]);
			a[x] = y;
			add1(dfn[x], a[x]);
			add2(dfn[x], a[x]);
			add2(dfnR[x] + 1, -a[x]);
		} else if(opt == 2) {
			int x;
			cin >> x;
			cout << query1(dfnR[x]) - query1(dfn[x] - 1) << " " << query2(dfn[x]) << endl;
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
