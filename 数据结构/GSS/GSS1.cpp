/**
 * Created by YXH_XianYu in 2023.10
 * Blog: https://yxhxianyu.fun
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'

struct ST {
	struct Node {
		int lv, rv, lrv, ans;
		int len;
	};
	Node add(Node a, Node b) {
		if(a.len == 0) return b;
		if(b.len == 0) return a;
		Node c;
		c.ans = max(a.ans, b.ans);
		c.ans = max(c.ans, a.rv + b.lv);
		c.lv = max(a.lv, a.lrv + b.lv);
		c.rv = max(b.rv, b.lrv + a.rv);
		c.lrv = a.lrv + b.lrv;
		c.len = a.len + b.len;
		return c;
	}
	vector<Node> t;

	#define LC (x << 1)
	#define RC (x << 1 | 1)

	ST(int n) {
		t.resize(n << 2);
	}

	void pushup(int x) {
		t[x] = add(t[LC], t[RC]);
	}
	void build(int x, int l, int r, const vector<int>& a) {
		if(l == r) {
			t[x].ans = t[x].lv = t[x].rv = t[x].lrv = a[l];
			t[x].len = 1;
			return;
		}

		int mid = l + r >> 1;
		build(LC, l, mid, a);
		build(RC, mid+1, r, a);
		pushup(x);
	}
	Node query(int x, int l, int r, int L, int R) {
		if(L <= l && r <= R) return t[x];
		if(R < l || r < L) return Node{};

		int mid = l + r >> 1;
		return add(query(LC, l, mid, L, R), query(RC, mid+1, r, L, R));
	}
};

void work() {
	int n;
	cin >> n;

	vector<int> a(n + 1);
	for(int i = 1; i <= n; i++) cin >> a[i];

	ST st(n);
	st.build(1, 1, n, a);

	int m;
	cin >> m;

	for(int i = 1; i <= m; i++) {
		int L, R;
		cin >> L >> R;
		cout << st.query(1, 1, n, L, R).ans << endl;
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