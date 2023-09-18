/**
 * Created by YXH_XianYu on 2023.8.30
 * Blog: https://yxhxianyu.fun
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'


void work() {
	int n, m, k;
	cin >> n >> m >> k;

	vector<int> h(n + 1);
	for(int i = 1; i <= n; i++) cin >> h[i];

	const int INF = 1LL << 60;

	vector<vector<int>> e(n + 1, vector<int>());
	vector<int> indeg(n + 1);
	vector<int> tag(n + 1, 1);
	for(int i = 1; i <= m; i++) {
		int u, v;
		cin >> u >> v;

		e[v].push_back(u);
		indeg[u]++;
		tag[v] = 0;
	}

	vector<int> f(n + 1);
	for(int i = 1; i <= n; i++) f[i] = h[i];

	vector<int> q(n + 1);
	int tl = 0;

	for(int i = 1; i <= n; i++) if(indeg[i] == 0) {
		q[++tl] = i;
	}

	for(int i = 1; i <= tl; i++) {
		int x = q[i];
		for(auto y: e[x]) {
			int v = f[x] + (h[y] > h[x] ? k : 0);
			if(v > f[y]) f[y] = v;

			if(--indeg[y] == 0) {
				q[++tl] = y;
			}
		}
	}
	
	vector<array<int, 2>> ans(n + 1, {INF, -1});

	for(int i = 1; i <= n; i++) {
		if(tag[i]) {
			ans[i][0] = h[i];
			ans[i][1] = f[i];
		}
	}

	sort(ans.begin() + 1, ans.begin() + n + 1);


	int N = 0;
	for(int i = 1; i <= n; i++) {
		if(ans[i][0] == INF) break;
		N = i;
	}

	int ansT = INF;
	int mn = ans[1][0];
	int mx = ans[1][1];
	for(int i = 2; i <= N; i++) {
		mx = max(mx, ans[i][1]);
	}
	ansT = mx - mn;

	for(int i = 2; i <= N; i++) {
		mn = ans[i][0];
		assert(mn < k);
		mx = max(mx, ans[i - 1][1] + k);

		ansT = min(ansT, mx - mn);
	}

	cout << ansT << endl;
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