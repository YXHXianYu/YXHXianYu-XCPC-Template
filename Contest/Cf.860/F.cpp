#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 400 + 10;

int n, m;
int a[maxn];
int s[maxn];

multiset<int> b;

int idx[maxn];
vector<int> f[maxn][maxn];
vector<int> ans[maxn];

void work() {
	
	cin >> n >> m;
	for(int i = 1; i <= n; i++) cin >> a[i];
	for(int i = 1; i <= m; i++) cin >> s[i];
	
	if(m == 1) {
		// spj
		int cnt = 0;
		for(int i = 1; i <= n; i++) cnt += a[i];
		cnt = s[1] - cnt;
		cout << cnt << endl;
		for(int i = 1; i <= n; i++) cout << a[i] << " ";
		cout << cnt << endl;
		return;
	}
	
	for(int i = 1; i <= m; i++) idx[i] = i;
	sort(idx + 1, idx + m + 1, [&](int a, int b) {
		return s[a] > s[b];	
	});
	
	for(int i = 1; i <= m; i++) ans[i].clear();
	
	for(int i = 1; i <= n; i++) b.insert(a[i]);
	
	for(int i1 = 2; i1 <= m; i1++) { // O(m)
		int i = idx[i1];
		
		if(s[i] == 1) {
			ans[i].push_back(*b.begin());
			b.erase(b.begin());
			continue;
		}
		
		for(int j = 1; j <= s[i]; j++) {
			for(int k = 0; k < s[i]; k++) {
				f[j][k].clear();
			}
		}
		
		// f[j][k], j in [1, s[i]], k in [0, s[i]-1]
		
		int first = true;
		for(auto x: b) { // O(n)
			if(first) {
				f[1][x % s[i]].push_back(x);
				first = false;
			} else {
				// j = s[i] - 1
				for(int k = 0; k < s[i]; k++) {
					if(f[s[i] - 1][k].size() == 0) continue;
					if((k + x) % s[i] == 0) {
						// find ans
						f[s[i]][0] = f[s[i] - 1][k];
						f[s[i]][0].push_back(x);
						break;
					}
				}
				if(f[s[i]][0].size() > 0) {
					break;
				}
				
				// j < s[i] - 1
				for(int j = s[i] - 2; j >= 1; j--) {
					for(int k = 0; k < s[i]; k++) {
						if(f[j][k].size() == 0) continue;
						int v = (k + x) % s[i];
						if(f[j + 1][v].size() != 0) continue;
						f[j + 1][v] = f[j][k];
						f[j + 1][v].push_back(x);
					}
				}
				// j = 0
				if(f[1][x % s[i]].size() == 0) {
					f[1][x % s[i]].push_back(x);
				}
			}
		}
		if(f[s[i]][0].size() > 0) {
			// find ans
			ans[i] = f[s[i]][0];
			for(auto x: ans[i]) {
				auto it = b.lower_bound(x);
				b.erase(it);
			}
		} else {
			assert(false);
		}
		
//		cout << i << ": "; for(auto x: ans[i]) cout << x << " "; cout << endl;
//		cout << " - "; for(auto x: b) cout << x << " "; cout << endl;
//		cout << endl;
		
	}
	
	int cnt = 0;
	for(auto x: b) {
		cnt = (cnt + x) % s[idx[1]];
		ans[idx[1]].push_back(x);
	}
	
	cnt = s[idx[1]] - cnt;
	ans[idx[1]].push_back(cnt);
	
	cout << cnt << endl;
	for(int i = 1; i <= m; i++) {
		for(auto x: ans[i]) {
			cout << x << " ";
		}
		cout << endl;
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
