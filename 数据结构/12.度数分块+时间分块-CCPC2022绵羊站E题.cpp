/**
 * Created by YXH_XianYu on 2023.8.22
 * Blog: https://yxhxianyu.fun
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'

// int B = sqrt(2*1e5*17);
int B = sqrt(1e5);
// int B = 1;
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

	auto flush = [&]() {
		for(int i = 1; i <= n; i++) {
			if(deg[i] > B) {
				nth_element(e[i].begin(), e[i].begin() + B, e[i].end(),
					[&](const array<int, 2>& a, const array<int, 2>& b) {
						return f[a[0]] + a[1] < f[b[0]] + b[1];
					}
				);
			}
		}
	};
	flush();

	vector<int> b(q + 1);
	const int INF = 1LL << 60;
	for(int i = 1; i <= q; i++) cin >> b[i];
	for(int i = q; i >= 1; i--) {
		int x = b[i];
		f[x] = INF;
		for(int j = 0, lim = min(deg[x], B); j < lim; j++)
			f[x] = min(f[x], f[e[x][j][0]] + e[x][j][1]);
		if(i % B == 0) flush();
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
