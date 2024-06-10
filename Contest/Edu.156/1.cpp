/**
 * Created by YXH_XianYu in 2023.10
 * Blog: https://yxhxianyu.fun
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'


void work() {
	int n;
	cin >> n;

	if(n <= 6) {
		cout << "NO" << endl;
		return;
	}

	if(n % 3 != 0) {
		cout << "YES" << endl;
		cout << 1 << " " << 2 << " " << n - 3 << endl;
		return;
	}
	
	// n % 3 == 0
	if(n - 5 >= 5) {
		cout << "YES" << endl;
		cout << 1 << " " << 4 << " " << n - 5 << endl;
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