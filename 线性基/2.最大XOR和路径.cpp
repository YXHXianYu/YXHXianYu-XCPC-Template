#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;

const int B = 62;
struct LinearBasis {
	vector<int> a = vector<int>(B);
	bool insert(int x) {
		for(int i = B - 1; i >= 0; i--) {
			if(x & (1LL << i)) {
				if(a[i] == 0) { a[i] = x; return true; }
				x ^= a[i];
			}
		}
		return false;
	}
	int queryMax(int x) {
		for(int i = B - 1; i >= 0; i--) {
			x = max(x, x ^ a[i]);
		}
		return x;
	}
};


void work() {
	int n, m;
	cin >> n >> m;

	vector<vector<array<int, 3>>> e(n + 1, vector<array<int, 3>>());
	for(int i = 1; i <= m; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		e[u].push_back({v, w, i});
		e[v].push_back({u, w, i});
	}

	vector<bool> inPath(n + 1, 0);
	vector<int> f(n + 1, 0);
	vector<int> s(n + 1, 0);
	vector<int> dep(n + 1, 0);
	vector<int> vis(n + 1, 0);
	vector<int> te(m + 1, 0);
	
	function<void(int, int)> dfs1 = [&](int x, int fa) {
		vis[x] = 1;
		for(auto [y, w, id]: e[x]) {
			if(y == fa) continue;
			if(vis[y]) continue;
			te[id] = 1;
			s[y] = s[x] ^ w;
			f[y] = x;
			dep[y] = dep[x] + 1;
			dfs1(y, x);
		}
	};

	dep[1] = 1;
	dfs1(1, 0);

	int x = n;
	while(x) {
		inPath[x] = 1;
		x = f[x];
	}

	vector<int> rings;

	function<void(int)> dfs2 = [&](int x) {
		// cout << "(" << x << ", " << f[x] << ")" << endl;
		for(auto [y, w, id]: e[x]) {
			if(y == f[x]) continue;
			if(te[id]) {
				dfs2(y);
	 		} else {
				if(inPath[y] && dep[y] < dep[x]) {
					// cout << x << " -> " << y << endl;
					rings.push_back(s[x] ^ s[y] ^ w);
				}
			}
		}
	};

	dfs2(1);

	LinearBasis b;
	for(auto& x: rings) {
		b.insert(x);
	}

	int ans = s[n];
	ans = b.queryMax(ans);

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
