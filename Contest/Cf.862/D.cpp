#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;

int n;
vector<int> e[maxn];

int f1[maxn];
int f2[maxn];
int g[maxn];
void dfs1(int x, int fa) {
	f1[x] = f2[x] = 0;
	for(auto y: e[x]) {
		if(y == fa) continue;
		dfs1(y, x);
		int v = f1[y] + 1;
		if(v > f1[x]) {
			f2[x] = f1[x];
			f1[x] = v;
		} else if(v > f2[x]) {
			f2[x] = v;
		}
//		if(x == 1) cout << y << ", " << f1[x] << ", " << f2[x] << endl;
	}
}
void dfs2(int x, int fa, int va) {
	g[x] = max(f1[x], va);
	for(auto y: e[x]) {
		if(y == fa) continue;
		
		if(f1[y] + 1 == f1[x])
			dfs2(y, x, max(va + 1, f2[x] + 1));
		else
			dfs2(y, x, max(va + 1, f1[x] + 1));
	}
}

int h[maxn];

void work() {
	
	cin >> n;
	for(int i = 1; i < n; i++) {
		int x, y;
		cin >> x >> y;
		e[x].push_back(y);
		e[y].push_back(x);
	}
	
	dfs1(1, 0);
	dfs2(1, 0, 0);
	
//	for(int i = 1; i <= n; i++) cout << "(" << f1[i] << ", " << f2[i] << ", " << g[i] << ")" << endl;
//	for(int i = 1; i <= n; i++) cout << g[i] << " "; cout << endl;

	sort(g + 1, g + n + 1);
	
	int ans = 1;
	for(int i = 1, j = 1; i <= n; i++) {
		while(j <= n && i > g[j]) {
			ans = min(ans + 1, n);
			j++;
		}
		cout << ans << " ";
	}
	cout << endl;
	
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
