#include<bits/stdc++.h>
using namespace std;
#define int long long


void work() {
	int n;
	cin >> n;
	
	vector<int> a(n + 1);
	for(int i = 1; i <= n; i++) cin >> a[i];
	
	const int INF = 1LL << 60;
	
	int lst = 1;
	int ans = 0;
	for(int i = 2; i <= n; i++) {
		if(a[i - 1] * a[i] < 0) {
			int mx = -INF;
			for(int j = lst; j < i; j++) {
				mx = max(mx, a[j]);
			}
			ans += mx;
			lst = i;
		}
	}
	
	int mx = -INF;
	for(int j = lst; j <= n; j++) {
		mx = max(mx, a[j]);
	}
	ans += mx;
	
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