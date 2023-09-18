/**
 * Created by YXH_XianYu on 2023.8.29
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

	vector<int> pos(n + 1);
	for(int i = 1; i <= n; i++) pos[a[i]] = i;

	int ans = 0;
	for(int i = 2; i <= n; i++) {
		if(pos[i - 1] > pos[i]) {
			ans++;
		}
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