#include<bits/stdc++.h>
using namespace std;
// #define int long long

struct ACAutomaton { // 默认无多测
	const static int maxn = 1e6 + 10; // 字符串总长
	const static int M = 26;          // 字符集
	struct Node {
		int son[M], go[M], fail;
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
	void init() { tot = 0; rt = newNode(); }

    int f[maxn + 1];
    int g[maxn + 1];

	int insert(const string& s) { // 0-index
		int n = s.size();
		int p = rt;
		for(int j = 0; j < n; j++) {
			int e = s[j] - 'a';
			if(!t[p].son[e]) t[p].son[e] = newNode();
			p = t[p].son[e];
		}
        g[p] += 1;
        f[p] += n - 1;
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
                    g[t[p].son[j]] += g[t[t[p].son[j]].fail];
                    f[t[p].son[j]] += f[t[t[p].son[j]].fail];
				} else {
					t[p].go[j] = (p == rt ? rt : t[t[p].fail].go[j]);
				}
			}
		}
	}

	int query(const string& s) { // 1-index
        const int MOD = 1e9 + 7;
		int n = s.size();
		int p = rt;
        long long cnt = 0;
		for(int i = 0; i < n; i++) {
			int e = s[i] - 'a';
			p = t[p].go[e];

            if(g[p] > 0)
                cnt = (cnt + 1LL * (n - i) * ((1LL * (i + 1) * g[p] % MOD - f[p] % MOD + MOD) % MOD) % MOD) % MOD;
		}

        return cnt;
	}
};

ACAutomaton ac; // 多测记得清空

void work() {
    int n, m;
    cin >> n >> m;

    ac.init();

    for(int i = 0; i < n; i++) {
        string s;
        cin >> s;

        ac.insert(s);
    }
    ac.build();

    for(int i = 0; i < m; i++) {
        string s;
        cin >> s;

        cout << ac.query(s) << '\n';
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