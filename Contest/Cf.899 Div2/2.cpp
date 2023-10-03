/**
 * Created by YXH_XianYu in 2023.9
 * Blog: https://yxhxianyu.fun
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'


void work() {
	int n;
	cin >> n;

	map<int, int> f;
	vector<vector<int>> a(n + 1, vector<int>());
	for(int i =1; i <= n; i++) {
		int x;
		cin >> x;
		a[i].resize(x);
		for(int j = 0; j < x; j++) {
			cin >> a[i][j];
			f[a[i][j]] += 1;
		}
	}

	int ans = 0;
	for(int i = 1; i <= n; i++) {
		int cnt = f.size();
		for(int j = 0; j < a[i].size(); j++) {
			if(f[a[i][j]] == 1) {
				cnt -= 1;
			}
		}
		if(cnt == f.size()) continue;
		ans = max(ans, cnt);
	}

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