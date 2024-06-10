#include<bits/stdc++.h>
using namespace std;
#define int long long


void work() {
	int n;
	cin >> n;
	
	
	int cnt = 0;
	for(int i = 1, j = 1; i <= n; i++, j <<= 1) {
		cnt |= j;
		if(i >= 2 && n % cnt == 0) {
			cout << n / cnt << endl;
			return;
		}
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