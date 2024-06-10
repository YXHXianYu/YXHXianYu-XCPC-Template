#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;

int n;
int a[maxn];

void work() {
	
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> a[i];
	
	int mx = 0, mn = 0;
	int tmpMx = 0; int tmpMn = 0;
	for(int i = 1; i <= n; i++) {
		tmpMx = max(0ll, tmpMx + a[i]);
		mx = max(mx, tmpMx);
		
		tmpMn = min(0ll, tmpMn + a[i]);
		mn = min(mn, tmpMn);
	}
	
	cout << max(mx, -mn) << endl;
	
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
