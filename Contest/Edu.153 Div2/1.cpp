#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'


void work() {
	string s;
	cin >> s;
	int n = s.size();
	s = " " + s;

	if(n == 2 && s[1] == '(' && s[2] == ')') {
		cout << "NO" << endl;
		return;
	}

	string t(2 * n + 1, 0);

	for(int i = 1; i <= n; i++) t[i] = '(';
	for(int i = 1; i <= n; i++) t[n+i] = ')';

	int flag = 1;
	for(int i = 1; i <= n + 1; i++) {
		int flag2 = 1;
		for(int j = 0; j < n; j++) {
			if(t[i+j] != s[j+1]) {
				flag2 = 0;
				break;
			}
		}
		if(flag2) {
			flag = 0;
			break;
		}
	}

	if(flag) {
		cout << "YES" << endl;
		for(int i = 1; i <= 2 * n; i++) cout << t[i]; cout << endl;
		return;
	}

	cout << "YES" << endl;
	for(int i = 1; i <= n; i++) cout << "()"; cout << endl;
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
