/**
 * Created by YXH_XianYu on 2023.8.23
 * Blog: https://yxhxianyu.fun
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'

int B = sqrt(2e5) / 3;
// int B = 1;
// O(q * (n / B + B))

void work() {
	int n, q;
	cin >> n >> q;

	vector<int> a(n + 1);
	vector<vector<int>> b(B + 1, vector<int>(B + 1));
	// B[i][j]: x = j (mod i)

	while(q--) {
		int opt;
		cin >> opt;
		if(opt == 1) {
			int x, y, d;
			cin >> x >> y >> d;

			if(x <= B) {
				b[x][y] += d;
			} else {
				for(int i = y; i <= n; i += x) a[i] += d;
			}

		} else if(opt == 2) {
			int x;
			cin >> x;

			int ans = a[x];
			for(int i = 1; i <= B; i++) {
				int j = x % i;
				ans += b[i][j];
			}
			cout << ans << endl;
		}
	}
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
