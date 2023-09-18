/**
 * Created by YXH_XianYu on 2023.8.29
 * Blog: https://yxhxianyu.fun
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'


void work() {
	int n, m;
	cin >> n >> m;

	vector<vector<int>> a(n + 1, vector<int>(m + 1));
	vector<int> row(n + 1);
	vector<int> col(m + 1);
	for(int i = 1; i <= n; i++) {
		string s;
		cin >> s;
		s = " " + s;
		for(int j = 1; j <= m; j++) {
			if(s[j] == '.') {
				a[i][j] = 0;
			} else if(s[j] == 'L') {
				a[i][j] = 1;
			} else if(s[j] == 'R') {
				a[i][j] = 2;
			} else if(s[j] == 'U') {
				a[i][j] = 3;
			} else if(s[j] == 'D') {
				a[i][j] = 4;
			} else assert(false);
		}
	}

	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			if(a[i][j]) {
				row[i]++;
				col[j]--;
			}
		}
	}

	for(int i = 1; i <= n; i++) {
		if(row[i] & 1) {
			cout << -1 << endl;
			return;
		}
	}
	for(int i = 1; i <= m; i++) {
		if(col[i] & 1) {
			cout << -1 << endl;
			return;
		}
	}

	vector<vector<int>> ans(n + 1, vector<int>(m + 1));
	vector<int> row1(n + 1);
	vector<int> col1(m + 1);
	

	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			if(a[i][j] == 3) {
				if(row1[i] > 0) {
					row1[i]--;
					row1[i+1]++;
					ans[i][j] = 2;
					ans[i+1][j] = 1;
				} else if(row1[i] < 0) {
					row1[i]++;
					row1[i+1]--;
					ans[i][j] = 1;
					ans[i+1][j] = 2;
				} else if(row1[i+1] > 0) {
					row1[i]++;
					row1[i+1]--;
					ans[i][j] = 1;
					ans[i+1][j] = 2;
				} else {
					row1[i]--;
					row1[i+1]++;
					ans[i][j] = 2;
					ans[i+1][j] = 1;
				}
			}
		}
	}

	for(int j = 1; j <= m; j++) {
		for(int i = 1; i <= n; i++) {
			if(a[i][j] == 1) {
				if(col1[j] > 0) {
					col1[j]--;
					col1[j+1]++;
					ans[i][j] = 2;
					ans[i][j+1] = 1;
				} else if(col1[j] < 0) {
					col1[j]++;
					col1[j+1]--;
					ans[i][j] = 1;
					ans[i][j+1] = 2;
				} else if(col1[j+1] > 0) {
					col1[j]++;
					col1[j+1]--;
					ans[i][j] = 1;
					ans[i][j+1] = 2;
				} else {
					col1[j]--;
					col1[j+1]++;
					ans[i][j] = 2;
					ans[i][j+1] = 1;
				}
			}
		}
	}

	for(int i = 1; i <= n; i++) if(row1[i] != 0) {
		cout << -1 << endl;
		return;
	}
	for(int i = 1; i <= m; i++) if(col1[i] != 0) {
		cout << -1 << endl;
		return;
	}
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			if(ans[i][j] == 0) cout << ".";
			else if(ans[i][j] == 1) cout << "W";
			else cout << "B";
		}
		cout << endl;
	}
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