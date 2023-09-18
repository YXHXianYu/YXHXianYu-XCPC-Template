#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'


void work() {
	int n;
	cin >> n;

	vector<int> a(n + 1);
	for(int i = 1; i <= n; i++) cin >> a[i];

	vector<int> cnt(n + 1);
	for(int i = 1; i <= n; i++) cnt[a[i]]++;

	for(int i = 1; i <= min(15ll, n); i++) cout << cnt[i] << " "; cout << endl;

	vector<int> f(n + 1);
	int lim = n - 4;
	for(int i = 1; i <= lim; i++) {
		int mn = cnt[i];
		for(int j = 1; j <= 4; j++) {
			mn = min(mn, cnt[i + j]);
		}
		for(int j = 0; j <= 4; j++) {
			cnt[i + j] -= mn;
		}
		if(i + 5 <= n) f[i + 5] += mn;
	}

	for(int i = n; i >= 1; i--) {
		int mn = f[i];
		for(int j = i; j <= n && mn; j++) {
			mn = min(mn, cnt[j]);
			cnt[j] -= mn;
		}
	}

	for(int i = 1; i <= n; i++) if(cnt[i] != 0) {
		cout << "NO" << endl;
		return;
	}
	cout << "YES" << endl;
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
