/**
 * Created by YXH_XianYu on 2023.9
 * Blog: https://yxhxianyu.fun
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'


void work() {
	int n, k;
	cin >> n >> k;

	vector<int> a(n + 1);
	for(int i = 1; i <= n; i++) cin >> a[i];

	vector<int> f(n + 1);
	for(int i = 1; i <= n; i++) f[i] = 1;

	vector<vector<int>> p(k + 1, vector<int>());
	for(int i = 1; i <= n; i++) {
		p[a[i]].push_back(i);
	}

	const int INF = 1LL << 60;
	int L = INF;
	int R = 0;

	vector<int> ans(k + 1);
	for(int i = k; i >= 1; i--) {
		for(auto j: p[i]) {
			L = min(L, j);
			R = max(R, j);
		}
		ans[i] = (p[i].size() == 0 ? 0 : 2 * (R - L + 1));
	}

	for(int i = 1; i <= k; i++) cout << ans[i] << " ";
	cout << endl;
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