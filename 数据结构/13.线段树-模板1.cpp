/**
 * Created by YXH_XianYu on 2023.8.22
 * Blog: https://yxhxianyu.fun
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'


struct ST {
	struct Node {
		int s, lzt;
	};
	vector<Node> t;
	#define LC (x << 1)
	#define RC (x << 1 | 1)

	ST(int n = 0) { init(n); }
	void init(int n) { t.resize(n << 2); }

	void pushup(int x) {
		t[x].s = t[LC].s + t[RC].s;
	}
	void pushdown(int x, int l, int r) {
		if(t[x].lzt) {
			int mid = l + r >> 1;

			t[LC].s += t[x].lzt * (mid - l + 1);
			t[LC].lzt += t[x].lzt;

			t[RC].s += t[x].lzt * (r - mid);
			t[RC].lzt += t[x].lzt;

			t[x].lzt = 0;
		}
	}
	void build(int x, int l, int r, vector<int>& a) {
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
			t[x].s += va * (r - l + 1);
			t[x].lzt += va;
			return;
		}
		if(R < l || r < L) return;

		pushdown(x, l, r);
		int mid = l + r >> 1;
		modify(LC, l, mid, L, R, va);
		modify(RC, mid+1, r, L, R, va);
		pushup(x);
	}
	int query(int x, int l, int r, int L, int R) {
		if(L <= l && r <= R) return t[x].s;
		if(R < l || r < L) return 0;

		pushdown(x, l, r);
		int mid = l + r >> 1;
		return query(LC, l, mid, L, R) + query(RC, mid+1, r, L, R);
	}
};


void work() {
	int n, m;
	cin >> n >> m;

	vector<int> a(n + 1);
	for(int i = 1; i <= n; i++) cin >> a[i];

	ST st(n);
	st.build(1, 1, n, a);

	for(int i = 1; i <= m; i++) {
		int opt;
		cin >> opt;
		if(opt == 1) {
			int x, y, k;
			cin >> x >> y >> k;
			st.modify(1, 1, n, x, y, k);
		} else if(opt == 2) {
			int x, y;
			cin >> x >> y;
			cout << st.query(1, 1, n, x, y) << endl;
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
