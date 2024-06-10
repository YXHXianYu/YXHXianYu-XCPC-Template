#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'

// all vec is 1-index; ht[2..n]
void buildSA(string& s, vector<int>& sa, vector<int>& rk, vector<int>& ht, int M = 128) {
	int n = s.size() - 1;
	s.push_back(0);
	sa = rk = ht = vector<int>(n + 1);
	vector<int> x(n + 1), y(n + 1), c(max(n, M) + 1);
	for(int i = 1; i <= n; i++) c[x[i] = s[i]]++;
	for(int i = 2; i <= M; i++) c[i] += c[i - 1];
	for(int i = n; i >= 1; i--) sa[c[x[i]]--] = i;
	for(int k = 1; k <= n; k <<= 1) {
		int p = 0;
		for(int i = n - k + 1; i <= n; i++) y[++p] = i;
		for(int i = 1; i <= n; i++) if(sa[i] > k) y[++p] = sa[i] - k;
		for(int i = 1; i <= M; i++) c[i] = 0;
		for(int i = 1; i <= n; i++) c[x[i]]++;
		for(int i = 2; i <= M; i++) c[i] += c[i - 1];
		for(int i = n; i >= 1; i--) sa[c[x[y[i]]]--] = y[i];
		swap(x, y);
		p = 1; x[sa[1]] = 1;
		for(int i = 2; i <= n; i++)
			x[sa[i]] = y[sa[i-1]] == y[sa[i]] && y[sa[i-1]+k] == y[sa[i]+k] ? p : ++p;
		if(p == n) break;
		M = p;
	}
	for(int i = 1; i <= n; i++) rk[sa[i]] = i;
	for(int i = 1, k = 0; i <= n; i++) {
		k = max(k - 1, 0ll);
		if(rk[i] == 1) continue;
		int j = sa[rk[i] - 1];
		while(s[i + k] == s[j + k]) k++;
		ht[rk[i]] = k;
	}
}

// n=1e5时，倍增241ms，SAIS 178ms (dls-oj)
// n=1e6时，SAIS 0.3s (reference)
void work() {
	string s;
	cin >> s;
	int n = s.size();
	s = " " + s;

	vector<int> sa, rk, ht;
	buildSA(s, sa, rk, ht); // 1-index

	int ans = (n + 1) * n / 2 * (n - 1);

	for(int i = 1; i < n; i++) ht[i] = ht[i + 1];
	n--;

	// Cartesian Tree (小根)
	vector<int> L(n + 1), R(n + 1), stk(n + 2);
	int rt = 0;
	for(int i = 1; i <= n; i++) {
		int lst = 0;
		while(stk[0] && ht[stk[stk[0]]] > ht[i]) lst = stk[stk[0]--];
		if(stk[0]) R[stk[stk[0]]] = i;
		else rt = i;
		L[i] = lst;
		stk[++stk[0]] = i;
	}
	function<void(int, int, int)> dfs = [&](int x, int l, int r) {
		ans -= 2 * ht[x] * (r - x + 1) * (x - l + 1);
		if(L[x]) dfs(L[x], l, x - 1);
		if(R[x]) dfs(R[x], x + 1, r);
	};
	dfs(rt, 1, n);

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
