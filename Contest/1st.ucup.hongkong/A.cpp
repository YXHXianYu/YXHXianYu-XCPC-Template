#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;

int n;

int p[maxn];
vector<int> e[maxn];

int dfs(int x) {
	if(e[x].size() == 0) return 1;
	if(e[x].size() == 1) return dfs(e[x][0]);
	
	int mx = 0;
	int mx2 = 0;
	for(auto y: e[x]) {
		int cur = dfs(y) + 1;
		if(cur > mx) {
			mx2 = mx;
			mx = cur;
		} else if(cur > mx2) {
			mx2 = cur;
		}
	}
	
//	cout << x << ": " << mx << ", " << mx2 << endl;
	
	return max(mx - 1, mx2);
}

void work() {
	
	cin >> n;
	for(int i = 1; i <= n; i++) e[i].clear();
	
	for(int i = 1; i <= n; i++) {
		cin >> p[i];
		if(i > 1) {
			e[p[i]].push_back(i);
		}
	}
	
	cout << dfs(1) << endl;
	
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
