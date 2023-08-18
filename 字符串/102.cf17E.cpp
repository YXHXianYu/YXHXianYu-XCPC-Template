#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;


void work() {
	int n;
	cin >> n;

	string s;
	cin >> s;
	s = " " + s;

	int N = 2 * n + 1;
	string t(N + 2, 0);
	t[1] = '#';
	for(int i = 1; i <= n; i++) {
		t[i << 1] = s[i];
		t[i << 1 | 1] = '#';
	}

	vector<int> f(N + 1);
	int md = 0, r = 0, j, k;
	for(int i = 1; i <= N; i++) {
		if(i <= r) f[i] = min(r - i, f[(md << 1) - i]);
		while(i-f[i]-1 >= 1 && i+f[i]+1 <= N && t[i-f[i]-1] == t[i+f[i]+1]) f[i]++;
		if(i + f[i] - 1 > r) md = i, r = i + f[i] - 1;
	}

	vector<int> i1(N + 1);
	for(int i = 0; i <= N; i++) i1[i] = i >> 1;

	vector<int> g(n + 2); // right end
	vector<int> h(n + 2); // left end
	for(int i = 1; i <= N; i++) {
		int L, L1, R1, R;
		if(t[i] == '#') {
			// #a#b#b#a#
			// ----4----
			// i=5 f[i]=4 L=1 L1=2 R1=3 R=4
			L = i1[i] - i1[f[i]] + 1;
			L1 = i1[i];
			R1 = i1[i] + 1;
			R = i1[i] + i1[f[i]];
		} else {
			// #a#b#c#b#a#
			// -----6-----
			// i=6 f[i]=5 L=1 L1=3 R1=3 R=5
			L = i1[i] - i1[f[i]];
			L1 = R1 = i1[i];
			R = i1[i] + i1[f[i]];
		}
		h[L - 1]--;
		h[L1]++;
		g[R1]++;
		g[R + 1]--;
	}

	const int MOD = 51123987;

	for(int i = 2; i <= n; i++) g[i] = (g[i] + g[i - 1]) % MOD;
	for(int i = n - 1; i >= 1; i--) h[i] = (h[i] + h[i + 1]) % MOD;
	for(int i = n - 1; i >= 1; i--) h[i] = (h[i] + h[i + 1]) % MOD;

	int ans1 = 0;
	for(int i = 1; i <= N; i++) ans1 = (ans1 + (f[i] + 1) / 2) % MOD;
	ans1 = ans1 * (ans1 - 1) / 2 % MOD;

	int ans2 = 0;
	for(int i = 1; i < n; i++) {
		ans2 = (ans2 + g[i] * h[i + 1] % MOD) % MOD;
	}

	int ans = (ans1 - ans2 + MOD) % MOD;
	
	// for(int i = 1; i <= N; i++) cout << t[i] << " "; cout << endl;
	// for(int i = 1; i <= N; i++) cout << f[i] << " "; cout << endl;

	// cout << ans1 << ", " << ans2 << ", " << ans << endl;

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
