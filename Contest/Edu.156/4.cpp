/**
 * Created by YXH_XianYu in 2023.10
 * Blog: https://yxhxianyu.fun
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'


void work() {
	int n, m;
	cin >> n >> m;

	string s;
	cin >> s;
	s = " " + s;

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

	vector<int> inv(n + 1);
	inv[1] = 1;
	for(int i = 2; i <= n; i++) {
		inv[i] = (MOD - MOD / i) * inv[MOD % i] % MOD;
	}

	int ans = 1;
	for(int i = 1; i < n; i++) {
		if(i >= 2 && s[i] == '?') {
			ans = ans * (i - 1) % MOD;
		}
	}

	auto output = [&]() {
		cout << (s[1] == '?' ? 0ll : ans) << endl;
	};

	output();

	for(int i = 1; i <= m; i++) {
		int id; char ch;
		cin >> id >> ch;
		
		if(id >= 2 && s[id] == '?') ans = ans * inv[id - 1] % MOD;
		s[id] = ch;
		if(id >= 2 && s[id] == '?') ans = ans * (id - 1) % MOD;

		output();
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