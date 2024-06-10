#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;


void work() {
	int n;
	cin >> n;

	vector<int> m(n + 1);
	vector<vector<int>> a(n + 1, vector<int>());
	vector<int> c;
	const int INF = 1LL << 60;
	int mn = INF;
	for(int i = 1; i <= n; i++) {
		cin >> m[i];
		a[i].resize(m[i] + 1);
		for(int j = 1; j <= m[i]; j++) cin >> a[i][j];
		sort(a[i].begin() + 1, a[i].begin() + m[i] + 1);
		c.push_back(a[i][2]);
		mn = min(mn, a[i][1]);
	}

	if(n == 1) {
		cout << mn << endl;
		return;
	}

	sort(c.begin(), c.end());
	int sum = 0;
	for(int i = 1; i < c.size(); i++) sum += c[i];
	sum += mn;

	cout << sum << endl;
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
