/**
 * Created by YXH_XianYu on 2023.8.31
 * Blog: https://yxhxianyu.fun
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'

struct ST {
	static void upd(array<int, 4>& a, array<int, 4> b) {
		if(b[0] > a[0]) {
			a = b;
		} else if(b[0] == a[0] && b[1] < a[1]) {
			a = b;
		}
	}

	struct Node {
		array<int, 4> lv, rv, mx;

		Node operator+ (const Node& p) {
			if(this->mx[0] == 0) return p;
			if(p.mx[0] == 0) return *this;

			Node c{};

			upd(c.mx, (*this).mx);
			upd(c.mx, p.mx);

			if((*this).rv[3] == p.lv[3]) {
				int len = p.lv[2] - (*this).rv[1] + 1;
				upd(c.mx, {len, (*this).rv[1], p.lv[2], 0});
			}

			
			c.lv = (*this).lv;
			if((*this).lv[1] == (*this).rv[1] && (*this).lv[2] == (*this).rv[2] && (*this).lv[3] == p.lv[3]) {
				c.lv[2] = p.lv[2];
			}
			c.rv = p.rv;
			if(p.rv[1] == p.lv[1] && p.rv[2] == p.lv[2] && p.rv[3] == (*this).rv[3]) {
				c.rv[1] = (*this).rv[1];
			}

			return c;
		}
	};
	vector<Node> t;
	#define LC (x << 1)
	#define RC (x << 1 | 1)

	ST(int n = 0) { init(n); }
	void init(int n) { t.resize(n << 2); }


	void pushup(int x) {
		t[x] = t[LC] + t[RC];
	}

	void build(int x, int l, int r, string& s) {
		if(l == r) {
			t[x].mx = {1, l, l};
			t[x].lv = t[x].rv = {1, l, l, ((int)(s[l]))};
			return;
		}

		int mid = l + r >> 1;
		build(LC, l, mid, s);
		build(RC, mid+1, r, s);
		pushup(x);
	}
	void modify(int x, int l, int r, int pos, int v) {
		if(pos <= l && r <= pos) {
			t[x].mx = {1, l, l};
			t[x].lv = t[x].rv = {1, l, l, v};
			return;
		}
		if(pos < l || r < pos) return;

		int mid = l + r >> 1;
		if(pos <= mid) modify(LC, l, mid, pos, v);
		else modify(RC, mid+1, r, pos, v);
		pushup(x);
	}
	Node query(int x, int l, int r, int L, int R) {
		if(L <= l && r <= R) return t[x];
		if(R < l || r < L) return Node();

		int mid = l + r >> 1;
		return query(LC, l, mid, L, R) + query(RC, mid+1, r, L, R);
	}
};

void work() {
	int n, m;
	cin >> n >> m;

	string s;
	cin >> s;
	s = " " + s;

	ST st(n);
	st.build(1, 1, n, s);

	for(int i = 1; i <= m; i++) {
		int opt;
		cin >> opt;

		if(opt == 1) {
			int x, y;
			cin >> x >> y;
			auto ans = st.query(1, 1, n, x, y);
			cout << ans.mx[1] << " " << ans.mx[2] << endl;
		} else if(opt == 2) {
			int x; char ch;
			cin >> x >> ch;
			st.modify(1, 1, n, x, ch);
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