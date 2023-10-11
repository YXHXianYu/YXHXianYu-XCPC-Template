/**
 * Created by YXH_XianYu in 2023.10
 * Blog: https://yxhxianyu.fun
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'


void work() {
	int n, p;
	cin >> n >> p;

	vector<array<int, 2>> a(n + 1);
	for(int i = 1; i <= n; i++) cin >> a[i][0];
	for(int i = 1; i <= n; i++) cin >> a[i][1];

	sort(a.begin() + 1, a.end(), [&](array<int, 2> a, array<int, 2> b) {
		if(a[1] != b[1]) return a[1] < b[1];
		return a[0] > b[0];
	});

	int ans = p;
	int cnt = n - 1;
	for(int i = 1; i <= n; i++) {
		if(a[i][1] < p) {
			if(cnt < a[i][0]) {
				ans += cnt * a[i][1];
				cnt = 0;
				break;
			} else {
				cnt -= a[i][0];
				ans += a[i][0] * a[i][1];
			}
		} else {
			break;
		}
	}

	ans += cnt * p;

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