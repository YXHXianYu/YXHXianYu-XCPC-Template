#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;

int n;
int a[maxn];

void work() {
	
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> a[i];
	
	if(n & 1) {
		int ans = 0;
		for(int i = 1; i <= n; i++) ans ^= a[i];
		cout << ans << endl;
	} else {
		int ans = 0;
		for(int i = 1; i <= n; i++) ans ^= a[i];
		if(ans == 0) {
			cout << 0 << endl;
		} else {
			cout << -1 << endl;
		}
	}
	
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
