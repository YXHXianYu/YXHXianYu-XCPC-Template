#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;


void work() {
	int n = 300;
	vector<int> sg(n + 1);

	for(int i = 1; i <= n; i++) {
		set<int> s;
		for(int j = 1; j < i; j++) {
			s.insert(sg[j - 1] ^ sg[i - j - 1]);
		}
		while(s.count(sg[i])) sg[i]++;
		cout << sg[i] << " ";
//		if(i % 34 == 0) cout << endl;
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
