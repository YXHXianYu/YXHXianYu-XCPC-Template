/**
 * Created by YXH_XianYu in 2023.10
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
	vector<array<int, 2>> b(n + 1);
	for(int i = 1; i <= n; i++) {
		cin >> a[i];
		b[i][0] = a[i];
		b[i][1] = i;
	}

	const int MOD = 998244353;
	const int MAXN = 1e5;

	sort(b.begin() + 1, b.end(), [&](array<int, 2> a, array<int, 2> b) {
		if(a[0] != b[0]) return a[0] > b[0];
		return a[1] < b[1];
	});

	vector<vector<int>> f(n + 1, vector<int>());
	for(int i = 1; i <= n; i++) {
		int mxv = a[i];
		int p = i;
		for(int j = i + i; j <= n; j += i) {
			if(a[j] > mxv) {
				mxv = a[j];
				p = j;
			}
		}
		f[p].push_back(i);
	}

	vector<int> p2(n + 1);
	p2[0] = 1;
	for(int i = 1; i <= n; i++) p2[i] = p2[i - 1] * 2 % MOD;

	auto upd = [&](int &a, int b) {
		a += b;
		if(a >= MOD) a -= MOD;
	};

	int ans = 0;
	int cnt = n;
	for(int i = 1; i <= n; i++) {
		int id = b[i][1];
		cnt -= f[id].size();
		upd(ans, a[id] * (p2[f[id].size()] - 1 + MOD) % MOD * p2[cnt] % MOD);
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