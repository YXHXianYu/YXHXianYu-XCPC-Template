#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;

int l, r;

int getV(int x) {
	int mx = 0;
	int mn = 9;
	while(x) {
		mx = max(mx, x % 10);
		mn = min(mn, x % 10);
		x /= 10;
	}
	return mx - mn;
}

void work() {
	
	cin >> l >> r;
	
	int ans = l;
	int ansv = -1;
	for(int i = l, j = 1; i <= r && j <= 100; i++, j++) {
		int va = getV(i);
		if(va > ansv) {
			ans = i;
			ansv = va;
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
