/**
 * Created by YXH_XianYu on 2023.9
 * Blog: https://yxhxianyu.fun
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'


void work() {
	int n, m;
	cin >> n >> m;

	vector<int> a(n + 1);
	for(int i = 1; i <= n; i++) cin >> a[i];

	vector<int> b(m + 1);
	for(int i = 1; i <= m; i++) cin >> b[i];

	int mn = 0, mx = 0;

	if(n & 1) {
		for(int i = 1; i <= n; i++) mx ^= a[i];
		for(int i = 1; i <= m; i++) {
			for(int j = 30; j >= 0; j--) {
				if(b[i] >> j & 1) {
					mx |= 1 << j;
				}
			}
		}

		for(int i = 1; i <= n; i++) mn ^= a[i];
	} else {
		for(int i = 1; i <= n; i++) mx ^= a[i];

		for(int i = 1; i <= n; i++) mn ^= a[i];
		for(int i = 1; i <= m; i++) {
			for(int j = 30; j >= 0; j--) {
				if(b[i] >> j & 1) {
					if(mn >> j & 1) {
						mn ^= 1 << j;
					}
				}
			}
		}
	}

	cout << mn << " " << mx << endl;


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