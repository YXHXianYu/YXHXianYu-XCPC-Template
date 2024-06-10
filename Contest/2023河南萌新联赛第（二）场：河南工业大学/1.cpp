/**
 * Created by YXH_XianYu on 2023.8.31
 * Blog: https://yxhxianyu.fun
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'


void work() {
	int n, q, k;
	cin >> n >> q >> k;

	vector<int> a(n + 1);
	for(int i = 1; i <= n; i++) cin >> a[i];

	vector<int> b(n + 1);
	for(int i = 1; i <= n; i++) cin >> b[i];

	vector<int> s(n + 1);
	for(int i = 1; i <= n; i++) s[i] = s[i - 1] + a[i];

	int cnt = 0;
	int sum = 0;
	vector<int> ans(n + 1);
	for(int i = 1; i <= n; i++) {
		if(i > 1 && b[i - 1] < b[i]) {
			cnt = 1;
			sum += a[i];
			ans[i] = sum;
		} else {
			// cout << i << ": " << cnt << ", " << sum << ", " << k << endl;
			cnt += 1;
			sum += a[i];
			if(cnt >= k) {
				cnt = k;
				sum = s[i] - s[i - k];
			}
			ans[i] = sum;
		}
	}

	while(q--) {
		int x;
		cin >> x;
		cout << ans[x] << endl;
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