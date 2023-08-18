#include<bits/stdc++.h>
using namespace std;
// #define int long long
#define endl '\n'

/**
 * 可持久化线段树，查询区间第k小
*/

struct PST {
	struct Node {
		int lc, rc, v;
	};
	vector<Node> t;
	int tot;
	#define LC (t[x].lc)
	#define RC (t[x].rc)

	PST(int n = 0) { init(n); }
	void init(int n) { t.resize(n + 1); tot = 0; }

	int newNode() { tot++; t[tot].lc = t[tot].rc = t[tot].v = 0; return tot; }
	int clone(int p) { tot++; t[tot] = t[p]; return tot; }

	void pushup(int x) { t[x].v = t[LC].v + t[RC].v; }
	void build(int &x, int l, int r) {
		x = newNode();
		if(l == r) return;
		int mid = l + r >> 1;
		build(LC, l, mid);
		build(RC, mid+1, r);
	}
	void add(int &x, int y, int l, int r, int pos, int va) {
		x = clone(y);
		if(pos <= l && r <= pos) {
			t[x].v += va;
			return;
		}
		if(pos < l || r < pos) return;

		int mid = l + r >> 1;
		if(pos <= mid) add(LC, t[y].lc, l, mid, pos, va);
		else add(RC, t[y].rc, mid+1, r, pos, va);
		pushup(x);
	}
	int query(int x, int y, int l, int r, int k) {
		if(l == r) return l;
		int s = t[t[x].lc].v - t[t[y].lc].v;
		int mid = l + r >> 1;
		if(k <= s) return query(t[x].lc, t[y].lc, l, mid, k);
		else return query(t[x].rc, t[y].rc, mid+1, r, k - s);
	}
};

void work() {
	int n, m;
	cin >> n >> m;

	vector<int> a(n + 1);
	for(int i = 1; i <= n; i++) cin >> a[i];

	auto b = a;
	sort(b.begin() + 1, b.end());
	b.erase(unique(b.begin() + 1, b.end()), b.end());
	map<int, int> f;
	map<int, int> g;
	for(int i = 1; i < b.size(); i++) {
		f[b[i]] = i;
		g[i] = b[i];
	}
	for(int i = 1; i <= n; i++) a[i] = f[a[i]];

	// for(int i = 1; i <= n; i++) cout << a[i] << " "; cout << endl;

	PST pst((n + m) * 20);
	vector<int> rt(n + 1);
	pst.build(rt[0], 1, n);

	for(int i = 1; i <= n; i++) {
		pst.add(rt[i], rt[i - 1], 1, n, a[i], 1);
	}

	for(int i = 1; i <= m; i++) {
		int l, r, k;
		cin >> l >> r >> k;
		cout << g[pst.query(rt[r], rt[l - 1], 1, n, k)] << endl;
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
