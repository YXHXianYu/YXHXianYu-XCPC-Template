#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;


void work() {
	int n, m;
	cin >> n >> m;

	int N = 3 * n;
	vector<int> f(N + 1);
	for(int i = 1; i <= N; i++) f[i] = i;

	function<int(int)> find = [&](int x) {
		if(x == f[x]) return x;
		else return f[x] = find(f[x]);
	};

	auto merge = [&](int x, int y) {
		x = find(x);
		y = find(y);
		if(x == y) return ;
		f[y] = x;
	};

	int ans = 0;
	for(int i = 1; i <= m; i++) {
		int opt, x, y;
		cin >> opt >> x >> y;

		if(x > n || y > n) { ans++; continue; }

		if(opt == 1) {
			if(find(x) == find(y + n) || find(x + n) == find(y)) {
				ans++;
				continue;
			}
			merge(x, y);
			merge(x + n, y + n);
			merge(x + n + n, y + n + n);
		} else {
			if(x == y) { ans++; continue; }
			if(find(x) == find(y) || find(y) == find(x + n)) {
				ans++;
				continue;
			}
			merge(x, y + n);
			merge(x + n, y + n + n);
			merge(x + n + n, y);
		}
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
