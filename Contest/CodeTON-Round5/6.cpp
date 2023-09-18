#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;


void work() {
	int n;
	cin >> n;
	
	vector<vector<int>> e(n + 1, vector<int>());
	for(int i = 1; i < n; i++) {
		int u, v;
		cin >> u >> v;
		e[u].push_back(v);
		e[v].push_back(u);
	}

	vector<int> ans(n + 1);

	const auto solve = [&](int rt) {
		vector<int> dep(n + 1);
		vector<int> vis(n + 1);
		int cnt = 0;

		queue<pair<int, int>> q;
		q.push({rt, 0});
		vis[rt] = 1;
		while(!q.empty()) {
			auto [x, d] = q.front();
			q.pop();
			dep[++cnt] = d;
			for(auto y: e[x]) {
				if(vis[y]) continue;
				q.push({y, d + 1});
				vis[y] = 1;
			}
		}
		// cout << "rt = " << rt << ": ";
		// for(int i = 1; i <= n; i++) cout << dep[i] << " ";
		// cout << endl;
		int sum = 0;
		for(int i = 1; i <= n; i++) {
			sum += 2 * dep[i];
			ans[i] = max(ans[i], (n - 1) * i - sum);
		}
	};


	for(int i = 1; i <= n; i++) {
		solve(i);
	}

	cout << 0 << " ";
	for(int i = 1; i <= n; i++) cout << ans[i] << " ";
	cout << endl;
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
