#include<bits/stdc++.h>
using namespace std;
// #define int long long
#define endl '\n'


void work() {
	int n, k;
	cin >> n >> k;

	string s;
	cin >> s;
	s = " " + s;
	
	vector<int> a(n + 1);
	for(int i = 1; i <= n; i++) {
		a[i] = s[i] - '0';
	}

	vector<vector<vector<int>>> f1(2, vector<vector<int>>(n + 3, vector<int>(k + 3)));
	vector<vector<vector<int>>> f2(2, vector<vector<int>>(n + 3, vector<int>(k + 3)));
	
	vector<vector<vector<int>>> g2(2, vector<vector<int>>(n + 3, vector<int>(k + 3)));

	for(int T = 0; T <= 1; T++) {
		for(int i = 1; i <= n; i++) {
			for(int j = 0; j <= k; j++) {
				if(a[i] == T) {
					f1[T][i][j] = f1[T][i - 1][j] + 1;
				} else if(j >= 1) {
					f1[T][i][j] = f1[T][i - 1][j - 1] + 1;
				}
				f2[T][i][j] = max(f1[T][i][j], max(f2[T][i-1][j], (j >= 1 ? f2[T][i][j-1] : 0)));
			}
		}
	}
	for(int T = 0; T <= 1; T++) {
		for(int i = 1; i <= n; i++) {
			for(int j = 0; j <= k; j++) {
				f1[T][i][j] = 0;
			}
		}
	}
	for(int T = 0; T <= 1; T++) {
		for(int i = n; i >= 1; i--) {
			for(int j = 0; j <= k; j++) {
				if(a[i] == T) {
					f1[T][i][j] = f1[T][i + 1][j] + 1;
				} else if(j >= 1) {
					f1[T][i][j] = f1[T][i + 1][j - 1] + 1;
				}
				g2[T][i][j] = max(f1[T][i][j], max(g2[T][i+1][j], (j >= 1 ? g2[T][i][j-1] : 0)));
			}
		}
	}

	// for(int i = 1; i <= n; i++, cout << endl) for(int j = 0; j <= k; j++) cout << f2[0][i][j] << " ";
	// cout << "===" << endl;
	// for(int i = 1; i <= n; i++, cout << endl) for(int j = 0; j <= k; j++) cout << g2[1][i][j] << " ";

	vector<int> ans0(n + 1, -1);
	vector<int> ans1(n + 1, -1);
	for(int i = 1; i < n; i++) {
		// i ~ i+1
		for(int j = 0; j <= k; j++) {
			// [1, i] use k
			int l0, l1;

			// [1, i] is 0
			l0 = f2[0][i][j];
			l1 = g2[1][i+1][k-j];

			// cout << i << ", " << j << ": " << l0 << ", " << l1 << endl;

			ans0[l0] = max(ans0[l0], l1);
			ans1[l1] = max(ans1[l1], l0);

			// [1, i] is 1
			l1 = f2[1][i][j];
			l0 = g2[0][i+1][k-j];

			ans0[l0] = max(ans0[l0], l1);
			ans1[l1] = max(ans1[l1], l0);

			// cout << i << ", " << j << ": " << l0 << ", " << l1 << endl;
		}
	}

	int l0, l1;

	l0 = g2[0][1][k];
	ans0[l0] = max(ans0[l0], 0);
	l1 = g2[1][1][k];
	ans1[l1] = max(ans1[l1], 0);

	l0 = f2[0][n][k];
	ans0[l0] = max(ans0[l0], 0);
	l1 = g2[1][n][k];
	ans1[l1] = max(ans1[l1], 0);

	// for(int i = 0; i <= n; i++) cout << "(" << i << ", " << ans0[i] << ") "; cout << endl;
	// for(int i = 0; i <= n; i++) cout << "(" << ans1[i] << ", " << i << ") "; cout << endl;

	for(int i = 1; i <= n; i++) {
		int v = 0;
		for(int j = 0; j <= n; j++) {
			if(ans0[j] != -1) {
				v = max(v, i * j + ans0[j]);
			}
			if(ans1[j] != -1) {
				v = max(v, j + i * ans1[j]);
			}
		}
		cout << v << " ";
	}
	cout << endl;


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
