#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'


void work() {
	int n;
	cin >> n;

	vector<int> a(n + 1);
	for(int i = 1; i <= n; i++)	cin >> a[i];

	sort(a.begin() + 1, a.end());

	if(a[1] != 0) {
		cout << -1 << endl;
		return;
	}
	for(int i = n; i >= 1; i--) cout << a[i];
	cout << endl;
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
