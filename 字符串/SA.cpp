#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'

// all vec is 1-index; ht[2..n]
void buildSA(string& s, vector<int>& sa, vector<int>& rk, vector<int>& ht, int M = 128) {
	int n = s.size() - 1;
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
	s.push_back(0);
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
// n=3e5，define int long long 影响 < 100ms
void work() {
	string s;
	cin >> s;
	int n = s.size();
	s = " " + s;

	vector<int> sa, rk, ht;
	buildSA(s, sa, rk, ht); // 1-index

	// ST-LCP 按需
	int lim = __lg(n);
	vector<vector<int>> st(lim + 1, vector<int>(n + 1));
	for(int i = 1; i <= n; i++) st[0][i] = ht[i];
	for(int k = 1; k <= lim; k++) {
		int lim2 = n - (1 << k) + 1;
		for(int i = 1; i <= n; i++) {
			st[k][i] = min(st[k-1][i], st[k-1][i+(1<<k-1)]);
		}
	}
	auto query = [&](int L, int R) {
		int k = __lg(R - L + 1);
		return min(st[k][L], st[k][R-(1<<k)+1]);
	};
	auto LCP = [&](int u, int v) {
		if(u == v) return n - u + 1;
		if(rk[u] > rk[v]) swap(u, v);
		// RMQ(ht, rk[u] + 1, rk[v])
		return query(rk[u] + 1, rk[v]);
	};

	// input: abaabaaabaaaab
	// output: 10 11 6 12 7 3 13 8 4 1 14 9 5 2
	//         3 4 2 3 6 1 2 5 4 0 1 4 3
	for(int i = 1; i <= n; i++) cout << sa[i] << " "; cout << endl;
	// for(int i = 2; i <= n; i++) cout << ht[i] << " "; cout << endl;
	// for(int i = 2; i <= n; i++) cout << LCP(sa[i-1], sa[i]) << " "; cout << endl;
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
