#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;

void work() {
	int n;
	cin >> n;

	vector<int> a(n + 1);
	for(int i = 1; i <= n; i++) cin >> a[i];

	const int MAXN = 2e5 + 10;
	bitset<MAXN> f;

	int ans = 0;
	int s = 0;
	f[1] = 1;
	for(int i = 1; i <= n; i++) {
		f |= f << a[i];
		s += a[i];
		if(f[i] == 1) {
			ans = max(ans, s - i + 1);
			f[i] = 0;
		}
		// for(int j = 1; j <= n; j++) cout << f[j]; cout << endl;
	}
	int n2 = n << 1;
	for(int i = n + 1; i <= n2; i++)
		if(f[i] == 1)
			ans = max(ans, s - i + 1);
	
	cout << ans << endl;
}

/*

*/

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
