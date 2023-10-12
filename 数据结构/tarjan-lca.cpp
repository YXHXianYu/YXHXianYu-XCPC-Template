/**
 * Created by YXH_XianYu in 2023.10
 * Blog: https://yxhxianyu.fun
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'


void work() {
	int n, m, rt;
	cin >> n >> m >> rt;

	vector<vector<int>> e(n + 1, vector<int>());
	for(int i = 1; i < n; i++) {
		int u, v;
		cin >> u >> v;
		e[u].push_back(v);
		e[v].push_back(u);
	}

	vector<int> dis(m + 1);
	vector<int> lca(m + 1);
	const int INF = 1LL << 30;

	vector<int> f(n + 1);
	for(int i = 1; i <= n; i++) f[i] = i;
	function<int(int)> find = [&](int x) {
		return (f[x] == x ? x : f[x] = find(f[x]));
	};

	vector<vector<array<int, 2>>> q(n + 1, vector<array<int, 2>>());
	for(int i = 1; i <= m; i++) {
		int u, v;
		cin >> u >> v;
		if(u == v) {
			dis[i] = 0;
			lca[i] = u;
		} else {
			q[u].push_back({v, i});
			q[v].push_back({u, i});
			dis[i] = INF;
		}
	}

	vector<int> v(n + 1), d(n + 1);
	function<void(int)> tarjan = [&](int x) {
		v[x] = 1;
		for(auto y: e[x]) {
			if(v[y]) continue;
			d[y] = d[x] + 1;
			tarjan(y);
			f[y] = x;
		}
		for(auto [y, id]: q[x]) {
			if(v[y] == 2) {
				lca[id] = find(y);
				dis[id] = min(dis[id], d[x] + d[y] - 2 * d[lca[id]]);
			}
		}
		v[x] = 2;
	};

	tarjan(rt);

	for(int i = 1; i <= m; i++) cout << lca[i] << endl;
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