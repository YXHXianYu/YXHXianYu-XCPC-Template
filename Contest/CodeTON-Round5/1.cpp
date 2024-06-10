#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;


void work() {
	int n, m;
	cin >> n >> m;

	vector<int> a(n + 1);
	for(int i = 1; i <= n; i++) cin >> a[i];

	vector<int> b(m + 1);
	for(int i = 1; i <= m; i++) cin >> b[i];

	int sa = 0;
	int sb = 0;
	for(int i = 1; i <= n; i++) sa += a[i];
	for(int i = 1; i <= m; i++) sb += b[i];

	if(sa == sb) {
		cout << "Draw" << endl;
	} else if(sa > sb) {
		cout << "Tsondu" << endl;
	} else {
		cout << "Tenzing" << endl;
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
