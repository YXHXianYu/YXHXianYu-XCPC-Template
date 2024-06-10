/*
JSOI2007 文本生成器
AC自动机+DP：AC自动机本质上是在维护当前dp状态是否出现了特定子串；常用于解决子串问题+计数dp
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;

struct ACAutomaton { // 默认无多测
	const static int maxn = 1e6 + 10; // 字符串总长
	const static int maxm = 26;       // 字符集
	struct Node {
		int son[maxm], go[maxm], fail;
		int cnt;
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
			int e = s[j] - 'A';
			if(!t[p].son[e]) t[p].son[e] = newNode();
			p = t[p].son[e];
		}
		t[p].cnt |= 1;
		return p;
	}

	int q[maxn];
	int tl;
	void build() {
		tl = 0;
		q[++tl] = rt;
		for(int i = 1; i <= tl; i++) {
			int p = q[i];
			for(int j = 0; j < maxm; j++) {
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

	int getAns(int n) { // 1-index
		for(int i = 1; i <= tl; i++) {
			t[q[i]].cnt |= t[t[q[i]].fail].cnt;
		}

		const int MOD = 1e4 + 7;
		vector<vector<array<int, 2>>> dp(n + 1, vector<array<int, 2>>(tot + 1));

		auto upd = [&](int &a, int b) {
			// a = (a + b) % MOD; // too slow ?
			a += b;
			if(a >= MOD) a -= MOD;
		};

		dp[0][1][0] = 1;
		for(int i = 0; i < n; i++) {
			for(int j = 1; j <= tot; j++) {
				for(int k = 0; k <= 1; k++) {
					if(dp[i][j][k] == 0) continue;
					for(int p = 0; p < maxm; p++) {
						upd(dp[i + 1][t[j].go[p]][k | t[t[j].go[p]].cnt],
							dp[i][j][k]);
					}
				}
			}
		}

		int ans = 0;
		for(int i = 1; i <= tot; i++) upd(ans, dp[n][i][1]);
		return ans;
	}
};

ACAutomaton ac;

void work() {
	int n, m;
	cin >> n >> m;

	ac.clear();

	vector<int> d(n + 1);
	vector<string> s(n + 1);
	string t;

	for(int i = 1; i <= n; i++) {
		cin >> s[i];
		d[i] = ac.insert(" " + s[i]);
	}

	ac.build();

	cout << ac.getAns(m) << endl;
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
