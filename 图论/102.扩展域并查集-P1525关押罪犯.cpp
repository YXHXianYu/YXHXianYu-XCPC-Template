#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;


void work() {
	int n, m;
	cin >> n >> m;

	vector<array<int, 3>> a(m + 1);
	for(int i = 1; i <= m; i++) cin >> a[i][1] >> a[i][2] >> a[i][0];
	sort(a.begin() + 1, a.begin() + m + 1);

	int N = (n << 1) + 1;
	vector<int> f(N + 1); // 2...n<<1|1
	for(int i = 2; i <= N; i++) f[i] = i;

	function<int(int)> find = [&](int x) {
		if(x == f[x]) return x;
		else return f[x] = find(f[x]);
	};

	auto merge = [&](int u, int v) {
		u = find(u); v = find(v);
		if(u == v) return;
		f[v] = u;
	};

	for(int i = m; i >= 1; i--) {
		int u = a[i][1], v = a[i][2];
		// cout << i << ", " << u << ", " << v << ": " << (find(u << 1) == find(v << 1)) << endl;
		if(find(u << 1) == find(v << 1)) {
			cout << a[i][0] << endl;
			return;
		} else {
			merge(u << 1, v << 1 | 1);
			merge(v << 1, u << 1 | 1);
		}
	}

	cout << 0 << endl;
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
