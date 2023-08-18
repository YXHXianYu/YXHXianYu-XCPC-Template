#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;


void work() {
	int n;
	cin >> n;

	__int128_t x = n;
	x = x * (n - 1) * (n - 2) * (n - 3) / 24;
	cout << ((int)(x)) << endl;
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
