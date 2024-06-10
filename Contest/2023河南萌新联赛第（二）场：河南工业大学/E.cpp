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

	vector<int> x(n + 1);
	for(int i = 1; i <= n; i++) cin >> x[i];

	vector<int> d(n + 1);
	for(int i = 1; i <= n; i++) {
		d[max(1ll, i-x[i])] += 1;
		d[i] -= 1;
		d[min(n + 1, i+1)] += 1;
		d[min(n + 1, i+x[i]+1)] -= 1;
	}

	int ans = 0;
	int cnt = 0;
	for(int i = 1; i <= n; i++) {
		cnt += d[i];
		if(cnt > 0) ans++;
	}
	cout << ans << endl;
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