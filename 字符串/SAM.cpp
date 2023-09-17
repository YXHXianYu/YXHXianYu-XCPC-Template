#include<bits/stdc++.h>
using namespace std;

struct SAM {
	static const int M = 26;
	struct Node {
		int len, link;
		int nxt[M];
	};
	vector<Node> t;
	int N, lst;

	Node& operator[] (int i) { return t[i]; }

	SAM(int n = 0) { init(n); }
	void init(int n) {
		t.resize(2 * n + 1); // 2n-1 Points, 3n-4 Edges
		N = 0;
		t[++N].len = 0;
		t[N].link = 0;
		memset(t[N].nxt, 0, sizeof(t[N].nxt));
		lst = N;
	}

	void add(char c) {
		c -= 'a';
		if(t[lst].nxt[c] && t[t[lst].nxt[c]].len == t[lst].len + 1) { // for exSAM
			lst = t[lst].nxt[c];
			return;
		}

		int x = ++N;
		t[N].len = t[lst].len + 1;
		t[N].link = 0;
		memset(t[N].nxt, 0, sizeof(t[N].nxt));

		int p = lst;
		lst = x;
		for(; p && !t[p].nxt[c]; p = t[p].link) t[p].nxt[c] = x;
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
};