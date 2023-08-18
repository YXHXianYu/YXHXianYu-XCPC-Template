#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;


void work() {
	string s;
	cin >> s;
	int n = s.size();
	s = " " + s;

	int m = (n << 1) + 1;
	string t(m + 1, ' ');
	for(int i = 1; i <= n; i++) {
		t[(i << 1) - 1] = '#';
		t[(i << 1)] = s[i];
	}
	t[m] = '#';

	vector<int> f(m + 1);
	int md = 0, r = 0, j, k;
	for(int i = 1; i <= m; i++) {
		if(i <= r) f[i] = min(r - i, f[(md << 1) - i]);
		while(i-f[i]-1 >= 1 && i+f[i]+1 <= m && t[i-f[i]-1] == t[i+f[i]+1]) f[i]++;
		if(i + f[i] - 1 > r) md = i, r = i + f[i] - 1;
	}

	int ans = 1;
	for(int i = 1; i <= m; i++) ans = max(ans, f[i]);
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
