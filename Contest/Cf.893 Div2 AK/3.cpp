#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'

void work() {
	int n;
	cin >> n;

	vector<int> ans;
	vector<int> vis(n + 1);
	if(n & 1) {
		ans.push_back(n);
		n--;
	}
	for(int i = n; i >= 2; i -= 2) {
		int j = i;
		while(vis[j] == 0) {
			vis[j] = 1;
			ans.push_back(j);
			if(j % 2 == 0) j /= 2;
			else break;
		}
	}
	for(int i = 1; i <= n; i++) if(!vis[i]) ans.push_back(i);
	
	for(auto x: ans) cout << x << " "; cout << endl;
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
