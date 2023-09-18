#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'


void work() {
	int n, m, d;
	cin >> n >> m >> d;

	vector<int> s(m + 5);
	for(int i = 1; i <= m; i++) cin >> s[i];

	int flag = true;
	s[0] = 1;
	s[m + 1] = n;
	for(int i = 1; i <= m; i++) {
		if((s[i] - s[i - 1]) % d != 0) {
			flag = false;
			break;
		}
	}

	if(flag) {
		int ans1 = (n - 1) / d + 1;
		cout << ans1 << " " << m << endl;
		return;
	}

	vector<int> ans(m + 5);

	int ans1 = 1;
	int lim = m + 1;
	for(int i = 1; i <= m; i++) {
		int del = s[i] - s[i - 1];
		if(del >= 1) {
			ans1 += (del - 1) / d + 1;
			ans[i] = (del - 1) / d + 1;
		} else {
			ans[i] = 0;
		}
		// cout << i << ": " << del << ", " << ans[i] << endl;
	}
	int del = s[m + 1] - s[m];
	ans1 += del / d;
	ans[m + 1] = del / d;
	// cout << m+1 << ": " << del << ", " << ans[m+1] << endl;

	// cout << "ans1 = " << ans1 << endl;
	
	const int INF = 1LL << 60;
	int ans2 = INF;
	int cnt = 0;
	for(int i = 1; i <= m; i++) {
		int del = s[i + 1] - s[i - 1];
		int v1;
		if(i != m) {
			v1 = (del >= 1 ? (del - 1) / d + 1 : 0);
		} else {
			v1 = del / d;
		}
		int v = ans1 - ans[i] - ans[i + 1] + v1;
		if(v < ans2) {
			ans2 = v;
			cnt = 1;
		} else if(v == ans2) {
			cnt++;
		}
		// cout << i << ": " << v << endl;
	}


	cout << ans2 << " " << cnt << endl;
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
