#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'

/* 线段树 单点加 区间最大值 线段树合并*/
struct ST {
	struct Node {
		int lc, rc;
		array<int, 2> s;
	};
	vector<Node> t;
	int tot;
	#define LC (t[x].lc)
	#define RC (t[x].rc)

	ST(int n = 0) { init(n); }
	void init(int n) { t.resize(n); tot = 0; }

	int newNode() { return ++tot; }
	void pushup(int x) {
		t[x].s = max(t[LC].s, t[RC].s);
	}

	void modify(int &x, int l, int r, int pos, int v) {
		if(!x) x = newNode();
		if(pos <= l && r <= pos) {
			if(t[x].s[1] == 0) t[x].s = {v, -l};
			else t[x].s[0] += v;
			return;
		}
		if(pos < l || r < pos) return;
		int mid = l + r >> 1;
		if(pos <= mid) modify(LC, l, mid, pos, v);
		else modify(RC, mid+1, r, pos, v);
		pushup(x);
	}

	array<int, 2> query(int x, int l, int r, int L, int R) {
		if(!x) return {0, 0};
		if(L <= l && r <= R) return t[x].s;
		if(R < l || r < L) return {0, 0};
		int mid = l + r >> 1;
		return max(query(LC, l, mid, L, R), query(RC, mid+1, r, L, R));
	}
	
	int merge(int x, int y, int l, int r) {
		if(!x || !y) return x + y;
		if(l == r) {
			t[x].s = {t[x].s[0] + t[y].s[0], -l};
			return x;
		}
		int mid = l + r >> 1;
		LC = merge(LC, t[y].lc, l, mid);
		RC = merge(RC, t[y].rc, mid+1, r);
		pushup(x);
		return x;
	}
};

void work() {
	int n, m;
	cin >> n >> m;

	vector<vector<int>> e(n + 1, vector<int>());
	for(int i = 1; i < n; i++) {
		int u, v;
		cin >> u >> v;
		e[u].push_back(v);
		e[v].push_back(u);
	}

	/* 树链剖分 */
	vector<int> fa(n + 1), sz(n + 1), son(n + 1), dep(n + 1),
				dfn(n + 1), dfnR(n + 1), top(n + 1), rk(n + 1);

	function<void(int)> dfs1 = [&](int x) {
		dep[x] = dep[fa[x]] + 1;
		sz[x] = 1;
		for(auto y: e[x]) {
			if(y == fa[x]) continue;
			fa[y] = x;
			dfs1(y);
			sz[x] += sz[y];
			if(sz[y] > sz[son[x]]) son[x] = y;
		}
	};
	function<void(int)> dfs2 = [&](int x) {
		dfn[x] = ++dfn[0];
		rk[dfn[0]] = x;
		if(!top[x]) top[x] = x;
		if(son[x]) top[son[x]] = top[x], dfs2(son[x]);
		for(auto y: e[x]) if(y != fa[x] && y != son[x]) dfs2(y);
		dfnR[x] = dfn[0];
	};
	auto getLca = [&](int x, int y) {
		while(top[x] != top[y]) {
			if(dep[top[x]] > dep[top[y]]) swap(x, y);
			y = fa[top[y]];
		}
		if(dep[x] > dep[y]) swap(x, y);
		return x;
	};
	
	dfs1(1);
	dfs2(1);

	/* 线段树（调用） */
	int N = 1e5;
	ST st(5 * m * __lg(N));
	vector<int> rt(n + 1);

	for(int i = 1; i <= m; i++) {
		int x, y, z;
		cin >> x >> y >> z;

		int lca = getLca(x, y);

		st.modify(rt[x], 1, N, z, 1);
		st.modify(rt[y], 1, N, z, 1);
		st.modify(rt[lca], 1, N, z, -1);
		st.modify(rt[fa[lca]], 1, N, z, -1);
	}

	/* 树上差分 */

	vector<int> ans(n + 1);
	function<void(int)> dfs3 = [&](int x) {
		for(auto y: e[x]) {
			if(y == fa[x]) continue;
			dfs3(y);
			rt[x] = st.merge(rt[x], rt[y], 1, N);
		}
		ans[x] = -st.query(rt[x], 1, N, 1, N)[1];
	};
	dfs3(1);

	for(int i = 1; i <= n; i++) cout << ans[i] << endl;
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
