#include<bits/stdc++.h>
using namespace std;
// #define int long long


struct SAM {
	static const int M = 26;
	struct Node {
		int len, link, nxt[M];
	};
	vector<Node> t;
	int N, lst;

	Node& operator[] (int i) { return t[i]; }

	SAM(int n = 0) { init(n); }
	void init(int n) {
		t.resize(2 * n + 1); // 2n-1 Points, 3n-4 Edges
		f.resize(2 * n + 1);
		N = 0;
		t[++N].len = 0;
		t[N].link = 0;
		memset(t[N].nxt, 0, sizeof(t[N].nxt));
		lst = N;
	}

	vector<int> f;

	void add(char c) {
		c -= 'a';
		if(t[lst].nxt[c] && t[lst].len + 1 == t[t[lst].nxt[c]].len) { // for exSAM
			lst = t[lst].nxt[c];
			return;
		}
		int x = ++N;
		t[N].len = t[lst].len + 1;
		t[N].link = 0;
		memset(t[N].nxt, 0, sizeof(t[N].nxt));

		f[x] = 1;

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

	long long solve() {
		vector<int> a(N + 1);
		for(int i = 1; i <= N; i++) a[i] = i;
		sort(a.begin() + 1, a.begin() + N + 1, [&](int a, int b) {
			return t[a].len < t[b].len;
		});

		long long ans = 0;
		for(int j = N; j >= 2; j--) {
			int i = a[j];
			if(f[i] >= 2) ans = max(ans, 1ll * f[i] * t[i].len);
			f[t[i].link] += f[i];
		}
		return ans;
	}
};

void work() {
	string s;
	cin >> s;
	int n = s.size();
	s = " " + s;

	SAM sam(n);
	for(int i = 1; i <= n; i++) sam.add(s[i]);

	cout << sam.solve() << endl;
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

