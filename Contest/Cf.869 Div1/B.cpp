#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e3 + 10;

int n, m;
vector<int> e[maxn];

int deg[maxn];

int vis[maxn];
int stk[maxn];
int flag = 0;

void dfs(int x, int st) {
//	cout << "(" << x << ")" << endl;
	for(auto y: e[x]) {
		if(vis[y] >= 2 || y == st) continue;
		
		stk[++stk[0]] = y;
		
		if(vis[y] == 1) {
			// found ans
			flag = 1;
			return;
		}
		
		vis[y] = 3;
		
		dfs(y, st);
		
		if(flag) return;
		
		stk[0]--;
	}
}



void work() {
	
	cin >> n >> m;
	
	for(int i = 1; i <= n; i++) e[i].clear(), deg[i] = 0;
	
	for(int i = 1; i <= m; i++) {
		int u, v;
		cin >> u >> v;
		e[u].push_back(v);
		e[v].push_back(u);
		deg[u]++;
		deg[v]++;
	}
	
	for(int i = 1; i <= n; i++) {
		if(deg[i] < 4) continue;
		// deg[i] >= 4;
		
		for(int j = 1; j <= n; j++) vis[j] = 0;
		stk[0] = 0;
		
		vector<int> t;
		for(auto y: e[i]) {
			t.push_back(y);
			vis[y] = 1;
		}
		vis[i] = 2;
		
//		cout << " - " << "i = " << i << endl;
		
		for(auto y: t) {
//			cout << " - " << "y = " << y << endl;
			
			stk[0] = 0;
			stk[++stk[0]] = y;
			flag = 0;
			dfs(y, y);
			if(flag == 1) {
				cout << "YES" << endl;
				
				vector<pair<int, int>> ans;
				
				int cnt = 0;
				for(auto y: t) {
					if(y != stk[1] && y != stk[stk[0]]) {
						ans.push_back({i, y});
						cnt++;
						if(cnt >= 2) break;
					}
				}
				ans.push_back({i, stk[1]});
				for(int i = 2; i <= stk[0]; i++) {
					ans.push_back({stk[i - 1], stk[i]});
				}
				ans.push_back({i, stk[stk[0]]});
				
				cout << ans.size() << endl;
				for(auto pr: ans) {
					int x = pr.first;
					int y = pr.second;
					cout << x << " " << y << endl;
				}
				
				return;
			}
		}
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
