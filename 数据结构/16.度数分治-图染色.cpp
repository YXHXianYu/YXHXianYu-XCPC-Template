/**
 * Created by YXH_XianYu on 2023.8.23
 * Blog: https://yxhxianyu.fun
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'


void work() {
	int n, m, q;
	cin >> n >> m >> q;

	vector<vector<int>> e(n + 1, vector<int>());
	vector<int> deg(n + 1);
	for(int i = 1; i <= m; i++) {
		int u, v;
		cin >> u >> v;
		e[u].push_back(v);
		e[v].push_back(u);
		deg[u]++, deg[v]++;
	}

	vector<vector<int>> E(n + 1, vector<int>());

	const int B = sqrt(2 * 4e5);
	// O(q * (2m/B + B)) => B = sqrt(2m)

	for(int x = 1; x <= n; x++) {
		if(deg[x] > B) for(auto y: e[x]) {
			E[y].push_back(x);
		}
	}

	vector<int> col(n + 1);
	vector<int> f(n + 1);
	while(q--) {
		int opt, x;
		cin >> opt >> x;
		if(opt == 1) {
			col[x] ^= 1;
			for(auto y: E[x]) {
				f[y] += col[x] ? 1 : -1;
			}

		} else if(opt == 2) {
			int ans = 0;
			if(deg[x] <= B) {
				for(auto y: e[x]) ans += col[y];
			} else {
				ans = f[x];
			}
			cout << ans << endl;

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
