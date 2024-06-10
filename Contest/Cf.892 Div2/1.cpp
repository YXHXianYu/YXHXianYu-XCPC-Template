#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;


void work() {
	int n;
	cin >> n;

	vector<int> a(n + 1);
	for(int i = 1; i <= n; i++) cin >> a[i];
	
	int mn = a[1];
	for(int i = 2; i <= n; i++) {
		mn = min(mn, a[i]);
	}

	vector<int> b, c;
	for(int i = 1; i <= n; i++) {
		if(a[i] == mn) b.push_back(a[i]);
		else c.push_back(a[i]);
	}

	if(b.size() == 0 || c.size() == 0) {
		cout << -1 << endl;
		return;
	}

	cout << b.size() << " " << c.size() << endl;
	for(auto x: b) cout << x << " "; cout << endl;
	for(auto x: c) cout << x << " "; cout << endl;
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
