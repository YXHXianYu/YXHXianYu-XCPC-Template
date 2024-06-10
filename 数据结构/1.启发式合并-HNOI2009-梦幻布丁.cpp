#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'


void work() {
	int n, m;
	cin >> n >> m;

	vector<int> a(n + 2); // for a[0] & a[n + 1]
	for(int i = 1; i <= n; i++) cin >> a[i];

	vector<vector<int>> p(1000000 + 1, vector<int>());
	for(int i = 1; i <= n; i++) {
		p[a[i]].push_back(i);
	}

	int ans = 1;
	for(int i = 2; i <= n; i++) ans += a[i] != a[i - 1];

	for(int T = 1; T <= m; T++) {
		int opt;
		cin >> opt;
		if(opt == 1) {
			int x, y;
			cin >> x >> y;
			if(x == y) continue;

			if(p[x].size() > p[y].size()) swap(p[x], p[y]);
			if(p[y].size() == 0) continue;

			for(auto z: p[x]) {
				ans -= a[z] != a[z - 1];
				ans -= a[z] != a[z + 1];
				a[z] = a[p[y][0]];
				ans += a[z] != a[z - 1];
				ans += a[z] != a[z + 1];
				p[y].push_back(z);
			}
			p[x].clear();

		} else if(opt == 2) {
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
