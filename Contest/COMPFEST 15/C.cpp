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

	vector<vector<array<int, 2>>> e(n + 1, vector<array<int, 2>>());
	vector<vector<int>> E(n + 1, vector<int>());

	for(int i = 1; i <= n; i++) {
		int sz;
		cin >> sz;

		e[i].resize(sz);
		for(int j = 0; j < sz; j++) {
			cin >> e[i][j][0] >> e[i][j][1];
			E[e[i][j][0]].push_back(i);
		}
	}

	vector<int> outdeg(n + 1);
	for(int i = 1; i <= n; i++) {
		outdeg[i] = e[i].size();
	}

	vector<int> q(n + 1);
	int tl = 0;
	for(int i = 1; i <= n; i++) {
		if(outdeg[i] == 0) {
			q[++tl] = i;
		}
	}

	vector<array<int, 3>> f(n + 1);

	const int MOD = 998244353;
	
	auto upd = [&](int& a, int b) {
		a += b;
		if(a >= MOD) a -= MOD;
	};

	/*
	f[x][0]: 以x为起点的0的个数
	f[x][1]: 以x为起点的1的个数
	*/

	for(int i = 1; i <= tl; i++) {
		int x = q[i];
		// solve
		for(int j = e[x].size() - 1; j >= 0; j--) {
			int y = e[x][j][0];
			int w = e[x][j][1];

			if(w == 1) {
				upd(f[x][2], (f[x][0] + f[y][0]) % MOD);
				upd(f[x][2], f[y][1] * f[x][0] % MOD);
				upd(f[x][1], 1);
			} else {
				upd(f[x][2], f[y][1] * f[x][0] % MOD);
				upd(f[x][0], 1);
			}
			upd(f[x][0], f[y][0]);
			upd(f[x][1], f[y][1]);
			upd(f[x][2], f[y][2]);
		}

		// cout << x << ": " << f[x][0] << ", " << f[x][1] << ", " << f[x][2] << endl;
		
		// topo
		for(auto y: E[x]) {
			if(--outdeg[y] == 0) {
				q[++tl] = y;
			}
		}
	}

	cout << f[1][2] << endl;
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