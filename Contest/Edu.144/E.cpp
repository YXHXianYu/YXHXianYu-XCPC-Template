#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;

int n;

vector<int> e[maxn];
vector<int> g;

int isLink = 0;
int leaf = 0;
void dfs0(int x, int fa) {
	if(e[x].size() >= 3) {
		isLink = 0;
	}
	
	if(leaf == 0 && e[x].size() == 1) {
		leaf = x;
	}
	
	for(auto y: e[x]) {
		if(y == fa) continue;
		dfs0(y, x);
	}
}

int dfs(int x, int f, int fa) {
	
	if(fa == -1) {
		if(e[x].size() == 1) {
			dfs(e[x][0], 1, x);
		} else {
			for(auto y: e[x]) {
				dfs(y, 0, x);
			}
		}
		return 0;
	} else {
		if(e[x].size() == 1) {
			return 1;
		} else if(e[x].size() == 2) {
			for(auto y: e[x]) {
				if(y == fa) continue;
				return dfs(y, (f > 0 ? (f + 1) : 0), x) + 1;
			}
		} else {
			if(f > 0) {
				g.push_back(f);
			}
			for(auto y: e[x]) {
				if(y == fa) continue;
				int v = dfs(y, 0, x);
				if(v > 0) {
					g.push_back(v);
				}
			}
			return 0;
		}
	}
	assert(false);
}

void work() {
	
	cin >> n;
	for(int i = 1; i <= n; i++) e[i].clear();
	for(int i = 1, u, v; i < n; i++) {
		cin >> u >> v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	
	isLink = 1;
	leaf = 0;
	dfs0(1, -1);
	if(isLink == 1) {
		cout << n << endl;
		return;
	}
	
	g.clear();
	dfs(leaf, 0, -1);

	sort(g.begin(), g.end());
	assert(g.size() >= 3);
	for(auto y: g) {
		cout << y << " ";
	} cout << endl;
	cout << min(g[2], g[0] + g[1] + 1) << endl;
	
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
