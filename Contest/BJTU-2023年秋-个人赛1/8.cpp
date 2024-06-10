#include<bits/stdc++.h>
using namespace std;
#define int long long


void work() {
	int n;
	cin >> n;
	
	const int MOD = 998244353;
	
	auto Pow = [&](int a, int n) {
		int ans = 1;
		while(n) {
			if(n & 1) ans = ans * a % MOD;
			a = a * a % MOD;
			n >>= 1;
		}
		return ans;
	};
	auto Inv = [&](int a) {
		return Pow(a, MOD - 2);
	};
	
	vector<int> p10(n + 1);
	p10[0] = 1;
	for(int i = 1; i <= n; i++) p10[i] = p10[i - 1] * 10 % MOD;
	
	auto upd = [&](int &a, int b) {
		a += b;
		if(a >= MOD) a -= MOD;
	};
	
	vector<int> ans(max(n, 4ll) + 1);
	
	ans[1] = 10;
	ans[2] = 180;
	ans[3] = 2610;
	ans[4] = 34200;
	
	for(int i = 5; i <= n; i++) {
		upd(ans[i], 2 * 9 * p10[i - 2] % MOD);
		upd(ans[i], (i - 2) * 9 * 9 * p10[i - 3] % MOD);
		ans[i] = 10 * ans[i] % MOD;
	}
	
	for(int i = n; i >= 1; i--) cout << ans[i] << " "; cout << endl;
}

/*
10 180 2610 34200 423000 5040000
18, 14.5, 

10
10 * 2 * 9
10 * (1 * 9 * 9 + 2 * 9 * 10)
10 * (2 * 9 * 10 * 10 + 2 * 9 * 9 * 10)
10 * (

2 * 9 * 10^(n - 2)
2 * 9^2 * 

*/

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