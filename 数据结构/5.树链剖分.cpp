/**
 * Created by YXH_XianYu on 2023.8.21
 * Blog: https://yxhxianyu.fun
*/
#include<bits/stdc++.h>
using namespace std;
// #define int long long
#define endl '\n'

int mod;

void upd(int &a, int b) { a += b; if(a >= mod) a -= mod; }

/* 本模板不需要define int long long */
struct ST {
	struct Node {
		int s, lzt;
	};
	vector<Node> t;
	ST(int n = 0) { init(n); }
	void init(int n) { t.resize(n); }

	#define LC (x << 1)
	#define RC (x << 1 | 1)
	void pushup(int x) {
		t[x].s = t[LC].s + t[RC].s;
		if(t[x].s >= mod) t[x].s -= mod;
	}
	void pushdown(int x, int l, int r) {
		if(t[x].lzt) {
			int mid = l + r >> 1;

			upd(t[LC].s, t[x].lzt * (mid - l + 1) % mod);
			upd(t[LC].lzt, t[x].lzt);

			upd(t[RC].s, t[x].lzt * (r - mid) % mod);
			upd(t[RC].lzt, t[x].lzt);

			t[x].lzt = 0;
		}
	}
	void build(int x, int l, int r, const vector<int>& a) {
		if(l == r) {
			t[x].s = a[l];
			return;
		}
		int mid = l + r >> 1;
		build(LC, l, mid, a);
		build(RC, mid+1, r, a);
		pushup(x);
	}
	void modify(int x, int l, int r, int L, int R, int va) {
		if(L <= l && r <= R) {
			upd(t[x].s, va * (r - l + 1) % mod);
			upd(t[x].lzt, va);
			return;
		}
		if(R < l || r < L) return;
		pushdown(x, l, r);
		int mid = l + r >> 1;
		if(L <= mid) modify(LC, l, mid, L, R, va);
		if(mid < R) modify(RC, mid+1, r, L, R, va);
		pushup(x);
	}
	int query(int x, int l, int r, int L, int R) {
		if(L <= l && r <= R) return t[x].s;
		if(R < l || r < L) return 0;
		pushdown(x, l, r);
		int mid = l + r >> 1;
		int ans = 0;
		if(L <= mid) upd(ans, query(LC, l, mid, L, R));
		if(mid < R) upd(ans, query(RC, mid+1, r, L, R));
		return ans;
	}
};


void work() {
	int n, m, rt;
	cin >> n >> m >> rt >> mod;

	vector<int> a(n + 1);
	for(int i = 1; i <= n; i++) cin >> a[i];

	vector<vector<int>> e(n + 1, vector<int>());
	for(int i = 1; i < n; i++) {
		int u, v;
		cin >> u >> v;
		e[u].push_back(v);
		e[v].push_back(u);
	}

	ST st((n << 2) + 1);

	// ShuPou
	vector<int> fa(n + 1), dep(n + 1), sz(n + 1), son(n + 1);
	vector<int> dfn(n + 1), dfnR(n + 1), rk(n + 1), top(n + 1);

	function<void(int)> dfs1 = [&](int x) {
		dep[x] = dep[fa[x]] + 1;
		sz[x] = 1;
		for(auto y: e[x]) {
			if(fa[x] == y) continue;
			fa[y] = x;
			dfs1(y);
			sz[x] += sz[y];
			if(sz[son[x]] < sz[y]) son[x] = y;
		}
	};
	function<void(int)> dfs2 = [&](int x) {
		dfn[x] = ++dfn[0];
		rk[dfn[0]] = x;

		st.modify(1, 1, n, dfn[x], dfn[x], a[x]);

		if(!top[x]) top[x] = x;
		if(son[x]) top[son[x]] = top[x], dfs2(son[x]);
		for(auto y: e[x]) if(y != fa[x] && y != son[x]) dfs2(y);
		dfnR[x] = dfn[0];
	};

	dfs1(rt);
	dfs2(rt);

	auto subtreeAdd = [&](int x, int v) {
		st.modify(1, 1, n, dfn[x], dfnR[x], v);
	};
	auto subtreeQuery = [&](int x) {
		return st.query(1, 1, n, dfn[x], dfnR[x]);
	};

	auto getLCA = [&](int x, int y) {
		while(top[x] != top[y]) {
			if(dep[top[x]] > dep[top[y]]) swap(x, y);
			y = fa[top[y]];
		}
		if(dep[x] > dep[y]) swap(x, y);
		return x;
	};
	auto pathAdd = [&](int x, int y, int v) {
		while(top[x] != top[y]) {
			if(dep[top[x]] > dep[top[y]]) swap(x, y);
			st.modify(1, 1, n, dfn[top[y]], dfn[y], v);
			y = fa[top[y]];
		}
		if(dep[x] > dep[y]) swap(x, y);
		st.modify(1, 1, n, dfn[x], dfn[y], v);
	};
	auto pathQuery = [&](int x, int y) {
		int ans = 0;
		while(top[x] != top[y]) {
			if(dep[top[x]] > dep[top[y]]) swap(x, y);
			upd(ans, st.query(1, 1, n, dfn[top[y]], dfn[y]));
			y = fa[top[y]];
		}
		if(dep[x] > dep[y]) swap(x, y);
		upd(ans, st.query(1, 1, n, dfn[x], dfn[y]));
		return ans;
	};


	for(int i = 1; i <= m; i++) {
		int opt;
		cin >> opt;
		if(opt == 1) {
			int x, y, z;
			cin >> x >> y >> z;
			pathAdd(x, y, z);
		} else if(opt == 2) {
			int x, y;
			cin >> x >> y;
			cout << pathQuery(x, y) << endl;
		} else if(opt == 3) {
			int x, z;
			cin >> x >> z;
			subtreeAdd(x, z);
		} else if(opt == 4) {
			int x;
			cin >> x;
			cout << subtreeQuery(x) << endl;
		} else assert(false);
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
