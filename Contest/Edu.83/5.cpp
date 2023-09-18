/**
 * Created by YXH_XianYu on 2023.9.7
 * Blog: https://yxhxianyu.fun
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'


void work() {
	int n;
	cin >> n;

	vector<int> a(n + 1);
	for(int i = 1; i <= n; i++) cin >> a[i];

	const int INF = 1LL << 60;
	vector<vector<int>> f(n + 1, vector<int>(n + 1, INF));

	for(int i = 1; i <= n; i++) f[i][i] = a[i];

	for(int len = 2; len <= n; len++) {
		for(int j = len; j <= n; j++) {
			int i = j - len + 1;

			for(int k = i; k < j; k++) {
				if(f[i][k] == f[k + 1][j] && f[i][k] != INF) {
					f[i][j] = f[i][k] + 1;
				}
			}
		}
	}

	vector<int> g(n + 1);
	g[0] = 0;
	g[1] = 1;
	for(int i = 1; i <= n; i++) {
		g[i] = i;
		for(int j = 0; j < i; j++) {
			if(f[j + 1][i] != INF)
				g[i] = min(g[i], g[j] + 1);
		}
	}

	cout << g[n] << endl;
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