#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;

int n;
int a[maxn];
int b[maxn];

void work() {
	
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> a[i];
	
	sort(a + 1, a + n + 1);
	
	int ans = 1;
	int cnt = 0;
	int mx = -1;
	
	for(int i = 1; i <= n; i++) {
//		cout << " - " << a[i] << ", " << cnt << ", " << mx << endl;
		if(a[i] > cnt && cnt > mx) {
			ans += 1;
		}
		cnt += 1;
		mx = max(mx, a[i]);
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
