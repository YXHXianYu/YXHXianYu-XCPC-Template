#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;

int n, m;
int x[maxn];
int y[maxn];

void work() {
	
	cin >> n >> m;
	for(int i = 1; i <= n; i++) cin >> x[i];
	
	int cnt1 = 0;
	int cnt2 = 0;
	int cnt = 0;
	for(int i = 1; i <= n; i++) {
		if(x[i] == -1) cnt1++;
		else if(x[i] == -2) cnt2++;
		else y[++cnt] = x[i];
	}

	if(cnt == 0) {
		int ans = max(cnt1, cnt2);
		ans = min(ans, m);
		cout << ans << endl;
		return;
	}
	
	sort(y + 1, y + cnt + 1);
	cnt = unique(y + 1, y + cnt + 1) - y - 1;

	int ans = max(cnt1 + cnt, cnt2 + cnt);
	
	if(ans >= m) {
		cout << m << endl;
		return;
	}
	
	for(int i = 1; i <= cnt; i++) {
		int ans1 = min(cnt1 + i - 1, y[i] - 1);
		int ans2 = min(cnt2 + cnt - i, m - y[i]);
		ans = max(ans, ans1 + 1 + ans2);
//		cout << i << ": " << ans1 << ", " << ans2 << ", " << 1 << endl;
	}

	

	cout << min(ans, m) << endl;
	
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
