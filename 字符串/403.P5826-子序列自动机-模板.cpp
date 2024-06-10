/**
 * Created by YXH_XianYu in 2023.10
 * Blog: https://yxhxianyu.fun
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'


void work() {
	int type, n, q, m;
	cin >> type >> n >> q >> m;

	vector<int> a(n + 1);
	for(int i = 1; i <= n; i++) cin >> a[i];

	vector<vector<int>> b(m + 1, vector<int>());

	for(int i = 1; i <= n; i++) {
		b[a[i]].push_back(i);
	}

	for(int i = 1; i <= q; i++) {
		int N;
		cin >> N;
		vector<int> x(N + 1);
		for(int j = 1; j <= N; j++) cin >> x[j];
        int p = 0, j;
		for(j = 1; j <= N; j++) {
			auto it = upper_bound(b[x[j]].begin(), b[x[j]].end(), p);
			if(it == b[x[j]].end()) break;
			else p = *it;
		}
		cout << (j <= N ? "No" : "Yes") << endl;
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