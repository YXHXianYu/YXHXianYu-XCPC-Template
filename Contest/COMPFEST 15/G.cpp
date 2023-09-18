/**
 * Created by YXH_XianYu on 2023.9
 * Blog: https://yxhxianyu.fun
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'


void work() {
	int n;
	cin >> n;

	vector<int> a(n + 1);
	for(int i = 1; i <= n; i++) cin >> a[i];

	vector<int> d(n + 1);
	for(int i = 1; i <= n; i++) cin >> d[i];	

	int allzero = true;
	for(int i = 1; i <= n; i++) if(a[i] != 0) {
		allzero = false;
		break;
	}

	if(allzero) {
		cout << "0" << endl;
		return;
	}

	int L = 0, R = 0;
	for(int i = 1; i <= n; i++) R = max(R, a[i]);

	vector<vector<array<int, 2>>> g(n + 1, vector<array<int, 2>>());
	for(int i = 1; i <= n; i++) {
		if(a[i] == 0) continue;
		int st = max(1ll, i - d[i]);
		int ed = min(n, i + d[i]);
		g[st].push_back({ed, a[i]});
	}

	auto check = [&](int md) -> bool {
		
		priority_queue<array<int, 2>> pq;
		
		for(int i = 1; i <= n; i++) {
			for(auto [ed, v]: g[i]) { pq.push({-ed, v}); }

			if(!pq.empty() && -pq.top()[0] < i) { return false; }

			int left = md;
			while(!pq.empty()) {
				auto [ed, v] = pq.top();
				pq.pop();
				ed = -ed;

				if(v < left) {
					left -= v;
				} else if(v == left) {
					break;
				} else {
					v -= left;
					pq.push({-ed, v});
					break;
				}
			}
		}

		return pq.empty();
	};

	while(R - L >= 2) {
		int md = L + R >> 1;
		if(check(md)) {
			R = md;
		} else {
			L = md;
		}
	}

	cout << R << endl;
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