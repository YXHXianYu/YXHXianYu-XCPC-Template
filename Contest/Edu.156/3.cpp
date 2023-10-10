/**
 * Created by YXH_XianYu in 2023.10
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

	int pos;
	cin >> pos;
	int delN = 0;
	{
		int cnt = 0;
		for(int i = n; i >= 1; i--) {
			if(pos <= i) {
				delN = n - i;
				break;
			} else {
				pos -= i;
			}
		}
	}

	// cout << "delN = " << delN << endl;

	vector<char> t(n + 1);
	int top = 0;

	t[++top] = s[1];
	for(int i = 2; i <= n; i++) {
		while(top && t[top] > s[i]) {
			if(delN > 0) {
				delN -= 1;
				top -= 1;
			} else {
				break;
			}
		}
		t[++top] = s[i];
	}
	// cout << "(" << pos << ")";
	cout << t[pos];
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