/**
 * Created by YXH_XianYu on 2023.9
 * Blog: https://yxhxianyu.fun
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'

const int INF = 1LL << 60;

struct ST {
	struct Node {
		int mx;
	};
	vector<Node> t;
	#define LC (x << 1)
	#define RC (x << 1 | 1)
	ST(int n = 0) { init(n); }
	void init(int n) { t.resize(n << 2); }

	void pushup(int x) {
		t[x].mx = max(t[LC].mx, t[RC].mx);
	}
	void modify(int x, int l, int r, int pos, int va) {
		if(pos <= l && r <= pos) { t[x].mx = va; return; }
		if(pos < l || r < pos) return;

		int mid = l + r >> 1;
		if(pos <= mid) modify(LC, l, mid, pos, va);
		else modify(RC, mid+1, r, pos, va);
		pushup(x);
	}
	// [L, R]; >=va; 0leftmost or 1rightmost
	int query(int x, int l, int r, int L, int R, int va, int type) {
		int mid = l + r >> 1;
		if(t[x].mx < va || L > R) return (type == 0 ? INF : -1);
		if(l == r) {
			return l;
		}

		if(type == 0) {
			if(L <= mid && t[LC].mx >= va) {
				int v = query(LC, l, mid, L, R, va, type);
				if(v != INF) return v;
			}
			int v = query(RC, mid+1, r, L, R, va, type);
			return v;
		} else {
			if(R > mid && t[RC].mx >= va) {
				int v = query(RC, mid+1, r, L, R, va, type);
				if(v != -1) return v;
			}
			int v = query(LC, l, mid, L, R, va, type);
			return v;
		}
	}
};

struct ST2 {
	struct Node {
		int sum;
	};
	vector<Node> t;
	#define LC (x << 1)
	#define RC (x << 1 | 1)
	ST2(int n = 0) { init(n); }
	void init(int n) { t.resize(n << 2); }

	void pushup(int x) {
		t[x].sum = t[LC].sum + t[RC].sum;
	}
	void modify(int x, int l, int r, int pos, int va) {
		if(pos <= l && r <= pos) { t[x].sum = va; return; }
		if(pos < l || r < pos) return;

		int mid = l + r >> 1;
		if(pos <= mid) modify(LC, l, mid, pos, va);
		else modify(RC, mid+1, r, pos, va);
		pushup(x);
	}
	int query(int x, int l, int r, int L, int R) {
		if(L <= l && r <= R) return t[x].sum;
		if(R < l || r < L || L > R) return 0;

		int mid = l + r >> 1;
		return query(LC, l, mid, L, R) + query(RC, mid+1, r, L, R);
	}
};


void work() {
	int n, m, k;
	cin >> n >> m >> k;
	
	vector<int> a(n + 1), b(m + 1);
	for(int i = 1; i <= n; i++) cin >> a[i];
	for(int i = 1; i <= m; i++) cin >> b[i];

	vector<int> tag(n + 1);
	int j = 1;
	for(int i = 1; i <= n && j <= m; i++) {
		if(a[i] == b[j]) {
			j += 1;
			tag[a[i]] = 1;
		}
	}

	vector<int> pos(n + 1);
	for(int i = 1; i <= n; i++) pos[a[i]] = i;

	multiset<int> tool;
	for(int i = 1; i <= k; i++) {
		int x;
		cin >> x;
		tool.insert(x);
	}

	if(j != m + 1) {
		cout << "NO" << endl;
		return;
	}

	ST st(n);
	ST2 st2(n);

	for(int i = 1; i <= n; i++) st.modify(1, 1, n, i, a[i]);
	for(int i = 1; i <= n; i++) st2.modify(1, 1, n, i, 1);
	for(int i = n; i >= 1; i--) {
		if(tag[i]) continue;
		int p = pos[i];

		int L = st.query(1, 1, n, 1, p - 1, i, 1);
		int R = st.query(1, 1, n, p + 1, n, i, 0);

		L = max(0ll, L);
		R = min(n + 1, R);

		int v = st2.query(1, 1, n, L + 1, R - 1);

		auto it = tool.upper_bound(v);
		if(it == tool.begin()) {
			cout << "NO" << endl;
			return;
		} else {
			it--;
			tool.erase(it);
			st.modify(1, 1, n, p, 0);
			st2.modify(1, 1, n, p, 0);
		}
	}

	cout << "YES" << endl;
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