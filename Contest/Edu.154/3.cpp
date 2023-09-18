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
	int n = s.size();
	s = " " + s;

	int top = 0;
	int cnt = 0; // ordered
	int norcnt = 0;
	vector<int> isNOrdered(n + 1);
	for(int i = 1; i <= n; i++) {
		if(s[i] == '+') {
			top += 1;
		} else if(s[i] == '-') {
			if(isNOrdered[top]) {
				isNOrdered[top] = 0;
				norcnt -= 1;
			}
			top -= 1;
			cnt = min(cnt, top);
		} else if(s[i] == '1') {
			if(top >= 2 && norcnt != 0) {
				cout << "NO" << endl;
				return;
			}
			cnt = top;
		} else if(s[i] == '0') {
			if(top <= 1 || top <= cnt) {
				cout << "NO" << endl;
				return;
			}
			// top > cnt
			if(isNOrdered[top] == 0) {
				isNOrdered[top] = 1;
				norcnt += 1;
			}
		} else assert(false);
	}

	cout << "YES" << endl;
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