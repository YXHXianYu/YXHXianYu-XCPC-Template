#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;


void work() {
	
	freopen("F2.in", "w", stdout);
	
	srand(time(0));
	
	int T = 1;
	int n = 200000;
	int k = 6;
	
	cout << T << endl;
	cout << n << " " << k << endl;
	
	for(int i = 1; i <= n; i++) {
		cout << (rand() % 9 + 1);
	}
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
