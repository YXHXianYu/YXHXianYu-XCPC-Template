/**
 * Created by YXH_XianYu on 2023.8.31
 * Blog: https://yxhxianyu.fun
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'


void work() {
	int n, k;
	cin >> n >> k;

	vector<int> a(n + 1);
	for(int i = 1; i <= n; i++) cin >> a[i];

	sort(a.begin() + 1, a.end());

	vector<int> pk(100);
	int N = 0;
	pk[0] = 1;
	for(int i = 1; pk[i-1] * k <= 10000000000000000LL; i++) {
		pk[i] = pk[i-1] * k;
		N = i;
	}

	vector<int> vis(100);
	for(int i = 1; i <= n; i++) {
		int x = a[i];
		for(int j = N; j >= 0; j--) {
			if(x >= pk[j]) {
				x -= pk[j];
				if(vis[j]) {
					cout << "NO" << endl;
					return;
				}
				vis[j] = 1;
			}
		}
		if(x) {
			cout << "NO" << endl;
			return;
		}
	}

	cout << "YES" << endl;
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