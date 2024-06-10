/**
 * Created by YXH_XianYu on 2023.8.31
 * Blog: https://yxhxianyu.fun
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'


void work() {
	string s;
	cin >> s;
	s = s;

	for(int i = 0; i <= 8; i++) {
		if(s[i] == '1') {
			cout << "13" << endl;
			return;
		} else if(s[i] == '3') {
			cout << "31" << endl;
			return;
		}
	}
	assert(false);
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