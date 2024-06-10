/**
 * Created by YXH_XianYu on 2023.8.29
 * Blog: https://yxhxianyu.fun
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'


void work() {
	int n, a, q;
	cin >> n >> a >> q;

	string s;
	cin >> s;
	s = " " + s;

	int mx = a, mn = a, sum = a;
	for(int i = 1; i <= q; i++) {
		if(s[i] == '+') {
			a++;
			mx = max(mx, a);
			sum++;
		} else if(s[i] == '-') {
			a--;
			mn = min(mn, a);
		}
	}

	if(mx == n) {
		cout << "YES" << endl;
		return;
	}

	if(sum >= n) {
		cout << "MAYBE" << endl;
		return;
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