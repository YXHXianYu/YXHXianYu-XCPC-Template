#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;


void work() {
	string s;
	cin >> s;
	int n = s.size();
	s = " " + s;

	vector<int> z(n + 1);
	int l = 0, r = 0;
	for(int i = 2; i <= n; i++) {
		z[i] = ((i <= r) ? (min(z[i - l + 1], r - i + 1)) : 0);
		while(i + z[i] <= n && s[i + z[i]] == s[z[i] + 1]) z[i]++;
		if(i + z[i] - 1 >= r) l = i, r = i + z[i] - 1;
	}

	// for(int i = 1; i <= n; i++) cout << z[i] << " "; cout << endl;

	int ans = 0;
	int mx = 0;
	for(int i = 2; i <= n; i++) {
		if(i + z[i] - 1 >= n && mx >= z[i]) {
			ans = z[i];
			break;
		}
		mx = max(mx, z[i]);
	}
	if(ans == 0) cout << "Just a legend" << endl;
	else cout << s.substr(1, ans) << endl;
	
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
