#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'


void work() {
	int n;
	cin >> n;

	vector<int> a(n + 1);
	for(int i = 1; i <= n; i++) cin >> a[i];

	int mn = n + 1;
	int mn2 = n + 1;
	int ans = 0;
	for(int i = 1; i <= n; i++) {
		if(a[i] < mn) {
			mn = a[i];
		} else if(a[i] < mn2) {
			mn2 = a[i];
			ans++;
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
