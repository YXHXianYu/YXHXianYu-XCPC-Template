#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;


void work() {
	int n, m;
	cin >> n >> m;

	// 0...2n-1: 2*i, 2*i+1
	// 0 index for x^1
	int N = n << 1;
	vector<vector<int>> e(N + 1, vector<int>());
	for(int i = 1; i <= m; i++) {
		char c1, c2;
		int u, v;
		cin >> c1 >> u >> c2 >> v;
		
		u--;
		v--;
		u = u * 2 + (c1 == 'h');
		v = v * 2 + (c2 == 'h');
		// u or v = 1
		e[u^1].push_back(v);
		e[v^1].push_back(u);
	}

	// tarjan
	int dfnCnt = 0, sccCnt = 0, top = 0;
	vector<int> dfn(N + 1), low(N + 1), scc(N + 1), stk(N + 2, -1);

	function<void(int)> tarjan = [&](int x) {
		dfn[x] = low[x] = ++dfnCnt;
		stk[++top] = x;
		for(auto y: e[x]) {
			if(!dfn[y]) tarjan(y);
			if(!scc[y]) low[x] = min(low[x], low[y]);
		}
		if(dfn[x] == low[x]) {
			sccCnt++;
			for(; stk[top + 1] != x; top--) {
				scc[stk[top]] = sccCnt;
			}
		}
	};

	for(int i = 0; i < N; i++) if(!dfn[i])
		tarjan(i);

	for(int i = 0; i < n; i++) {
		// scc[i << 1] < scc[i << 1 | 1] => choose i<<1
		if(scc[i << 1] == scc[i << 1 | 1]) {
			cout << "BAD" << endl;
			return;
		}
	}
	cout << "GOOD" << endl;
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
