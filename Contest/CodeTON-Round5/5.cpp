#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;
const int INF = 1LL << 60;

struct SegmentTree {
	struct Node {
		int s;
		int lzt;
	};
	vector<Node> t;
	#define LC (x << 1)
	#define RC (x << 1 | 1)
	SegmentTree(int n): t(vector<Node>(n << 3)) {
	}
	void pushup(int x) {
		t[x].s = min(t[LC].s, t[RC].s);
	}
	void pushdown(int x) {
		if(t[x].lzt) {
			t[LC].s += t[x].lzt;
			t[LC].lzt += t[x].lzt;
			t[RC].s += t[x].lzt;
			t[RC].lzt += t[x].lzt;
			t[x].lzt = 0;
		}
	}
	void build(int x, int l, int r) {
		t[x].s = INF;
		if(l == r) return;
		int mid = l + r >> 1;
		build(LC, l, mid);
		build(RC, mid+1, r);
		pushup(x);
	}
	void modify(int x, int l, int r, int pos, int va) {
		if(pos <= l && r <= pos) {
			t[x].s = va;
			return;
		}
		if(pos < l || r < pos || l == r) return;
		int mid = l + r >> 1;
		pushdown(x);
		modify(LC, l, mid, pos, va);
		modify(RC, mid+1, r, pos, va);
		pushup(x);
	}
	void rangeAdd(int x, int l, int r, int L, int R, int va) {
		if(L <= l && r <= R) {
			t[x].s += va;
			t[x].lzt += va;
			return;
		}
		if(R < l || r < L || l == r) return;
		int mid = l + r >> 1;
		pushdown(x);
		rangeAdd(LC, l, mid, L, R, va);
		rangeAdd(RC, mid+1, r, L, R, va);
		pushup(x);
	}
	int query(int x, int l, int r, int L, int R) {
		if(L <= l && r <= R) return t[x].s;
		if(R < l || r < L) return INF;
		int mid = l + r >> 1;
		pushdown(x);
		return min(query(LC, l, mid, L, R), query(RC, mid+1, r, L, R));
	}
	#undef LC
	#undef RC
};

void work() {
	int n, k, A;
	cin >> n >> k >> A;

	vector<array<int, 3>> a(n + 1);
	for(int i = 1; i <= n; i++) {
		cin >> a[i][0] >> a[i][1] >> a[i][2];
		a[i][1] = k - a[i][1];
	}

	sort(a.begin() + 1, a.begin() + n + 1, [&](const array<int, 3>& a, const array<int, 3>&b) {
		if(a[1] != b[1]) return a[1] < b[1];
		return a[0] > b[0];
	});

	// for(int i = 1; i <= n; i++) cout << i << ": " << a[i][0] << ", " << a[i][1] << ", " << a[i][2] << endl;

	int sum = 0;
	for(int i = 1; i <= n; i++) sum += a[i][2];

	vector<vector<array<int, 3>>> b(k + 1, vector<array<int, 3>>());
	for(int i = 1; i <= n; i++) {
		b[a[i][1]].push_back(a[i]);
	}

	vector<int> f(k + 1, sum);
	SegmentTree seg(k);
	seg.build(1, 0, k);

	/**
	 * f[i]: 前i行可以铺三角形的最小总花费
	 * f[i] = min{f[i-1], f[j] - A*(i-j) - cost{可以被j+1~i的三角形覆盖的点}}, j in [0, i-1]
	 *      = min{f[i-1], f[j] - A*(i-j) - cost{y<=i && x>j}}, j in [0, i-1]
	 * 
	 * 线段树维护 f[j] - A*j - cost{y<=i && x>j}
	*/
	seg.modify(1, 0, k, 0, sum);
	for(int i = 1; i <= k; i++) {
		for(auto& x: b[i]) {
			seg.rangeAdd(1, 0, k, 0, x[0], -x[2]);
		}
		f[i] = min(f[i - 1], seg.query(1, 0, k, 0, i - 1) + i * A);
		seg.modify(1, 0, k, i, f[i] - i * A);
	}

	cout << f[k] << endl;
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
