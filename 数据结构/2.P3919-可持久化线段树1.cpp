#include<bits/stdc++.h>
using namespace std;
// #define int long long
#define endl '\n'

/**
 * 长度为N的数组
 * 1. 在某个历史版本上修改某一位置的值
 * 2. 查询某个历史版本上某一位置的值
*/

// 空间复杂度 O(nlogn + qlogn)
struct PST {
	#define LLI long long
	struct Node {
		int lc, rc;
		LLI v;
	};
	vector<Node> t;
	int tot;
	#define LC (t[x].lc)
	#define RC (t[x].rc)

	PST(int n = 0) { init(n); }
	void init(int n) { t.resize(n); tot = 0; }

	int newNode() {
		tot++;
		t[tot].lc = t[tot].rc = t[tot].v = 0;
		return tot;
	}
	int clone(int p) {
		tot++;
		t[tot] = t[p];
		return tot;
	}

	void build(int &x, int l, int r, const vector<int>& a) {
		x = newNode();
		if(l == r) {
			t[x].v = a[l];
			return;
		}

		int mid = l + r >> 1;
		build(LC, l, mid, a);
		build(RC, mid+1, r, a);
	}
	void modify(int &x, int y, int l, int r, int pos, int v) {
		x = clone(y);
		if(l == r) {
			t[x].v = v;
			return;
		}

		int mid = l + r >> 1;
		if(pos <= mid) {
			modify(LC, t[y].lc, l, mid, pos, v);
			RC = t[y].rc;
		} else {
			modify(RC, t[y].rc, mid+1, r, pos, v);
			LC = t[x].lc;
		}
	}
	int query(int x, int l, int r, int pos) {
		if(!x) return 0;
		if(pos <= l && r <= pos) return t[x].v;
		int mid = l + r >> 1;
		if(pos <= mid) return query(LC, l, mid, pos);
		else return query(RC, mid+1, r, pos);
	}
};

void work() {
	int n, m;
	cin >> n >> m;

	vector<int> a(n + 1);
	for(int i = 1; i <= n; i++) cin >> a[i];

	PST pst((n + m) * 20); // (n + q) logn
	vector<int> rt(m + 1);
	pst.build(rt[0], 1, n, a);

	for(int i = 1; i <= m; i++) {
		int ver, opt;
		cin >> ver >> opt;

		if(opt == 1) {
			int pos, v;
			cin >> pos >> v;

			pst.modify(rt[i], rt[ver], 1, n, pos, v);
		} else if(opt == 2) {
			int pos;
			cin >> pos;

			rt[i] = rt[ver];
			cout << pst.query(rt[ver], 1, n, pos) << '\n';

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
