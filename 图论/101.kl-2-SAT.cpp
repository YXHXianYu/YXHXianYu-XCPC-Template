#include<bits/stdc++.h>
using namespace std;
#define int long long


void work() {
	int n;
	cin >> n;

	vector<vector<int>> a(n + 1, vector<int>(n + 1));
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			cin >> a[i][j];
		}
	}

	// 带权并查集 (DSU)

	vector<int> f(n + 1);
	vector<int> g(n + 1); // g[i]: whether choose i
	for(int i = 1; i <= n; i++) f[i] = i, g[i] = 0;

	function<int(int)> find = [&](int x) {
		if(x == f[x]) return x;
		int rt = find(f[x]);
		g[x] ^= g[f[x]];
		return f[x] = rt;
	};

	auto merge = [&](int x, int y, int t) { // x => y
		int u = find(x), v = find(y);
		if(u == v) return;
		g[u] = t ^ g[x] ^ g[y];
		f[u] = v;
	};

	for(int i = 1; i <= n; i++) {
		for(int j = i + 1; j <= n; j++) {
			if(a[i][j] > a[j][i]) { // 换
				merge(i, j, 1);
			} else if(a[i][j] < a[j][i]) { // 不换
				merge(i, j, 0);
			}
		}
	}

	for(int i = 1; i <= n; i++) find(i);

	for(int i = 1; i <= n; i++)
		for(int j = i + 1; j <= n; j++)
			if(g[i] ^ g[j])
				swap(a[i][j], a[j][i]);

	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			cout << a[i][j] << " ";
		}
		cout << '\n';
	}
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int t = 1;
	cin >> t;
	while(t--) {
		work();
	}

	int lim = 2e5;
	for(int i = 1; i <= lim; i++) cout << endl;
	
	return 0;
}
