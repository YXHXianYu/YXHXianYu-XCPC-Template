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
	for(int i = 1; i <= n; i++) b[i] = a[i] - (n - i + 1);

	int lim = __lg(n);
	vector<vector<int>> st(lim + 1, vector<int>(n + 1));
	for(int i = 1; i <= n; i++) st[0][i] = b[i];
	for(int k = 1; k <= lim; k++) {
		int lim2 = n - (1 << k) + 1;
		for(int i = 1; i <= lim2; i++) {
			st[k][i] = max(st[k-1][i], st[k-1][i+(1<<k-1)]);
		}
	}

	auto query = [&](int L, int R) {
		int k = __lg(R - L + 1);
		return max(st[k][L], st[k][R-(1<<k)+1]);
	};

	vector<int> s(n + 1);
	for(int i = 1; i <= n; i++) s[i] = s[i - 1] + b[i];

	int ans = 0;
	for(int i = 1; i <= n; i++) ans = max(ans, a[i]);

	for(int L = 1; L <= n; L++) {
		for(int R = L; R < n; R++) {
			int sum = s[R] - s[L - 1]  + k;
			int len = R - L + 1;
			int t = (sum >= 0 ? sum / len : (sum + 1) / len - 1);
			if(t < query(L, R)) continue;
			// if(L == 1 && R == 4) cout << t << ", " << query(L, R) << endl;
			int v = t + (n - L + 1);
			v = min(v, a[R+1] + len);
			ans = max(ans, v);
			// cout << L << ", " << R << ": " << v << ", " << t << endl;
		}
	}

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
