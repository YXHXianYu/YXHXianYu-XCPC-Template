/**
 * Created by YXH_XianYu on 2023.9
 * Blog: https://yxhxianyu.fun
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'


void work() {
	int n, k;
	cin >> n >> k;

	string s;
	cin >> s;
	s = " " + s;

	vector<int> ans(n + 2);
	int ansN = 0;

	vector<int> b(k + 2);
	function<void(int, int, int)> dfs = [&](int x, int lst, int len) {
		if(x > k) {
			int lef = n - lst;
			if(abs(lef - len) > 1 || lef <= 0) return;

			b[k + 1] = n;

			vector<int> a(n + 2);
			int N = b[1];
			for(int j = b[1], id = 1; j >= 1; j--, id++) a[id] = s[j] - '0';
			for(int i = 2; i <= k + 1; i++) {
				N = max(N, b[i] - b[i - 1]);
				for(int j = b[i], id = 1; j > b[i - 1]; j--, id++) {
					a[id] += s[j] - '0';
					if(a[id] >= 10) {
						a[id + 1] += a[id] / 10;
						a[id] %= 10;
						if(id == N) N++;
					}
				}
			}
			for(int i = 1; i <= N; i++) {
				if(a[i] >= 10) {
					a[i + 1] += a[i] / 10;
					a[i] %= 10;
					if(i == N) N++;
				}
			}

			// cout << " - ";
			// for(int i = N; i >= 1; i--) cout << a[i]; cout << endl;

			auto check = [&]() {
				if(N != ansN) return N < ansN;
				for(int i = N; i >= 1; i--) {
					if(a[i] != ans[i]) {
						return a[i] < ans[i];
					}
				}
				return false;
			};

			if(ansN == 0 || check()) {
				ansN = N;
				ans = a;
			}

			return;
		}

		int lef = n - lst;
		int seg = (k + 1) - x + 1;
		if(lef < seg) return;

		if(x == 1) {
			for(int i = 1, lim = min(n, n / (k + 1) + 5); i <= lim; i++) {
				b[x] = lst + i;
				dfs(x + 1, b[x], i);
			}
		} else {
			if(len > 1) { b[x] = lst + len-1; dfs(x + 1, b[x], len-1); }

			b[x] = lst + len;
			dfs(x + 1, b[x], len);

			b[x] = lst + len+1;
			dfs(x + 1, b[x], len+1);
		}
	};

	dfs(1, 0, 0);

	for(int i = ansN; i >= 1; i--) cout << ans[i]; cout << endl;
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	// freopen("F.txt", "r", stdin);
	// freopen("F.out", "w", stdout);
	
	int t = 1;
	cin >> t;
	while(t--) {
		work();
	}
	
	return 0;
}