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

	auto solve = [&](int x) {
		while(x >= 0) {
			cout << x << endl;
			cout.flush();
			cin >> x;
		}
	};

	for(int i = 1, j = 0; i <= n; i++, j++) {
		if(a[i] != j) {
			solve(j);
			return;
		}
	}
	solve(n);
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