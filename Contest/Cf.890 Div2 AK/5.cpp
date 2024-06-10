#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;


void work() {
	int n;
	cin >> n;
	
	vector<vector<int>> e(n + 1, vector<int>());
	vector<int> fa(n + 1);
	for(int i = 2; i <= n; i++) {
		cin >> fa[i];
		e[fa[i]].push_back(i);
	}

	int ans = 0;
	vector<int> sz(n + 1);

	function<void(int)> dfs = [&](int x) {
		vector<int> a;
		for(auto y: e[x]) {
			dfs(y);
			a.push_back(sz[y]);
			sz[x] += sz[y];
		}
		if(a.size() <= 1) {
			sz[x] += 1;
			return;
		}

		int sz2 = sz[x] / 2;
		vector<int> f(sz2 + 5);

		int lim = 0;
		f[0] = 1;
		for(int i = 0; i < a.size(); i++) {
			auto g = f;
			for(int j = 0; j <= lim; j++) {
				if(g[j] == 1) {
					if(j + a[i] <= sz2) f[j + a[i]] = 1;
				}
			}
			lim = min(lim + a[i], sz2);
		}

		int cnt = 0;
		for(int i = lim; i >= 0; i--) {
			if(f[i] == 1) {
				ans += i * (sz[x] - i);
				// cout << x << ": " << i << " * " << sz[x] - i << endl;
				break;
			}
		}

		sz[x] += 1;
	};

	dfs(1);

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
