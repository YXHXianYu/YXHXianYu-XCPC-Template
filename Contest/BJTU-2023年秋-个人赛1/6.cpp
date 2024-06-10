#include<bits/stdc++.h>
using namespace std;
#define int long long


void work() {
	int n, m, k;
	cin >> n >> m >> k;
	
	vector<array<int, 2>> a(k + 1), b(k + 1);
	for(int i = 1; i <= k; i++) cin >> a[i][0] >> a[i][1];
	for(int i = 1; i <= k; i++) cin >> b[i][0] >> b[i][1];
	for(int i = 1; i <= k; i++) a[i][0] = b[i][0] - a[i][0];
	for(int i = 1; i <= k; i++) a[i][1] = b[i][1] - a[i][1];
	
//	for(int i = 1; i <= k; i++) cout << a[i][0] << " " << a[i][1] << endl;
	
	vector<char> ans;
	for(int i = 1; i < n; i++) ans.push_back('U');
	for(int i = 1; i < m; i++) ans.push_back('L');
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j < m; j++) {
			ans.push_back((i & 1 ? 'R' : 'L'));
		}
		if(i < n) ans.push_back('D');
	}
	
	cout << ans.size() << endl;
	for(auto ch: ans) cout << ch;
	cout << endl;
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