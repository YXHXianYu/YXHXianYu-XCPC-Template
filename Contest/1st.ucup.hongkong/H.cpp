#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;


void work() {
	int l, r, b, k;
	cin >> l >> r >> b >> k;
	
	if(l < b) l = b;
	// l >= b
	int d = ceil(1.0 * l / b);
	b *= d;
	
	int ans = k * b;
	
	cout << ans << endl;
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
