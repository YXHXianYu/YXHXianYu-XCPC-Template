#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'


void work() {
	int n, m;
	cin >> n >> m;

	vector<int> a(n + 1);
	for(int i = 1; i <= n; i++) cin >> a[i];

	vector<int> f(m + 1);
	int cnt = 1;
	if(a[1] <= m) f[a[1]] = cnt;
	for(int i = 2; i <= n; i++) {
		if(a[i - 1] + 1 == a[i]) {
			cnt++;
		} else {
			cnt = 1;
		}
		if(a[i] <= m) f[a[i]] = max(f[a[i]], cnt);
	}

	// for(int i = 1; i <= m; i++) cout << f[i] << " "; cout << endl;

	vector<array<int, 2>> stk(m + 1);
	int top = 0;
	for(int i = m; i >= 1; i--) {
		while(top >= 2 && i >= stk[top-1][0]-stk[top-1][1] && stk[top][0]-stk[top][1] >= i-f[i]) {
			top--;
		}
		if(i < stk[top][0]-stk[top][1]) {
			cout << "-1" << endl;
			return;
		}
		stk[++top] = {i, f[i]};
		if(stk[top][0] - stk[top][1] <= 0) {
			cout << top << endl;
			return;
		}
	}
	cout << -1 << endl;
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
