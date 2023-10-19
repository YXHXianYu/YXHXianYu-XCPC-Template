/**
 * Created by YXH_XianYu in 2023.10
 * Blog: https://yxhxianyu.fun
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long

// 区间修改、区间求和
struct ST {
	struct Node {
		int s, lzt;
	};
	vector<Node> t;

	#define LC (x << 1)
	#define RC (x << 1 | 1)

	ST(int n) {
		t.resize(n << 2);
	}

	void pushdown(int x, int l, int r) {
		if(t[x].lzt == -1) {
			t[LC].s = 0;
			t[LC].lzt = -1;
			t[RC].s = 0;
			t[RC].lzt = -1;
		} else if(t[x].lzt == 1) {
			int mid = l + r >> 1;
			t[LC].s = (mid - l + 1);
			t[LC].lzt = 1;
			t[RC].s = (r - mid);
			t[RC].lzt = 1;
		} else if(t[x].lzt == 0) {
			;
		} else assert(false);
		t[x].lzt = 0;
	}
	void pushup(int x) {
		t[x].s = t[LC].s + t[RC].s;
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
	void modify(int x, int l, int r, int L, int R, int v) {
		if(L <= l && r <= R) {
			if(v == 1) {
				t[x].s = (r - l + 1);
				t[x].lzt = 1;
			} else {
				t[x].s = 0;
				t[x].lzt = -1;
			}
			return;
		}
		if(R < l || r < L || L > R) return;

		pushdown(x, l, r);
		int mid = l + r >> 1;
		modify(LC, l, mid, L, R, v);
		modify(RC, mid+1, r, L, R, v);
		pushup(x);
	}
	int query(int x, int l, int r, int L, int R) {
		if(L <= l && r <= R) return t[x].s;
		if(R < l || r < L || L > R) return 0;

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

	vector<array<int, 3>> q(m + 1);
	for(int i = 1; i <= m; i++) cin >> q[i][0] >> q[i][1] >> q[i][2];

	int Q;
	cin >> Q;

	auto check = [&](int mid) {

		vector<int> b(n + 1);
		for(int i = 1; i <= n; i++) {
			b[i] = (a[i] >= mid);
		}

		// cout << "check " << mid << " : " << endl;

		ST st(n);
		st.build(1, 1, n, b);

		// for(int i = 1; i <= n; i++) cout << b[i] << " "; cout << '\n';

		for(int i = 1; i <= m; i++) {
			if(q[i][0] == 0) {
				int L = q[i][1];
				int R = q[i][2];
				int v = (R - L + 1) - st.query(1, 1, n, L, R);
				// cout << "(" << v << ")";
				st.modify(1, 1, n, L, L+v-1, 0);
				st.modify(1, 1, n, L+v, R, 1);
			} else if(q[i][0] == 1) {
				int L = q[i][1];
				int R = q[i][2];
				int v = st.query(1, 1, n, L, R);
				// cout << "(" << v << ")";
				st.modify(1, 1, n, L, L+v-1, 1);
				st.modify(1, 1, n, L+v, R, 0);
			} else assert(false);

			// for(int i = 1; i <= n; i++) cout << st.query(1, 1, n, i, i) << " "; cout << '\n';
		}

		// for(int i = 1; i <= n; i++) cout << st.query(1, 1, n, i, i) << " "; cout << '\n';

		int res = st.query(1, 1, n, Q, Q);
		return res == 1;
	};

	// <  mid => 0
	// >= mid => 1
	int L = 1, R = n + 1;
	while(R - L >= 2) {
		int mid = L + R >> 1;
		if(check(mid)) {
			L = mid;
		} else {
			R = mid;
		}
	}

	cout << L << '\n';
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