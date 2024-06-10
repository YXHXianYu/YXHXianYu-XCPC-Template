/**
 * Created by YXH_XianYu on 2023.9
 * Blog: https://yxhxianyu.fun
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'


void work() {
	int n;
	cin >> n;

	vector<int> fa(n + 1);
	vector<vector<int>> e(n + 1, vector<int>());
	for(int i = 1; i <= n; i++) {
		cin >> fa[i];

		if(i > 1) e[fa[i]].push_back(i);
	}

	function<int(int)> dfs = [&](int x) -> int {
		if(e[x].size() == 0) {
			return 1;
		}
		int mx = 0, mx2 = 0;
		for(auto y: e[x]) {
			int v = dfs(y);
			if(v > mx) {
				mx2 = mx;
				mx = v;
			} else if(v > mx2) {
				mx2 = v;
			}
		}
		// cout << x << ": " << 1 + max(mx - 1, mx2) << endl;
		return 1 + max(mx - 1, mx2);
	};

	int ans = dfs(1);

	cout << ans << endl;
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int t = 1;
	cin >> t;
	while(t--) {
		work();
	}
	
	return 0;
}