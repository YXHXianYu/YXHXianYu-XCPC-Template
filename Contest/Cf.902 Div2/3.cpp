/**
 * Created by YXH_XianYu in 2023.10
 * Blog: https://yxhxianyu.fun
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'


void work() {
	int n, m, k;
	cin >> n >> m >> k;

	// 0 0 2 2 2
	// 0 0 0 3 3
	// 0 0 0 0 4
	// 0 1 1 1 5
	// 0 0 2 2 6
	// 0 0 0 3 7
	// 0 0 0 0 8

	// a[n+1] <= n ===> 2 distinct

	if(k > 3) {
		cout << 0 << endl;
	} else if(k == 3) {
		if(m > n) {
			int v = m - n;
			v = (v - v / n);
			cout << v << endl;
		} else {
			cout << 0 << endl;
		}
	} else if(k == 2) {
		if(m > n) {
			cout << n + (m - n) / n << endl;
		} else {
			cout << m << endl;
		}
	} else if(k == 1) {
		cout << 1 << endl;
	} else assert(false);
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