#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;


void work() {
	int n;
	cin >> n;

	vector<int> a(n + 1);
	for(int i = 1; i <= n; i++) {
		cin >> a[i];
	}

	int cnt = 0;
	int s = 0;
	int ans = 0;
	for(int i = 1; i <= n; i++) {
		if(a[i] < 0) cnt += 1;
		s += a[i];
	}

	while(s < 0) {
		ans += 1;
		s += 2;
		cnt += 1;
	}

	// cout << ans << ", " << cnt << ", " << s << endl;

	if(cnt & 1) ans += 1;

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
