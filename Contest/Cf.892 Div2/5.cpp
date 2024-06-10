#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;


void work() {
	int n, k;
	cin >> n >> k;

	vector<int> a(n + 1);
	for(int i = 1; i <= n; i++) cin >> a[i];

	vector<int> b(n + 1);
	for(int i = 1; i <= n; i++) cin >> b[i];

	for(int i = 1; i <= n; i++) if(a[i] > b[i]) swap(a[i], b[i]);

	vector<vector<int>> va(n + 1, vector<int>(n + 1));
	for(int i = 1; i <= n; i++) {
		for(int p = i; p >= 1; p--) {
			int j = i - p + 1;
			va[i][j] = abs(a[i]-b[j]) + abs(a[j]-b[i]);
		}
	}

	/*
	bl < br => (br-ar) + (bl-al)
	br < bl => ditto
	ar < br => (br+ar) - (bl+al)
	al < bl => (bl+al) - (br+ar)

	al < bl


	f[i][j] = max(f[i-1][j], f[i-k][j-k] + va[i][k]);
	*/

	vector<vector<int>> f(n + 1, vector<int>(k + 1));
	for(int d = 0; d < n; d++) {
		int i = d + 1;
		int j = i - d;
		f[i][j] = max(f[i - 1][j], va[i][i]);

		int mx1 = f[i-1][j-1] + (b[i] - a[i]);
		int mx2 = f[i-1][j-1] - (b[i] + a[i]);
		int mx3 = f[i-1][j-1] + (b[i] + a[i]);

		for(i = d + 2, j = i - d; i <= n && j <= k; i++, j = i - d) {
			mx1 = max(mx1, f[i-1][j-1] + (b[i] - a[i]));
			mx2 = max(mx2, f[i-1][j-1] - (b[i] + a[i]));
			mx3 = max(mx3, f[i-1][j-1] + (b[i] + a[i]));
			f[i][j] = max(max(f[i - 1][j], mx3 - (b[i] + a[i])), max(mx1 + (b[i] - a[i]), mx2 + (b[i] + a[i])));
		}
	}

	// for(int i = 1; i <= n; i++, cout << endl) for(int j = 1; j <= k; j++) cout << f[i][j] << " ";

	cout << f[n][k] << endl;
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
