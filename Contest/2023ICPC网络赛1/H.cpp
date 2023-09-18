#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'

void work() {
	int n;
	cin >> n;
	
	string s;
	cin >> s;
	s = " " + s;
	
	deque<int> dq;
	for(int i = 1; i <= n; i++) {
		if('a' <= s[i] && s[i] <= 'z') {
			dq.push_front(s[i]);
		} else {
			dq.push_back(s[i]);
		}
	}
	
	int L, R = 0;
	
	vector<int> T(n + 1);
	T[0] = 0;
	T[1] = 1;
	for(int i = 2; i <= n; i++) {
		int x = T[i - 1];
		if(
	}
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
