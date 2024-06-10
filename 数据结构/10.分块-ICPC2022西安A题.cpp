/**
 * Created by YXH_XianYu on 2023.8.22
 * Blog: https://yxhxianyu.fun
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'

/*
block len: B
O(nB + n*n/B) => B = sqrt(n)
*/

const int B = sqrt(1e5);

void work() {
	int n, m, q;
	cin >> n >> m >> q;

	vector<array<int, 3>> opt(q + 1);
	int Q = 0;
	vector<array<int, 3>> a(q + 1);
	for(int i = 1; i <= q; i++) {
		cin >> opt[i][0] >> opt[i][1];
		if(opt[i][0] == 1) {
			cin >> opt[i][2];
			a[++Q] = {opt[i][1], opt[i][2], i};
		}
	}

	vector<int> pos(q + 1);
	sort(a.begin() + 1, a.begin() + Q + 1, [&](const array<int, 3>& a, const array<int, 3>& b) {
		if(a[1] != b[1]) return a[1] < b[1];
		return a[0] < b[0];
	});
	for(int i = 1; i <= Q; i++) pos[a[i][2]] = i;

	int N = (Q - 1) / B + 1;
	vector<int> L(N + 10), R(N + 10), bel(Q + 10);
	for(int i = 1; i <= Q; i++) {
		bel[i] = (i - 1) / B + 1;
		if(L[bel[i]] == 0) L[bel[i]] = i;
		R[bel[i]] = i;
	}

	vector<vector<int>> P(N + 10, vector<int>(n + 10));
	for(int i = 1; i <= N; i++) {
		for(int j = 1; j <= n; j++) {
			P[i][j] = j;
		}
	}

	vector<int> vis(Q + 10);
	for(int i = 1; i <= q; i++) {
		if(opt[i][0] == 2) {
			int x = opt[i][1];
			for(int i = 1; i <= N; i++) x = P[i][x];
			cout << x << endl;
		} else if(opt[i][0] == 1) {
			int p = pos[i];
			int b = bel[p];
			vis[p] = 1;
			for(int j = L[b]; j <= R[b]; j++) if(vis[j]) {
				P[b][a[j][0]] = a[j][0];
				P[b][a[j][0] + 1] = a[j][0] + 1;
			}
			for(int j = R[b]; j >= L[b]; j--) if(vis[j]) {
				swap(P[b][a[j][0]], P[b][a[j][0] + 1]);
			}
		} else assert(false);
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
