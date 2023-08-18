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
void work() {
	int n;
	cin >> n;

	string s;
	cin >> s;
	s = " " + s;

	vector<int> sa, rk, ht;
	buildSA(s, sa, rk, ht); // 1-index

	vector<int> a(n + 1);
	for(int i = 1; i <= n; i++) cin >> a[i];

	vector<int> f(n + 1);
	vector<long long> mx(n + 1), mn(n + 1), sz(n + 1);
	vector<vector<int>> pos(n + 1, vector<int>());
	for(int i = 1; i <= n; i++) {
		f[i] = i;
		mx[i] = mn[i] = a[sa[i]];
		sz[i] = 1;
	}
	for(int i = 1; i <= n; i++) {
		pos[ht[i]].push_back(i);
	}
	function<int(int)> find = [&](int x) {
		return f[x] == x ? x : f[x] = find(f[x]);
	};

	const long long INF = 1LL << 60;
	vector<long long> ansSum(n + 1);
	vector<long long> ansVa(n + 1, -INF);
	for(int i = n - 1; i >= 0; i--) {
		ansSum[i] = ansSum[i + 1];
		ansVa[i] = ansVa[i + 1];
		for(auto p: pos[i]) {
			int u = find(p - 1), v = find(p);
			ansSum[i] += sz[u] * sz[v];
			ansVa[i] = max(ansVa[i], max(mx[u] * mx[v], mn[u] * mn[v]));
			f[v] = u;
			sz[u] += sz[v];
			mx[u] = max(mx[u], mx[v]);
			mn[u] = min(mn[u], mn[v]);
		}
	}
	for(int i = 0; i < n; i++) {
		cout << ansSum[i] << " " << (ansVa[i] == -INF ? 0 : ansVa[i]) << endl;
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
