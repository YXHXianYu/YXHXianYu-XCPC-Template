#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'


void work() {
	int n, k;
	cin >> n >> k;

	string s;
	cin >> s;
	s = " " + s;

	if(k & 1) {
		vector<char> s1, s2;
		for(int i = 1; i <= n; i++) {
			if(i & 1) s1.push_back(s[i]);
			else s2.push_back(s[i]);
		}
		sort(s1.begin(), s1.end());
		sort(s2.begin(), s2.end());
		for(int i = 1, j = 0; i <= n; i++, j++) {
			if(i & 1) cout << s1[j / 2];
			else cout << s2[j / 2];
		}
		cout << endl;
	} else {
		sort(s.begin() + 1, s.end());
		for(int i = 1; i <= n; i++) cout << s[i]; cout << endl;
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
