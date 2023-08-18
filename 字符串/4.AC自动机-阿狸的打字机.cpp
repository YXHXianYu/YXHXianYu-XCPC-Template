#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;

/**
 * n个模式串si 和 一个文本串t，求每个模式串的在文本串里的出现次数
 * ① 建Trie
 * ② 从根开始Bfs
*/

struct ACAutomaton { // 默认无多测
	const static int maxn = 2e5 + 10; // 字符串总长
	const static int M = 26;          // 字符集
	struct Node {
		int son[M], go[M], fail;
		int cnt;
		
		vector<array<int, 2>> q;
	} t[maxn];
	int tot, rt, cur;

	Node& operator[] (int i) {
		return t[i];
	}

	int newNode() {
		tot++;
		return tot;
	}
	void clear() { tot = 0; rt = newNode(); }

	int q[maxn + 1];
	int tl;
	void solve(const string& s) {
		int n = s.size() - 1;

		vector<int> a(n + 1);
		vector<int> fa(n + 1);

		int p = rt;
		for(int i = 1; i <= n; i++) {
			if(s[i] == 'P') {
				a[++a[0]] = p;
			} else if(s[i] == 'B') {
				p = fa[p];
			} else if('a' <= s[i] && s[i] <= 'z') {
				int e = s[i] - 'a';
				if(t[p].son[e] == 0) t[p].son[e] = newNode(), fa[t[p].son[e]] = p;
				p = t[p].son[e];
			} else assert(false);
		}

		tl = 0;
		q[++tl] = rt;
		for(int i = 1; i <= tl; i++) {
			int p = q[i];
			for(int j = 0; j < M; j++) {
				if(t[p].son[j]) {
					t[p].go[j] = t[p].son[j];
					t[t[p].son[j]].fail = (p == rt ? rt : t[t[p].fail].go[j]);
					q[++tl] = t[p].son[j];
				} else {
					t[p].go[j] = (p == rt ? rt : t[t[p].fail].go[j]);
				}
			}
		}

		vector<vector<int>> e(tot + 1, vector<int>());

		for(int i = 1; i <= tl; i++) {
			int p = q[i];
			e[t[p].fail].push_back(p);
		}

		vector<int> dfn(tot + 1), dfnR(tot + 1);

		function<void(int x)> dfs1 = [&](int x) {
			dfn[x] = ++dfn[0];
			for(auto y: e[x]) {
				dfs1(y);
			}
			dfnR[x] = dfn[0];
		};

		dfs1(rt);

		// for(int i = 1; i <= tot; i++) cout << i << ": " << dfn[i] << ", " << dfnR[i] << endl;

		int q;
		cin >> q;
		for(int i = 1; i <= q; i++) {
			int x, y;
			cin >> x >> y;
			t[a[y]].q.push_back({a[x], i});
		}

		// bit
		vector<int> bit(tot + 1);
		#define lowbit(x) (x&-x)
		auto add = [&](int x, int v) {
			for(; x <= tot; x += lowbit(x)) bit[x] += v;
		};
		auto query = [&](int x) {
			int ans = 0; for(; x; x -= lowbit(x)) ans += bit[x]; return ans;
		};

		// solve
		vector<int> ans(q + 1);
		function<void(int)> dfs2 = [&](int x) {
			add(dfn[x], 1);
			for(auto [s, id]: t[x].q) {
				ans[id] = query(dfnR[s]) - query(dfn[s] - 1);
			}
			// trie sons
			for(int j = 0; j < M; j++) if(t[x].son[j]) {
				dfs2(t[x].son[j]);
			}
			add(dfn[x], -1);
		};
		dfs2(rt);

		#define endl '\n'
		// output
		for(int i = 1; i <= q; i++) cout << ans[i] << endl;
	}


};

ACAutomaton ac; // 多测记得清空

void work() {
	string s;
	cin >> s;
	ac.clear();
	ac.solve(" " + s);
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int t = 1;
	while(t--) {
		work();
	}
	
	return 0;
}
