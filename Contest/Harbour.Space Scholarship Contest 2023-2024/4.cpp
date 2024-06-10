#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'


void work() {
	int n;
	cin >> n;

	vector<vector<int>> a(n + 1, vector<int>(n + 1));
	for(int i = 1; i <= n; i++) {
		string s;
		cin >> s;
		for(int j = 1; j <= n; j++) {
			a[i][j] = s[j - 1] - '0';
		}
	}

	vector<vector<array<int, 3>>> f(n + 1,vector<array<int, 3>>(n + 1));
	int ans = 0;
	
	for(int j = 1; j <= n; j++) {
		if(a[1][j]) {
			ans++;
			f[1][j][0] ^= 1;
		}
	}

	for(int i = 2; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			int cnt = a[i][j];
			if(j >= 2 && f[i-1][j-1][2]) {
				cnt ^= 1;
				f[i][j][2] ^= 1;
			}
			if(j >= 2 && f[i-1][j-1][0]) {
				cnt ^= 1;
				f[i][j][2] ^= 1;
			}
			if(j < n && f[i-1][j+1][1]) {
				cnt ^= 1;
				f[i][j][1] ^= 1;
			}
			if(j < n && f[i-1][j+1][0]) {
				cnt ^= 1;
				f[i][j][1] ^= 1;
			}
			if(f[i-1][j][0]) {
				cnt ^= 1;
				f[i][j][0] ^= 1;
			}
			if(cnt) {
				ans++;
				f[i][j][0] ^= 1;
			}
		}
	}

	// for(int i = 1; i <= n; i++) {
	// 	for(int j = 1; j <= n; j++) cout << "(" << f[i][j][0] << "," << f[i][j][1] << "," << f[i][j][2] << ") ";
	// 	cout << endl;
	// }

	cout << ans << endl;
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
