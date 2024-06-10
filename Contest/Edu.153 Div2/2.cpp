#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'


void work() {
	int m, k, a1, ak;
	cin >> m >> k >> a1 >> ak;

	int ans = 0;

	int d = m % k;
	int d2 = m / k;
	if(d <= a1) {
		a1 -= d;
		ak += a1 / k;
	} else {
		ans += d - a1;
	}

	d2 = max(d2 - ak, 0ll);

	ans += d2;

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
