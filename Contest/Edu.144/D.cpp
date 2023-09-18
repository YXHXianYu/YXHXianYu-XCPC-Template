#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;
const int INF = (1LL << 60);

int n, k, x;
int a[maxn];

int f[21][maxn];

void work() {
	
	cin >> n >> k >> x;
	for(int i = 1; i <= n; i++) cin >> a[i];
	for(int i = 1; i <= n; i++) a[i] -= x;
	
	// k position += x
	
	int ans = 0;
	for(int i = 1; i <= n; i++) {
		f[0][i] = max(0ll, f[0][i - 1] + a[i]);
	}
	for(int j = 1; j <= k; j++) {
		f[j][0] = -INF;
		f[j][j] = max(0ll, f[j - 1][j - 1] + a[j] + x * 2);
		for(int i = j + 1; i <= n; i++) {
			f[j][i] = max(0ll, f[j][i - 1] + a[i]);
			f[j][i] = max(f[j][i], f[j - 1][i - 1] + a[i] + x * 2);
		}
	}
	
//	for(int j = 0; j <= k; j++) {
//		for(int i = 1; i <= n; i++) {
//			cout << f[j][i] << " ";
//		}
//		cout << endl;
//	}
	
	for(int i = 1, lim = n - k; i <= lim; i++) {
		ans = max(ans, f[0][i]);
	}
	
	for(int j = 1; j <= k; j++) {
		for(int i = j, lim = n - k + j; i <= lim; i++) {
			ans = max(ans, f[j][i]);
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
