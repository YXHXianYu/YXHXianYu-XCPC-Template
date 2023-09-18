#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;


void work() {
	int n;
	cin >> n;

	vector<int> p(n + 1);
	for(int i = 1; i <= n; i++) p[i] = i;
	swap(p[n - 1], p[n]);

	int ans = 0;
	for(int i = 1; i <= n; i++) {
		int sum = 0;
		int mx = 0;
		for(int j = 1; j < i; j++) p[j] = j;
		for(int j = i, k = n; j <= n; j++, k--) p[j] = k;
		for(int j = 1; j <= n; j++) sum += p[j] * j, mx = max(mx, p[j] * j);
		ans = max(ans, sum - mx);
		// cout << i << ": " << sum << "-" << mx << "=" << sum-mx << endl;
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
