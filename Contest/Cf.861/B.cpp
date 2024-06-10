#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 3e5 + 10;

int n, m;
vector<int> c[maxn];

void work() {
	
	cin >> n >> m;
	for(int i = 1; i <= m; i++) {
		c[i].resize(n + 1);
	}
	
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			cin >> c[j][i];
		}
	}
	
	for(int i = 1; i <= m; i++) {
		sort(c[i].begin() + 1, c[i].end());
	}
	
//	for(int i = 1; i <= m; i++) {
//		for(int j = 1; j <= n; j++) {
//			cout << c[i][j] << " ";
//		}
//		cout << endl;
//	}
	
	int ans = 0;
	for(int i = 1; i <= m; i++) {
		int cnt = 0;
		for(int j = 2; j <= n; j++) {
			cnt += c[i][j - 1];
			ans += c[i][j] * (j - 1) - cnt;
		}
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
