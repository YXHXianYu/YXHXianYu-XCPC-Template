/**
 * Created by YXH_XianYu on 2023.9
 * Blog: https://yxhxianyu.fun
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'


void work() {

	auto solve = [&](int n, int k) -> int {
		int ans = 0;

		vector<vector<int>> f(k + 1, vector<int>(k + 1));
		f[1][1] = 1;
		for(int i = 2; i <= k; i++) {
			f[i][1] = 1;
			int d = 1 << k - i;
			for(int j = 1 + d; j <= k; j += d) {
				f[i][j] = f[i][j - d] + f[i-1][j];
			}
		}

		

	};

	int n = 10;
	int k = 20;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= k; j++) {
			cout << solve(i, j) << " ";
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