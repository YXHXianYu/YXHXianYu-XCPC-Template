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
		int mn;
		int lzt;
	};
	vector<Node> t;

	ST(int n = 0) { init(n); }
	void init(int n) { t.resize(n << 2); }

	#define LC (x << 1)
	#define RC (x << 1 | 1)

	void pushup(int x) {
		t[x].mn = min(t[LC].mn, t[RC].mn);
	}
	void pushdown(int x) {
		if(t[x].lzt != 0) {
			t[LC].mn += t[x].lzt;
			t[LC].lzt += t[x].lzt;

			t[RC].mn += t[x].lzt;
			t[RC].lzt += t[x].lzt;

			t[x].lzt = 0;
		}
	}

	void modify(int x, int l, int r, int L, int R, int va) {
		if(L <= l && r <= R) {
			t[x].mn += va;
			t[x].lzt += va;
			return;
		}
		if(R < l || r < L) return;

		pushdown(x);
		int mid = l + r >> 1;
		modify(LC, l, mid, L, R, va);
		modify(RC, mid+1, r, L, R, va);
		pushup(x);
	}
	int query(int x, int l, int r, int L, int R) {
		if(L <= l && r <= R) return t[x].mn;
		if(R < l || r < L) return INF;

		pushdown(x);
		int mid = l + r >> 1;
		return min(query(LC, l, mid, L, R), query(RC, mid+1, r, L, R));
	}
	void output(int n) {
		for(int i = 1; i <= n; i++) cout << query(1, 1, n, i, i) << " ";
		cout << endl;
	}
};

void work() {
	int n;
	cin >> n;

	vector<int> p(n + 1), a(n + 1);
	for(int i = 1; i <= n; i++) cin >> p[i];
	for(int i = 1; i <= n; i++) cin >> a[i];

	ST st(n + 2);

	/*
	ans[i] = sum{a[j], j <= i && p[j] > k} + sum{a[j], j > i && p[j] <= k}
	pre[k] = sum{a[j], j <= i && p[j] > k}
	suf[k] = sum{a[j], j > i && p[j] <= k}
	// i = 0
	*/

	for(int i = 1; i <= n; i++) {
		st.modify(1, 0, n + 1, p[i], n + 1, a[i]);
	}

	int ans = INF;
	for(int i = 1; i < n; i++) {
		st.modify(1, 0, n + 1, p[i], n + 1, -a[i]);
		st.modify(1, 0, n + 1, 0, p[i] - 1, a[i]);
		
		ans = min(ans, st.query(1, 0, n + 1, 0, n + 1));
	}

	cout << ans << endl;
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