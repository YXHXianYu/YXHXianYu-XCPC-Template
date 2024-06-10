#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;


void work() {
	int n, m;
	cin >> n >> m;

	vector<int> a(n + 1);
	for(int i = 1; i <= n; i++) cin >> a[i];

	vector<pair<int, int>> edge(m + 1);
	vector<vector<int>> e(n + 1, vector<int>());
	for(int i = 1; i <= m; i++) {
		int u, v;
		cin >> u >> v;
		edge[i] = {u, v};
		e[u].push_back(v);
	}

	// tarjan
	vector<int> dfn(n + 1), low(n + 1), scc(n + 1), stk(n + 1), va(n + 1);
	int dfncnt = 0, scccnt = 0, top = 0;
	
	function<void(int)> tarjan = [&](int x) {
		dfn[x] = low[x] = ++dfncnt;
		stk[++top] = x;
		for(auto y: e[x]) {
			if(!dfn[y]) tarjan(y);
			if(!scc[y]) low[x] = min(low[x], low[y]);
		}
		if(dfn[x] == low[x]) {
			scccnt++;
			for(; stk[top + 1] != x; top--) {
				scc[stk[top]] = scccnt;
				va[scccnt] += a[stk[top]];
			}
		}
	};

	for(int i = 1; i <= n; i++) if(!dfn[i]) tarjan(i);

	// new graph
	int N = scccnt;
	vector<int> indeg(N + 1);
	for(int i = 1; i <= N; i++) e[i].clear();
	for(int i = 1; i <= m; i++) {
		auto [u, v] = edge[i];
		if(scc[u] == scc[v]) continue;
		u = scc[u];
		v = scc[v];
		e[u].push_back(v);
		indeg[v]++;
	}

	// topo
	vector<int> f(N + 1);
	vector<int> q(N + 1);
	int hd = 0, tl = 0;
	for(int i = 1; i <= N; i++) {
		if(indeg[i] == 0) {
			q[++tl] = i;
		}
	}

	while(hd < tl) {
		int x = q[++hd];
		f[x] += va[x];
		for(auto y: e[x]) {
			f[y] = max(f[y], f[x]);
			if(--indeg[y] == 0) q[++tl] = y;
		}
	}

	int ans = 0;
	for(int i = 1; i <= N; i++) ans = max(ans, f[i]);

	cout << ans << endl;
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
