/**
 * Created by YXH_XianYu in 2023.10
 * Blog: https://yxhxianyu.fun
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'

struct PAM {
	struct Node {
		int fail, len, num, fa; // num: 该回文串的后缀的回文串个数
		int son[26];
	};
	vector<Node> t;
	vector<int> f; // f[i]: 以第i个字符结尾的回文串个数
	int N;

	PAM(int n = 0) {
		t.resize(n + 2);
		f.resize(n + 2);
		t[0].fail = 1;
		t[1].len = -1;
		N = 1;
	}

	void build(string& s) {
		int n = s.size() - 1;

		auto getfail = [&](int x, int i) {
			while(s[i - t[x].len - 1] != s[i]) x = t[x].fail;
			return x;
		};

		int lst = 0;
		for(int i = 1; i <= n; i++) {
			/* For LuoguP5496 */ if(i >= 2) s[i] = (s[i] + f[i - 1] - 'a') % 26 + 'a';
			int e = s[i] - 'a';
			int x = getfail(lst, i);
			if(!t[x].son[e]) {
				t[++N].fail = t[getfail(t[x].fail, i)].son[e];
				t[x].son[e] = N;
				t[N].fa = x;
				t[N].len = t[x].len + 2;
				t[N].num = t[t[N].fail].num + 1;
			}
			lst = t[x].son[e];
			f[i] = t[lst].num;
		}
	}

};


void work() {
	string s;
	cin >> s;
	int n = s.size();
	s = " " + s;

	PAM pam(n);
	pam.build(s);

	for(int i = 1; i <= n; i++) cout << pam.f[i] << " ";
	cout << endl;
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