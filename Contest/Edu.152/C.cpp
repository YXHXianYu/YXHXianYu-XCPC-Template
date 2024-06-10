#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;


void work() {
	int n, m;
	cin >> n >> m;
	
	string s;
	cin >> s;
	s = " " + s;

	vector<int> a(n + 1);
	for(int i = 1; i <= n; i++) a[i] = s[i] - '0';
	vector<int> f(n + 1);
	for(int i = 1; i <= n; i++) f[i] = f[i - 1]+ a[i];

	vector<int> c1(n + 1);
	c1[n] = n;
	for(int i = n - 1; i >= 1; i--) {
		if(a[i] == 1 && a[i + 1] == 1) {
			c1[i] = c1[i + 1];
		} else {
			c1[i] = i;
		}
	}
	vector<int> c1i(n + 1);
	c1i[1] = 1;
	for(int i = 2; i <= n; i++) if(a[i] == 1 && a[i - 1] == 1) c1i[i] = c1i[i - 1]; else c1i[i] = i;

	vector<int> c0(n + 1);
	c0[n] = n;
	for(int i = n - 1; i >= 1; i--) if(a[i] == 0 && a[i + 1] == 0) c0[i] = c0[i + 1]; else c0[i] = i;

	vector<int> c0i(n + 1);
	c0i[1] = 1;
	for(int i = 2; i <= n; i++) {
		if(a[i] == 0 && a[i - 1] == 0) {
			c0i[i] = c0i[i - 1];
		} else {
			c0i[i] = i;
		}
	}

	// for(int i = 1; i <= n; i++) cout << c1[i] << " "; cout << endl;
	
	bool flag = false;
	vector<pair<int, int>> g;
	for(int i = 1; i <= m; i++) {
		int u, v;
		cin >> u >> v;
		
		if(u == v) {
			flag = true;
			continue;
		}
		int type = f[v] - f[u-1];
		// cout << " - " << c0[u] + 1 << ", " << c1i[v] << endl;
		if((a[u] == 0 && a[v] == 1 && c0[u] + 1 == c1i[v]) || type == v - u + 1 || type == 0) {
			flag = true;
			continue;
		}

		if(u > 1 && a[u - 1] == 0) u = c0i[u - 1];
		if(v < n && a[v + 1] == 1) v = c1[v + 1];

		// cout << i << ": " << u << ", " << v << endl;
		g.push_back({u, v});
	}
	// cout << g.size() << ", " << flag << endl;

	sort(g.begin(), g.end());
	g.erase(unique(g.begin(), g.end()), g.end());

	cout << g.size() + flag << endl;
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int t = 1;
	cin >> t;
	while(t--) {
		work();
	}
	
	return 0;
}
