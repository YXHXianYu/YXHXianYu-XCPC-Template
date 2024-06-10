/**
 * Created by YXH_XianYu on 2023.9
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

	vector<array<int, 2>> b(n + 1);
	for(int i = 1; i <= n; i++) b[i] = {a[i], i};

	sort(b.begin() + 1, b.end());
	
	vector<int> ans(n + 1);
	for(int i = 1; i <= n; i++) ans[b[i][1]] = n - i + 1;

	for(int i = 1; i <= n; i++) cout << ans[i] << " "; cout << endl;
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