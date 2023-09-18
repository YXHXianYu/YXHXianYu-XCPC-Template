/**
 * Created by YXH_XianYu on 2023.8.31
 * Blog: https://yxhxianyu.fun
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'


void work() {
	string a;
	cin >> a;
	string b;
	cin >> b;
	int n = a.size();
	a = " " + a;
	b = " " + b;

	for(int i = 1; i < n; i++) {
		if(a[i] == '0' && b[i] == '0' && a[i+1] == '1' && b[i+1] == '1') {
			cout << "YES" << endl;
			return;
		}
	}
	cout << "NO" << endl;
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