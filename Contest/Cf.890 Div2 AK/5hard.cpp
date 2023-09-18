#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 1e6 + 10;

template <int len = 1>
int getDp(const vector<int>& a, int sz) {
	if(sz >= len) return getDp<min(len << 1, maxn)>(a, sz);

	bitset<len> f;

	f[0] = 1;
	for(auto x: a) f = f | (f << x);

	int ans = 0;
	for(int i = 1; i < sz; i++) {
		if(f[i]) {
			ans = max(ans, i * (sz - i));
		}
	}
	return ans;
}

void work() {
	int n;
	cin >> n;
	
	vector<vector<int>> e(n + 1, vector<int>());
	vector<int> fa(n + 1);
	for(int i = 2; i <= n; i++) {
		cin >> fa[i];
		e[fa[i]].push_back(i);
	}

	int ans = 0;
	vector<int> sz(n + 1);

	auto solve = [](vector<int>& a) -> int {
		sort(a.begin(), a.end());
		int s = 0;
		for(auto x: a) s += x;
		
		int mx = *a.rbegin();
		if(2 * mx >= s) return mx * (s - mx);

		vector<pair<int, int>> b;
		for(auto x: a) {
			if(b.size() == 0 || b.rbegin()->first != x) {
				b.push_back({x, 1});
			} else {
				b.rbegin()->second++;
			}
		}

		a.clear();
		for(auto& pr: b) {
			int cnt = 0;
			for(int i = 1; true; i <<= 1) {
				if(i + cnt >= pr.second) {
					a.push_back(pr.first * (pr.second - cnt));
					break;
				} else {
					a.push_back(pr.first * i);
					cnt += i;
				}
			}
		}

		// for(auto& pr: b) cout << "(" << pr.first << ", " << pr.second << ") "; cout << endl;
		// for(auto x: a) cout << x << " "; cout << endl;

		return getDp(a, s);
	};

	function<void(int)> dfs = [&](int x) {
		vector<int> a;
		for(auto y: e[x]) {
			dfs(y);
			a.push_back(sz[y]);
			sz[x] += sz[y];
		}
		if(a.size() <= 1) {
			sz[x] += 1;
			return;
		}
		ans += solve(a);
		sz[x] += 1;

		// int sz2 = sz[x] / 2;
		// vector<int> f(sz2 + 5);

		// int lim = 0;
		// f[0] = 1;
		// for(int i = 0; i < a.size(); i++) {
		// 	auto g = f;
		// 	for(int j = 0; j <= lim; j++) {
		// 		if(g[j] == 1) {
		// 			if(j + a[i] <= sz2) f[j + a[i]] = 1;
		// 		}
		// 	}
		// 	lim = min(lim + a[i], sz2);
		// }

		// int cnt = 0;
		// for(int i = lim; i >= 0; i--) {
		// 	if(f[i] == 1) {
		// 		ans += i * (sz[x] - i);
		// 		// cout << x << ": " << i << " * " << sz[x] - i << endl;
		// 		break;
		// 	}
		// }

	};

	dfs(1);

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
