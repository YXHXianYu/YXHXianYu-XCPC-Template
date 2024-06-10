#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'


void work() {
	int x, y, n;
	cin >> x >> y >> n;

	vector<int> a(n + 1);
	a[n] = y;
	int cnt = 1;
	for(int i = n - 1; i >= 1; i--) {
		a[i] = a[i + 1] - cnt;
		cnt++;
	}
	if(a[1] < x) {
		cout << -1 << endl;
	} else {
		a[1] = x;
		for(int i = 1; i <= n; i++) cout << a[i] << " "; cout << endl;
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
