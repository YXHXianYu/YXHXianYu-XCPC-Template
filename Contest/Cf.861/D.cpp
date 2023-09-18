#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;

int n, k;
int a[maxn];

map<int, int> f;

void work() {
	
	cin >> n >> k;
	for(int i = 1; i <= n; i++) cin >> a[i];
	
	if(k == 1) {
		cout << 0 << endl;
		return;
	}
	
	if(n == k) {
		int ans = 0;
		int mid = n / 2 + 1;
		for(int i = mid - 1, j = mid + 1; i >= 1; i--, j++) {
			if(a[i] != a[j])
				ans++;
		}
		cout << ans << endl;
		return;
	}
	
	int ans = 0;
	
	f.clear();
	int cnt = 0;
	for(int i = 1; i <= n; i += 2) {
		if(i >= k + 2) {
			f[a[i - k - 1]] -= 1;
		}
		
		if(
		
		
	}
	
	
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
