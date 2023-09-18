/**
 * Created by YXH_XianYu on 2023.8.31
 * Blog: https://yxhxianyu.fun
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'

/*
1 1 2 5 2  2 4 
*/

void work() {
	int n;
	cin >> n;

	if(n <= 2) { cout << 0 << endl; return; }
	int ans = 0;
	int sum2 = 1;
	int sum5 = 0;
	int cnt2 = 1;
	int cnt5 = 0;
	for(int i = 3; i <= n; i++) {
		int x = 4 * i - 2;
		while(x % 5 == 0) {
			x /= 5;
			cnt5 += 1;
		}
		while(~x & 1) {
			x >>= 1;
			cnt2 += 1;
		}
		x = i + 1;
		while(x % 5 == 0) {
			x /= 5;
			cnt5 -= 1;
		}
		while(~x & 1) {
			x >>= 1;
			cnt2 -= 1;
		}
		sum2 += cnt2;
		sum5 += cnt5;
	}
	cout << min(sum2, sum5) << endl;
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