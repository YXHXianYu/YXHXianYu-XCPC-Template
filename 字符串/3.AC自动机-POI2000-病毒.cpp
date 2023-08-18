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
	const static int maxn = 3e4 + 10; // 字符串总长
	const static int M = 2;          // 字符集
	struct Node {
		int son[M], go[M], fail;
		int cnt, vis, instk;
	} t[maxn];
	int tot, rt, cur;

	int newNode() {
		tot++;
		memset(t[tot].son, 0, sizeof(t[tot].son));
		memset(t[tot].go, 0, sizeof(t[tot].go));
		t[tot].fail = t[tot].cnt = 0;
		return tot;
	}
	void clear() { tot = 0; rt = newNode(); }

	int insert(const string& s) { // 1-index
		int n = s.size() - 1;
		int p = rt;
		for(int j = 1; j <= n; j++) {
			int e = s[j] - '0';
			if(!t[p].son[e]) t[p].son[e] = newNode();
			p = t[p].son[e];
		}
		t[p].cnt = 1;
		return p;
	}

	int q[maxn + 1];
	int tl;
	void build() {
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
	}

	string ans() {
		for(int i = 1; i <= tot; i++) {
			int p = q[i];
			t[p].cnt |= t[t[p].fail].cnt;
		}

		function<bool(int)> dfs = [&](int x) {
			t[x].vis = 1;
			t[x].instk = 1;
			for(int j = 0; j < M; j++) {
				if(t[t[x].go[j]].cnt) continue;
				if(t[t[x].go[j]].vis) {
					if(t[t[x].go[j]].instk) return true;
				} else {
					if(dfs(t[x].go[j])) return true;
				}
			}
			t[x].instk = 0;
			return false;
		};

		int ans = dfs(rt);

		return (ans ? "TAK" : "NIE");
	}
};

ACAutomaton ac;

void work() {
	int n;
	cin >> n;

	ac.clear();

	for(int i = 1; i <= n; i++) {
		string s;
		cin >> s;
		ac.insert(" " + s);
	}

	ac.build();

	cout << ac.ans() << endl;
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
