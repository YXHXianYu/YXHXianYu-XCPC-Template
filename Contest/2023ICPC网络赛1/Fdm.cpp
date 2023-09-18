#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'

void work() {
	freopen("F.txt", "w", stdout);
	
	srand(time(0));
	
	auto randLL = [&]() -> int {
		return rand();
	};
	
	auto random = [&](int l, int r) {
		return (randLL() << 48 | randLL() << 32 | randLL() << 16 | randLL()) % (r - l + 1) + l;
	};
	
	int t = 1;
	cout << t << endl;
	
	for(int i = 1; i <= t; i++) {
		int n = 5e5;
		cout << n << endl;
		
		for(int i = 1; i <= n; i++) {
			cout << random(0, 1e18) << " ";
		}
		cout << endl;
	}
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
