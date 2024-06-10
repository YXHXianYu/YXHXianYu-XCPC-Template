/**
 * Created by YXH_XianYu on 2023.9
 * Blog: https://yxhxianyu.fun
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'


void work() {
	freopen("data.txt", "w", stdout);
	srand(time(0));

	auto random = [&](int l, int r) {
		return rand() % (r - l + 1) + l;
	};

	int t = 100000;
	int n = 100;

	cout << t << endl;
	for(int i = 1; i <= t; i++) {
		// cout << n << endl;
		for(int j = 1; j <= n; j++) {
			cout << ((char)(random('a', 'b')));
		}
		cout << endl;
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