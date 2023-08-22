/**
 * Created by YXH_XianYu on 2023.8.21
 * Blog: https://yxhxianyu.fun
*/
#include<bits/stdc++.h>
using namespace std;
// #define int long long
#define endl '\n'

/* 无需define int long long */
/* 区间翻转 */
struct FHQ {
	struct Node {
		int lc, rc;
		int sz, pos, va;
		int tag;
		void rev() { tag ^= 1; std::swap(lc, rc); }
	};
	vector<Node> t;
	int rt, tot;

	FHQ(int n = 0) { init(n); }
	void init(int n) { t.resize(n + 1); rt = tot = 0; }

	#define LC (t[x].lc)
	#define RC (t[x].rc)
	void pushup(int x) {
		t[x].sz = t[LC].sz + t[RC].sz + 1;
	}
	int newNode(int va) {
		tot++;
		t[tot].sz = 1;
		t[tot].pos = rand() << 15 | rand();
		t[tot].va = va;
		return tot;
	}
	void pushdown(int x) {
		if(t[x].tag) {
			if(LC) t[LC].rev();
			if(RC) t[RC].rev();
			t[x].tag = 0;
		}
	}

	void splits(int x, int sz, int &l, int &r) {
		if(x == 0) { l = r = 0; return; }
		pushdown(x);
		if(sz <= t[LC].sz) { r = x; splits(LC, sz, l, LC); }
		else { l = x; splits(RC, sz-t[LC].sz-1, RC, r); }
		pushup(x);
	}
	void splitv(int x, int va, int &l, int &r) {
		if(x == 0) { l = r = 0; return; }
		pushdown(x);
		if(va < t[x].va) { r = x; splitv(LC, va, l, LC); }
		else { l = x; splitv(RC, va, RC, r); }
		pushup(x);
	}
	int merge(int l, int r) {
		if(l == 0 || r == 0) return l + r;
		if(t[l].pos < t[r].pos) {
			pushdown(l);
			t[l].rc = merge(t[l].rc, r);
			pushup(l);
			return l;
		} else {
			pushdown(r);
			t[r].lc = merge(l, t[r].lc);
			pushup(r);
			return r;
		}
	}

	void insert(int va) {
		int a, b;
		splitv(rt, va, a, b);
		rt = merge(merge(a, newNode(va)), b);
	}
	void erase(int va) {
		int a, b, c;
		splitv(rt, va, a, b);
		splits(a, t[a].sz - 1, a, c);
		rt = merge(a, b);
	}
	int getRank(int va) {
		int a, b, ans;
		splitv(rt, va - 1, a, b);
		ans = t[a].sz + 1;
		rt = merge(a, b);
		return ans;
	}
	int getVa(int sz) {
		int a, b, c, ans;
		splits(rt, sz, a, b);
		splits(a, sz - 1, a, c);
		ans = t[c].va;
		rt = merge(merge(a, c), b);
		return ans;
	}
	int getLower(int va) {
		int a, b, c, ans;
		splitv(rt, va - 1, a, b);
		splits(a, t[a].sz - 1, a, c);
		ans = t[c].va;
		rt = merge(merge(a, c), b);
		return ans;
	}
	int getUpper(int va) {
		int a, b, c, ans;
		splitv(rt, va, a, b);
		splits(b, 1, b, c);
		ans = t[b].va;
		rt = merge(merge(a, b), c);
		return ans;
	}
	void rev(int l, int r) {
		int a, b, c;
		splits(rt, l - 1, a, b);
		splits(b, r - l + 1, b, c);
		t[b].rev();
		rt = merge(merge(a, b), c);
	}

	void outputSeq(int x) {
		if(x == 0) return;
		pushdown(x);
		outputSeq(LC);
		cout << t[x].va << " ";
		outputSeq(RC);
	}
};

void work() {
	int n, m;
	cin >> n >> m;

	FHQ fhq(n);
	for(int i = 1; i <= n; i++) {
		fhq.insert(i);
	}
	
	for(int i = 1; i <= m; i++) {
		int l, r;
		cin >> l >> r;
		fhq.rev(l, r);
	}

	fhq.outputSeq(fhq.rt);
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
