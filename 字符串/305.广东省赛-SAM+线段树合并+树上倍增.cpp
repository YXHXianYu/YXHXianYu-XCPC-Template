/**
 * 2022广东省赛I题：https://codeforces.com/gym/103650/problem/I
 * 原题：给一个字符串S和Q次询问，每次询问查询 一个最短的串使得S[l..r]是该串的Border，输出串长
 * 
 * 线段树合并，维护后缀自动机上每个结点的endpos集合
 * 线段树维护了endpos集合中相邻两个非0元素的最近距离
 * 树上倍增可以logn找到一个子串对应的节点
*/
#include<bits/stdc++.h>
using namespace std;

// 单点修改，区间最短相邻1，合并
const int INF = 1 << 30;
struct SGT {
	struct Node {
		int L, R, ans;
		Node(): L(0), R(0), ans(INF) {}
		Node(int _L, int _R, int _ans): L(_L), R(_R), ans(_ans) {}
		Node operator+(const Node& p) const {
			if(L == 0 && p.L == 0) return Node{0, 0, INF};
			if(L == 0) return p;
			if(p.L == 0) return *this;
			Node s;
			s.ans = min(p.L - R, min(ans, p.ans));
			s.L = L;
			s.R = p.R;
			return s;
		}
	};
	vector<Node> t;
	vector<int> lc, rc;
	int N;

	#define LC (lc[x])
	#define RC (rc[x])

	SGT(int n = 0) { init(n); }
	void init(int n) {
		t.resize(n);
		lc.resize(n);
		rc.resize(n);
		N = 0;
	}

	void pushup(int x) {
		t[x] = t[LC] + t[RC];
	}
	void modify(int &x, int l, int r, int pos) {
		if(!x) x = ++N;

		if(pos <= l && r <= pos) { t[x] = {l, l, INF}; return; }
		if(pos < l || r < pos) return;

		int mid = l + r >> 1;
		if(pos <= mid) modify(LC, l, mid, pos);
		else modify(RC, mid+1, r, pos);
		pushup(x);
	}
	// 线段树合并，每次不新建节点
	int merge(int x, int y) {
		if(!x || !y) return x + y;
		lc[x] = merge(lc[x], lc[y]);
		rc[x] = merge(rc[x], rc[y]);
		pushup(x);
		return x;
	}
	// 线段树合并，每次新建节点（空间复杂度需要开2倍）
	// int merge(int y, int z) {
	// 	if(!y || !z) return y + z;
	// 	int x = ++N;
	// 	lc[x] = merge(lc[y], lc[z]);
	// 	rc[x] = merge(rc[y], rc[z]);
	// 	pushup(x);
	// 	return x;
	// }
};

const int M = 26;
struct SAM {
	struct Node {
		int len, link;
		int nxt[M];
	};
	vector<Node> t;
	int N, lst;

	vector<int> endpos;
	vector<int> pos;

	SAM(int n = 0) { init(n); }
	void init(int n) {
		t.resize(2 * n + 1);
		N = 1;
		t[N] = t[0];
		lst = N;

		endpos.resize(2 * n + 1);
		pos.resize(2 * n + 1);
	}

	void add(int c, int id) {
		c -= 'a';
		int x = ++N;
		t[x] = t[0];
		t[x].len = t[lst].len + 1;

		endpos[N] = id;
		pos[id] = N;

		int p = lst;
		lst = x;
		for(; p && t[p].nxt[c] == 0; p = t[p].link) t[p].nxt[c] = x;

		if(!p) {
			t[x].link = 1;
		} else {
			int q = t[p].nxt[c];
			if(t[p].len + 1 == t[q].len) {
				t[x].link = q;
			} else {
				int cl = ++N;
				t[cl] = t[q];
				t[cl].len = t[p].len + 1;
				if(t[cl].len == t[x].len) lst = cl;
				for(; p && t[p].nxt[c] == q; p = t[p].link) t[p].nxt[c] = cl;
				t[q].link = t[x].link = cl;
			}
		}
	}

	void solve() {

		/* 1. build edges */
		vector<vector<int>> e(N + 1, vector<int>());
		for(int i = 2; i <= N; i++) e[t[i].link].push_back(i);

		/* 2. ST */
		vector<vector<int>> st(log2(N) + 1, vector<int>(N + 1));
		int lim = log2(N);
		for(int i = 1; i <= N; i++) st[0][i] = t[i].link;
		for(int i = 1; i <= lim; i++) {
			for(int j = 1; j <= N; j++) {
				st[i][j] = st[i - 1][st[i - 1][j]];
			}
		}

		auto getPos = [&](int L, int R) {
			int len = R - L + 1;
			int p = pos[R];
			for(int i = lim; i >= 0; i--) {
				if(t[st[i][p]].len >= len) {
					p = st[i][p];
				}
			}
			return p;
		};

		/* 3. endpos & solve */
		int Q;
		cin >> Q;

		vector<int> ans(Q + 1);
		vector<vector<int>> q(N + 1, vector<int>());
		for(int i = 1; i <= Q; i++) {
			int L, R;
			cin >> L >> R;
			int p = getPos(L, R);
			ans[i] = R - L + 1;
			q[p].push_back(i);
		}

		vector<int> rt(N + 1);
		SGT sgt(N * (log2(N) + 2) + 10);

		function<void(int)> dfs2 = [&](int x) {
			if(endpos[x]) sgt.modify(rt[x], 1, N, endpos[x]);
			for(auto y: e[x]) {
				dfs2(y);
				rt[x] = sgt.merge(rt[x], rt[y]);
			}
			int v = sgt.t[rt[x]].ans;
			for(auto i: q[x]) {
				ans[i] = (v == INF ? -1 : ans[i] + v);
			}
		};
		dfs2(1);

		/* 5. output */
		for(int i = 1; i <= Q; i++) cout << ans[i] << endl;
	}
};

void work() {
	string s;
	cin >> s;
	int n = s.size();
	s = " " + s;

	SAM sam(n);
	for(int i = 1; i <= n; i++) sam.add(s[i], i);
	sam.solve();
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