/**
 * Created by YXH_XianYu on 2023.8.31
 * Blog: https://yxhxianyu.fun
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'


void work() {
	int n, p;
	cin >> n >> p;

	vector<int> a(n + 1);
	for(int i = 1; i <= n; i++) cin >> a[i];

	int l = -1, r = 0;
	for(int i = 1; i <= n; i++) r = max(r, a[i]);

	auto check = [&](int md) {
		int sum = 0;
		for(int i = 1; i <= n; i++) {
			if(a[i] > md) {
				sum += 2 * (a[i] - md);
			}
		}
		return sum >= p;
	};

	while(r - l >= 2) {
		int mid = l + r >> 1;
		if(check(mid)) {
			l = mid;
		} else {
			r = mid;
		}
	}

	cout << l << endl;
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