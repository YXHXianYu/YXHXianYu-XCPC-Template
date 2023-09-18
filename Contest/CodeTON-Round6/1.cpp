/**
 * Created by YXH_XianYu on 2023.9
 * Blog: https://yxhxianyu.fun
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'


void work() {
	int n, k, x;
	cin >> n >> k >> x;

	if(x <= k - 2) {
		cout << -1 << endl;
		return;
	}
	if(n <= k - 1) {
		cout << -1 << endl;
		return;
	}

	int ans = (0 + k - 1) * k / 2;
	n -= k;

	if(x <= k) {
		ans += n * (k - 1);
	} else {
		ans += n * x;
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