#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;

int n, q;
int a[maxn];
int f[maxn];

void work() {
	
	cin >> n >> q;
	for(int i = 1; i <= n; i++) cin >> a[i];
	
	f[1] = 1;
	f[2] = 2;
	for(int i = 3; i <= n; i++) {
		if(a[i - 2] >= a[i - 1] && a[i - 1] >= a[i]) {
			f[i] = f[i - 1];
		} else {
			f[i] = f[i - 1] + 1;
		}
	}
	
//	for(int i = 1; i <= n; i++) cout << f[i] << " "; cout << endl;
	
	for(int i = 1; i <= q; i++) {
		int L, R;
		cin >> L >> R;
		
		int ans = f[R] - f[L - 1];
		
		if(L >= 2 && (R - L + 1) >= 2 && a[L - 1] >= a[L] && a[L] >= a[L + 1]) ans++;
		if(L >= 3 && a[L - 2] >= a[L - 1] && a[L - 1] >= a[L]) ans++;
		
		
		if(R - L + 1 == 1) ans = 1;
		else if(R - L + 1 == 2) ans = 2;
		else if(R - L + 1 >= 3) ans = max(ans, 2ll);
		
		cout << ans << endl;
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
