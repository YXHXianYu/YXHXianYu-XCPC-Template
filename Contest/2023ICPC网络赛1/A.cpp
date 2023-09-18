#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'

void work() {
	int n, m;
	cin >> n >> m;
	
	vector<string> a(n + 1), b(m + 1);
	for(int i = 1; i <= n; i++) cin >> a[i];
	for(int i = 1; i <= m; i++) cin >> b[i];
	
	vector<string> c(1), d(1), e;
	map<string, int> f;
	
	for(int i = 1; i <= n; i++) {
		if(f.count(a[i]) == 0) {
			f[a[i]] = 1;
			c.push_back(a[i]);
		}
	}
	
	n = c.size() - 1;
	f.clear();
	
	for(int i = 1; i <= m; i++) {
		if(f.count(b[i]) == 0) {
			f[b[i]] = 1;
			d.push_back(b[i]);
		}
	}
	
	m = d.size() - 1;
	f.clear();
	
	int i, j;
	for(i = 1, j = 1; i <= n && j <= m; i++, j++) {
		if(f.count(c[i]) == 0) {
			f[c[i]] = 1;
			e.push_back(c[i]);
		}
		if(f.count(d[j]) == 0) {
			f[d[j]] = 1;
			e.push_back(d[j]);
		}
	}
	
	for(; i <= n; i++) {
		if(f.count(c[i]) == 0) {
			f[c[i]] = 1;
			e.push_back(c[i]);
		}
	}
	
	for(; j <= m; j++) {
		if(f.count(d[j]) == 0) {
			f[d[j]] = 1;
			e.push_back(d[j]);
		}
	}
	
//	cout << endl;
	for(auto s: e) cout << s << endl;
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
