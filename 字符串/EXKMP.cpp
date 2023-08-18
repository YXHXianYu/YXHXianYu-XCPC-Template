#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;


void work() {
	string a;
	cin >> a;
	int n = a.size();
	a = " " + a;

	string b;
	cin >> b;
	int m = b.size();
	b = " " + b;

	vector<int> z(m + 1);
	int l = 0, r = 0;
	for(int i = 2; i <= m; i++) {
		z[i] = i <= r ? min(z[i - l + 1], r - i + 1) : 0;
		while(i + z[i] <= m && b[z[i] + 1] == b[i + z[i]]) z[i]++;
		if(i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
	}

	vector<int> p(n + 1);
	l = 0, r = 0;
	for(int i = 1; i <= n; i++) {
		p[i] = i <= r ? min(z[i - l + 1], r - i + 1) : 0;
		while(i + p[i] <= n && b[p[i] + 1] == a[i + p[i]]) p[i]++;
		if(i + p[i] - 1 > r) l = i, r = i + p[i] - 1;
	}

	int ans1 = m + 1;
	for(int i = 2; i <= m; i++) ans1 ^= i * (z[i] + 1);

	int ans2 = 0;
	for(int i = 1; i <= n; i++) ans2 ^= i * (p[i] + 1);

	cout << ans1 << endl;
	cout << ans2 << endl;
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
