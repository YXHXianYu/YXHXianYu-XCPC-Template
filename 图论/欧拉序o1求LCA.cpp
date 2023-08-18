#include<bits/stdc++.h>
using namespace std;
// #define endl '\n'

unsigned int A, B, C;
inline unsigned int rng61() {
    A ^= A << 16;
    A ^= A >> 5;
    A ^= A << 1;
    unsigned int t = A;
    A = B;
    B = C;
    C ^= t ^ A;
    return C;
}

#define int long long

/**
 * 欧拉序O(1)求LCA
*/
void work() {
	int n, m;
	cin >> n >> m >> A >> B >> C;

	vector<vector<int>> e(n + 1, vector<int>());
	for(int i = 1; i < n; i++) {
		int u, v;
		cin >> u >> v;
		e[u].push_back(v);
		e[v].push_back(u);
	}

	// euler
	int N = (n << 1) - 1;
	vector<int> euler(N + 1), pos(n + 1), dep(n + 1);

	function<void(int, int)> dfs = [&](int x, int fa) {
		euler[++euler[0]] = x;
		pos[x] = euler[0];
		for(auto y: e[x]) {
			if(y == fa) continue;

			dep[y] = dep[x] + 1;
			dfs(y, x);
			euler[++euler[0]] = x;
		}
	};
	
	dep[1] = 1;
	dfs(1, 0);
	assert(N == euler[0]);
	
	// st
	int lim = __lg(N);
	vector<vector<array<int, 2>>> st(lim + 1, vector<array<int, 2>>(N + 1));
	for(int i = 1; i <= N; i++) {
		st[0][i] = {dep[euler[i]], euler[i]};
	}

	for(int k = 1; k <= lim; k++) {
		int lim2 = N - (1 << k) + 1;
		for(int i = 1; i <= lim2; i++) {
			st[k][i] = min(st[k-1][i], st[k-1][i+(1<<k-1)]);
		}
	}

	auto query = [&](int L, int R) {
		int k = __lg(R - L + 1);
		return min(st[k][L], st[k][R-(1<<k)+1])[1];
	};

	// solve
	int ans = 0;
	for(int i = 1; i <= m; i++) {
		int u = rng61() % n + 1, v = rng61() % n + 1;
		u = pos[u], v = pos[v];
		if(u > v) swap(u, v);
		// u <= v
		int ansi = query(u, v);
		ans ^= ansi * i;
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
