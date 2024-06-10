#include<bits/stdc++.h>
using namespace std;
// #define int long long
#define endl '\n'

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
		k = max(k - 1, 0);
		if(rk[i] == 1) continue;
		int j = sa[rk[i] - 1];
		while(s[i + k] == s[j + k]) k++;
		ht[rk[i]] = k;
	}
}

void work() {
	string s;
	cin >> s;
	int n = s.size();
	s = " " + s;

	vector<int> sa, rk, ht;
	buildSA(s, sa, rk, ht);

	int T, k;
	cin >> T >> k;

	if(T == 0) {
		int i, v;
		for(i = 1; i <= n; i++) {
			v = n - sa[i] + 1 - ht[i];
			if(k <= v) break;
			k -= v;
		}
		if(i > n) {
			cout << -1 << endl;
		} else {
			for(int j = sa[i], p = 1; p <= k + ht[i]; j++, p++) cout << s[j]; cout << endl;
		}
	} else {
		vector<int> f(n + 1);
		for(int i = 1; i <= n; i++) f[i] = i;
		function<int(int)> find = [&](int x) {
			return f[x] == x ? x : f[x] = find(f[x]);
		};
		vector<int> sz(n + 1), len(n + 1);
		vector<vector<int>> pos(n + 1, vector<int>());
		vector<vector<array<int, 3>>> seg(n + 1, vector<array<int, 3>>());
		for(int i = 1; i <= n; i++) sz[i] = 1;
		for(int i = 2; i <= n; i++) pos[ht[i]].push_back(i);
		for(int i = 1; i <= n; i++) len[i] = n - sa[i] + 1;
		// 将相同子段由下至上合并
		for(int i = n - 1; i >= 0; i--) {
			for(auto p: pos[i]) {
				int u = find(p - 1), v = find(p);
				if(len[u] > i) seg[u].push_back({i + 1, len[u], sz[u]});
				if(len[v] > i) seg[v].push_back({i + 1, len[v], sz[v]});
				f[v] = u;
				sz[u] += sz[v];
				len[u] = i;
			}
		}
		if(len[1] >= 1) {
			seg[1].push_back({1, len[1], sz[1]});
		}
		for(int i = 1; i <= n; i++) {
			reverse(seg[i].begin(), seg[i].end());
		}
		for(int i = 1; i <= n; i++) {
			for(auto [l, r, sz]: seg[i]) {
				if(k > (r - l + 1) * sz) {
					k -= (r - l + 1) * sz;
				} else {
					for(int j = sa[i], lim = sa[i] + l + (k-1) / sz - 1; j <= lim; j++)
						cout << s[j];
					cout << endl;
					return;
				}
			}
		}
		cout << -1 << endl;
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
