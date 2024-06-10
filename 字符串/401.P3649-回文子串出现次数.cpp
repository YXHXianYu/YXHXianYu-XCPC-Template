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
		int fail, len, num, fa;
		int son[26];
	};
	vector<Node> t;
	int N = 0;

	PAM(int n) { 
		t.resize(n + 2);
		t[0].fail = 1;
		t[1].len = -1;
		N = 1;
	}

	int build(string& s) {
		int n = s.size() - 1;

		auto getfail = [&](int x, int i) {
			while(s[i - t[x].len - 1] != s[i]) x = t[x].fail;
			return x;
		};

		int lst = 0;
		vector<int> f(n + 2); // f[i]: 第i个点的出现次数
		for(int i = 1; i <= n; i++) {
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
			f[lst] += 1;
		}

		vector<int> id(N);
		for(int i = 2; i <= N; i++) id[i - 1] = i;
		sort(id.begin() + 1, id.end(), [&](int i, int j) {
			return t[i].len > t[j].len;
		});
		int ans = 0;
		for(int i = 1; i < N; i++) {
			int x = id[i];
			ans = max(ans, f[x] * t[x].len);
			f[t[x].fail] += f[x]; // 类似后缀自动机，往fail树父亲累计贡献
		}
		return ans;
	}
};

void work() {
	string s;
	cin >> s;
	int n = s.size();
	s = " " + s;

	PAM pam(n);
	int ans = pam.build(s);

	cout << ans << endl;
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