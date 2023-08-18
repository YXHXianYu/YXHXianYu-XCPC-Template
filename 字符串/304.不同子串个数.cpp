#include<bits/stdc++.h>
using namespace std;
// #define int long long
typedef long long LLI;
#define endl '\n'

struct SAM {
	static const int M = 26;
	struct Node {
		int len, link;
		map<int, int> nxt;
	};
	vector<Node> t;
	int N, lst;

	Node& operator[] (int i) { return t[i]; }

	SAM(int n = 0) { init(n); }
	void init(int n) {
		t.resize(2 * n + 1); // 2n-1 Points, 3n-4 Edges
		N = 1;
		lst = N;
	}

	LLI ans = 0;

	void add(int c) {
		if(t[lst].nxt[c] && t[lst].len + 1 == t[t[lst].nxt[c]].len) { // for exSAM
			lst = t[lst].nxt[c];
			return;
		}

		int x = ++N;
		t[N].len = t[lst].len + 1;

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

				ans -= t[q].len - t[t[q].link].len;

				t[q].link = t[x].link = cl;

				ans += t[q].len - t[t[q].link].len;
				ans += t[cl].len - t[t[cl].link].len;

			}
		}

		ans += t[x].len - t[t[x].link].len;
	}
};

void work() {
	int n;
	cin >> n;

	vector<int> a(n + 1);
	for(int i = 1; i <= n; i++) cin >> a[i];

	SAM sam(n);

	for(int i = 1; i <= n; i++) {
		sam.add(a[i]);
		cout << sam.ans << endl;
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
