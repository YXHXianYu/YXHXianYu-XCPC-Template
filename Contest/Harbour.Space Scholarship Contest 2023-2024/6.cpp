/**
 * Created by YXH_XianYu on 2023.8.27
 * Blog: https://yxhxianyu.fun
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'


void work() {
	int n, Q;
	cin >> n >> Q;

	vector<int> a(n + 1);
	vector<vector<int>> pos(n + 1, vector<int>());
	for(int i = 1; i <= n; i++) {
		cin >> a[i];
		pos[a[i]].push_back(i);
	}

	for(int i = 1; i <= n; i++) {
		if(pos[i].size() == 0) continue;
		cout << i << ": "; for(auto j: pos[i]) cout << j << " "; cout << endl;
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