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
	const static int maxn = 1e6 + 10; // 字符串总长
	const static int M = 26;          // 字符集
	struct Node {
		int son[M], go[M], fail, ffail;
		int mark;
		multiset<int> v;
	} t[maxn];
	int tot, rt, cur;

	int newNode() {
		tot++;
		return tot;
	}
	void init() { tot = 0; rt = newNode(); }

	int insert(const string& s) { // 1-index
		int n = s.size() - 1;
		int p = rt;
		for(int j = 1; j <= n; j++) {
			int e = s[j] - 'a';
			if(!t[p].son[e]) t[p].son[e] = newNode();
			p = t[p].son[e];
		}
		t[p].mark = 1;
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
		for(int i = 1; i <= tl; i++) {
			int p = q[i];
			if(t[t[p].fail].mark == 1) t[p].ffail = t[p].fail;
			else t[p].ffail = t[t[p].fail].ffail;
		}
	}

	int query(const string& s) {
		int n = s.size() - 1;

		int p = rt;
		int ans = -1;
		for(int i = 1; i <= n; i++) {
			int e = s[i] - 'a';
			p = t[p].go[e];
			for(int j = p; j; j = t[j].ffail) {
				if(t[j].mark) {
					ans = max(ans, *t[j].v.rbegin());
				}
			}
		}
		
		return ans;
	}

};

ACAutomaton ac; // 多测记得清空

void work() {
	int n, q;
	cin >> n >> q;

	ac.init();

	vector<int> d(n + 1);
	vector<int> v(n + 1);
	vector<string> s(n + 1);

	for(int i = 1; i <= n; i++) {
		cin >> s[i];
		d[i] = ac.insert(" " + s[i]);
		ac.t[d[i]].v.insert(v[i]);
	}

	ac.build();

	for(int i = 1;  i <= q; i++) {
		int opt;
		cin >> opt;
		if(opt == 1) {
			int i, x;
			cin >> i >> x;
			auto& ms = ac.t[d[i]].v;
			ms.erase(ms.lower_bound(v[i]));
			v[i] = x;
			ms.insert(v[i]);
		} else if(opt == 2) {
			string t;
			cin >> t;
			cout << ac.query(" " + t) << endl;
		} else assert(false);
	}
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
