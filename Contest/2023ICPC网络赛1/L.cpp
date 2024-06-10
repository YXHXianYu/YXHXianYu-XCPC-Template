#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'

void work() {
	int n, t;
	cin >> n >> t;
	int mx = 0;
	for(int i = 0; i < n; i++) {
		int a;
		cin >> a;
		mx = max(mx, a);
	}
	int k = (mx % t == 0 ? mx / t : (mx / t + 1));
	k = max(k, 2ll);
	cout << k;
	
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
