/**
 * Created by YXH_XianYu on 2023.8.22
 * Blog: https://yxhxianyu.fun
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'

int B = sqrt(2*1e5*17);
// int B = sqrt(1e5);
// int B = 1;
// O(2m + q(B + 2m/B*logn + logn))
// B => sqrt(2mlogn)

void work() {
	int n, m, q;
	cin >> n >> m >> q;

	vector<int> a(n + 1);
	for(int i = 1; i <= n; i++) cin >> a[i];

	vector<vector<array<int, 2>>> e(n + 1, vector<array<int, 2>>());
	vector<int> deg(n + 1);
	for(int i = 1; i <= m; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		e[u].push_back({v, w});
		e[v].push_back({u, w});
		deg[u]++, deg[v]++;
	}


	vector<int> f(n + 1);
	vector<multiset<int>> g(n + 1);
	vector<vector<array<int, 2>>> adj(n + 1, vector<array<int, 2>>());
	for(int i = 1; i <= n; i++) {
		if(deg[i] > B) {
			for(auto [y, w]: e[i]) {
				g[i].insert(w);
				adj[y].push_back({i, w});
			}
		}
	}

	vector<int> b(q + 1);
	const int INF = 1LL << 60;
	for(int i = 1; i <= q; i++) cin >> b[i];
	for(int i = q; i >= 1; i--) {
		int x = b[i];
		if(deg[x] <= B) {
			int ans = INF;
			for(auto [y, w]: e[x]) ans = min(ans, f[y] + w);
			for(auto [y, w]: adj[x]) g[y].erase(g[y].find(f[x] + w)), g[y].insert(ans + w);
			f[x] = ans;
		} else {
			int ans = *g[x].begin();
			for(auto [y, w]: adj[x]) g[y].erase(g[y].find(f[x] + w)), g[y].insert(ans + w);
			f[x] = ans;
		}
	}
	int ans = 0;
	const int MOD = 998244353;
	for(int i = 1; i <= n; i++) {
		ans += f[i] % MOD * a[i] % MOD;
		if(ans >= MOD) ans -= MOD;
	}
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
