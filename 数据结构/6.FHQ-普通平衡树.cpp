/**
 * Created by YXH_XianYu on 2023.8.21
 * Blog: https://yxhxianyu.fun
*/
#include<bits/stdc++.h>
using namespace std;
// #define int long long
#define endl '\n'

/* 无需define int long long */
/* 插入、删除、前驱、后继、排名、查值 */
struct FHQ {
	struct Node {
		int lc, rc;
		#define LC (t[x].lc)
		#define RC (t[x].rc)
		int sz, pos, va;
	};
	vector<Node> t;
	int rt, tot;

	FHQ(int n = 0) { init(n); }
	void init(int n) { t.resize(n + 1); rt = tot = 0; }

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

	void splits(int x, int sz, int &l, int &r) {
		if(x == 0) { l = r = 0; return; }
		if(sz <= t[LC].sz) { r = x; splits(LC, sz, l, LC); }
		else { l = x; splits(RC, sz-t[LC].sz-1, RC, r); }
		pushup(x);
	}
	void splitv(int x, int va, int &l, int &r) {
		if(x == 0) { l = r = 0; return; }
		if(va < t[x].va) { r = x; splitv(LC, va, l, LC); }
		else { l = x; splitv(RC, va, RC, r); }
		pushup(x);
	}
	int merge(int l, int r) {
		if(l == 0 || r == 0) return l + r;
		if(t[l].pos < t[r].pos) {
			t[l].rc = merge(t[l].rc, r);
			pushup(l);
			return l;
		} else {
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
};

void work() {
	int n;
	cin >> n;

	FHQ fhq(n);
	
	for(int i = 1; i <= n; i++) {
		int opt, x;
		cin >> opt >> x;
		if(opt == 1) {
			fhq.insert(x);
		} else if(opt == 2) {
			fhq.erase(x);
		} else if(opt == 3) {
			cout << fhq.getRank(x) << endl;
		} else if(opt == 4) {
			cout << fhq.getVa(x) << endl;
		} else if(opt == 5) {
			cout << fhq.getLower(x) << endl;
		} else if(opt == 6) {
			cout << fhq.getUpper(x) << endl;
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
