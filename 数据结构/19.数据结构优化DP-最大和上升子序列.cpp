#include<bits/stdc++.h>
using namespace std;
#define int long long

struct SegmentTree {
	struct Node {
		int mx;
	};
	vector<Node> t;

	SegmentTree(int n = 0) { myInitialize(n); }
	void myInitialize(int n) { t.resize(n * 4 + 1); }

	#define LC (x << 1)
	#define RC (x << 1 | 1)
	void pushup(int x) {
		t[x].mx = max(t[LC].mx, t[RC].mx);
	}
	void modify(int x, int l, int r, int pos, int va) {
		if(pos <= l && r <= pos) {
			t[x].mx = va;
			return;
		}
		if(pos < l || r < pos) return;

		int mid = l + r >> 1;
		if(pos <= mid) modify(LC, l, mid, pos, va);
		if(mid < pos) modify(RC, mid+1, r, pos, va);
		pushup(x);
	}
	int query(int x, int l, int r, int L, int R) {
		if(L <= l && r <= R) return t[x].mx;
		if(R < l || r < L) return 0;
		
		int mid = l + r >> 1;
		return max(
			(L <= mid ? query(LC, l, mid, L, R) : 0ll),
			(mid < R ? query(RC, mid+1, r, L, R) : 0ll)
		);
	}
};

void work() {
	int n;
	cin >> n;

	vector<int> a(n + 1);
	for(int i = 1; i <= n; i++) cin >> a[i];

	int N = 0;
	for(int i = 1; i <= n; i++) N = max(N, a[i]);

	SegmentTree myst(N);
	vector<int> b(n + 1);
	for(int i = 1; i <= n; i++) {
		int v = myst.query(1, 1, N, 1, a[i] - 1);
		if(b[a[i]] < v + a[i]) myst.modify(1, 1, N, a[i], v + a[i]);
	}

	cout << myst.query(1, 1, N, 1, N) << endl;
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