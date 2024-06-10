#include<bits/stdc++.h>
using namespace std;
#define int long long


void work() {
	int n;
	cin >> n;
	
	
	vector<int> p(n + 1);
	for(int i = 1; i <= n; i++) cin >> p[i];
	
	vector<int> c(n + 1);
	for(int i = 1; i <= n; i++) cin >> c[i];
	
	vector<vector<int>> rings;
	vector<int> vis(n + 1);
	
	auto getRing = [&](int st) {
		int x = st;
		vector<int> a;
		do {
			a.push_back(x);
			vis[x] = 1;
			x = p[x];
		} while(x != st);
		rings.push_back(a);
	};
	
	for(int i = 1; i <= n; i++) if(!vis[i]) getRing(i);
	
	sort(rings.begin(), rings.end(), [&](const vector<int>& a, const vector<int>& b) {
		return a.size() < b.size();
	});
	
	int ans = n;
	for(auto ring: rings) {
//		for(auto x: ring) cout << x << " "; cout << endl;

		int N = ring.size();
		ans = min(ans, N);
		for(int i = 1; i < N && i < ans; i++) {
			if(N % i != 0) continue;
			for(int j = 0; j < i; j++) {
				int foundAns = true;
				int col = c[ring[j]];
				for(int k = j + i; k < N; k += i) {
					if(c[ring[k]] != col) {
						foundAns = false;
					}
				}
				if(foundAns) {
					ans = min(ans, i);
					break;
				}
			}
		}
	}
	
	cout << ans << endl;
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int t = 1;
	cin >> t;
	while(t--) {
		work();
	}	
	
	return 0;
}