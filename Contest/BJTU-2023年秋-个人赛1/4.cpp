#include<bits/stdc++.h>
using namespace std;
#define int long long


void work() {
	int n, k;
	cin >> n >> k;
	
	
	if((n & 1) ^ (k & 1)) {
		cout << "NO" << endl;
		return;
	}
	
	int sum = (1 + 2*k-1) * k / 2;
	
	if(n >= sum) {
		cout << "YES" << endl;
	} else {
		cout << "NO" << endl;
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