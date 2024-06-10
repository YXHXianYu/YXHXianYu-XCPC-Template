/**
 * Created by YXH_XianYu in 2023.10
 * Blog: https://yxhxianyu.fun
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'

/**
 * 设A是任意一个回文串，则形如AA的串，就叫做双回文串
 * 统计一个串的所有前缀的双回文子串个数
*/
struct PAM {
	struct Node {
		int fail, len, fa, sum;
		int son[26];
		int cnt = 0;
	};
	vector<Node> t;
	vector<vector<int>> fa;
	int lim;
	int N = 0;

	PAM(int n) {
		lim = log2(n + 1);
		t.resize(n + 2);
		fa.resize(lim + 1, vector<int>(n + 2));
		t[0].fail = 1;
		t[1].len = -1;
		N = 1;
	}

	void solve(string& s) {
		int n = s.size() - 1;

		auto getfail = [&](int x, int i) {
			while(s[i - t[x].len - 1] != s[i]) x = t[x].fail;
			return x;
		};

		int lst = 0;
		int ans = 0;
		for(int i = 1; i <= n; i++) {
			int e = s[i] - 'a';
			int x = getfail(lst, i);
			if(!t[x].son[e]) {
				t[++N].fail = t[getfail(t[x].fail, i)].son[e];
				t[x].son[e] = N;
				t[N].fa = x;

				// 树上倍增
				fa[0][N] = t[N].fail;
				for(int k = 1; k <= lim; k++) fa[k][N] = fa[k - 1][fa[k - 1][N]];

				t[N].len = t[x].len + 2;
			}
			lst = t[x].son[e];
			t[lst].cnt = t[t[lst].fail].cnt;

			// 找fail树祖先中是否存在长度为当前回文串一半的节点
			if(~t[lst].len & 1) {
				int y = lst;
				int tar = t[lst].len / 2;
				for(int k = lim; k >= 0; k--) {
					if(t[fa[k][y]].len == tar) {
						y = fa[k][y];
						break;
					} else if(t[fa[k][y]].len > tar) {
						y = fa[k][y];
					}
				}
				if(tar > 0 && t[y].len == tar) {
					t[lst].cnt += 1;
				}
			}
			
			ans += t[lst].cnt;
			cout << ans << " ";
		}
		cout << endl;
	}
};


void work() {
	string s;
	cin >> s;
	int n = s.size();
	s = " " + s;

	PAM pam(n);
	pam.solve(s);
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int t = 1;
	cin >> t;
	while(t--) {
		work();
	}
	
	return 0;
}