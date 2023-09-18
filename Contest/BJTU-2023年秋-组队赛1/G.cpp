/**
 * Created by YXH_XianYu on 2023.9
 * Blog: https://yxhxianyu.fun
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'

struct SAM {
	static const int M = 26;
	struct Node {
		int len, link, nxt[M];
	};
	vector<Node> t;
	int N, lst;

	vector<int> f;

	SAM(int n = 0) { init(n); }
	void init(int n) {
		t.resize(2 * n + 1);
		f.resize(2 * n + 1);
		N = 0;
		t[++N].len = 0;
		t[N].link = 0;
		memset(t[N].nxt, 0, sizeof(t[N].nxt));
		lst = N;
	}

	void add(char c) {
		c -= 'a';
		if(t[lst].nxt[c] && t[lst].len + 1 == t[t[lst].nxt[c]].len) {
			lst = t[lst].nxt[c];
			return;
		}

		int x = ++N;
		t[N].len = t[lst].len + 1;
		t[N].link = 0;
		memset(t[N].nxt, 0, sizeof(t[N].nxt));

		f[x] += 1;

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

	int solve() {
		const int MOD = 1e9 + 7;
		auto upd = [&](int& a, int b) {
			a += b;
			if(a >= MOD) a -= MOD;
		};
		auto Pow = [&](int a, int n) {
			int ans = 1;
			while(n) {
				if(n & 1) ans = ans * a % MOD;
				a = a * a % MOD;
				n >>= 1;
			}
			return ans;
		};
		auto Inv = [&](int a) {
			return Pow(a, MOD - 2);
		};

		vector<int> p(26), pinv(26);
		for(int i = 0; i <= 25; i++) cin >> p[i];
		
		int sum = 0;
		for(int i = 0; i <= 25; i++) upd(sum, p[i]);
		int suminv = Inv(sum);
		for(int i = 0; i <= 25; i++) p[i] = p[i] * suminv % MOD;
		for(int i = 0; i <= 25; i++) pinv[i] = Inv(p[i]);

		vector<int> a(N + 1);
		for(int i = 1; i <= N; i++) a[i] = i;
		sort(a.begin() + 1, a.end(), [&](int a, int b) {
			return t[a].len < t[b].len;
		});

		vector<int> F(N + 1);
		F[1] = 1;
		for(int i = 1; i <= N; i++) {
			int x = a[i];
			for(int j = 0; j < M; j++) {
				if(t[x].nxt[j] == 0) continue;
				upd(F[t[x].nxt[j]], F[x] * pinv[j] % MOD);
			}
		}

		auto calc = [&](int x) {
			return (1 + x) * x / 2 % MOD;
		};

		int ans = 0;
		for(int j = N; j >= 2; j--) {
			int i = a[j];
			upd(ans, calc(f[i]) * F[i] % MOD);
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