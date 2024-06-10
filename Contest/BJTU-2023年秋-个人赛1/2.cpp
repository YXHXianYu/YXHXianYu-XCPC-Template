#include<bits/stdc++.h>
using namespace std;
#define int long long


void work() {
	int n;
	cin >> n;
	
	if((n >> 1) & 1) {
		cout << "NO" << endl;
	} else {
		cout << "YES" << endl;
		int N = n >> 1;
		int sum = 0;
		for(int i = 1; i <= N; i++) cout << (i << 1) << " ", sum += (i << 1);
		for(int i = 1; i < N; i++) cout << (i << 1) - 1 << " ", sum -= (i << 1) - 1;
		cout << sum << endl;
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