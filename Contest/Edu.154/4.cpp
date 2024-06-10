/**
 * Created by YXH_XianYu on 2023.8.31
 * Blog: https://yxhxianyu.fun
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'


void work() {
	int n;
	cin >> n;

	vector<int> a(n + 1);
	for(int i = 1; i <= n; i++) cin >> a[i];

	if(n == 1) {
		cout << "0" << endl;
		return;
	}

	vector<int> f(n + 1); // last up
	vector<int> g(n + 1); // first down

	f[n] = 0;
	for(int i = n - 1; i >= 1; i--) {
		if(a[i] >= a[i + 1]) f[i] = f[i + 1] + 1;
		else f[i] = f[i + 1];
	}
	g[1] = 0;
	for(int i = 2; i <= n; i++) {
		if(a[i-1] <= a[i]) g[i] = g[i - 1] + 1;
		else g[i] = g[i - 1];
	}

	int ans = min(f[1], g[n] + 1);
	for(int i = 1; i < n; i++) {
		ans = min(ans, g[i] + 1 + f[i + 1]);
	}
	for(int i = 2; i < n; i++) {
		ans = min(ans, g[i - 1] + 2 + f[i + 1]);
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