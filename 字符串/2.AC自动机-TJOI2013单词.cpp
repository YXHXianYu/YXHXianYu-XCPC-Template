#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;

/**
 * ① 建Trie
 * ② 从根开始Bfs
*/

struct ACAutomaton { // 默认无多测
	const static int N = 1e6 + 10; // 字符串总长
	const static int M = 26;       // 字符集
	struct Node {
		int son[M], go[M], fail;
		int cnt;
	} t[N];
	int tot, rt, cur;

	int newNode() { return ++tot; }
	void clear() { tot = 0; rt = newNode(); }

	int insert(const string& s) { // 1-index
		int n = s.size() - 1;
		int p = rt;
		for(int j = 1; j <= n; j++) {
			int e = s[j] - 'a';
			if(!t[p].son[e]) t[p].son[e] = newNode();
			p = t[p].son[e];
		}
		return p;
	}

	int q[N + 1];
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

	/* TJOI 单词 特异 */
	void getAns(const string& s) {
		int p = rt;
		for(auto ch: s) {
			p = (ch == 0 ? rt : t[p].go[ch-'a']);
			t[p].cnt += 1;
		}
		for(int i = tl; i >= 1; i--) {
			int p = q[i];
			t[t[p].fail].cnt += t[p].cnt;
		}
	}
};

ACAutomaton ac;

void work() {
	int n;
	cin >> n;

	ac.clear();

	vector<int> d(n + 1);
	string t;

	for(int i = 1; i <= n; i++) {
		string s;
		cin >> s;
		d[i] = ac.insert(" " + s);
		t = t + s;
		t.push_back(0);
	}

	ac.build();

	ac.getAns(t);

	for(int i = 1; i <= n; i++) {
		cout << ac.t[d[i]].cnt << endl;
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
