#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;


void work() {
	// refer to jiangly's code
    int n;
	cin >> n;

	vector<int> a(n + 1);
	for(int i = 1; i <= n; i++) cin >> a[i];

	int lim = 20 * n;
	vector<bool> b(lim);

	vector<int> c;
	for(int i = 1; i <= n; i++) {
		vector<int> d;
		if(a[i] < lim) {
			d.push_back(a[i]);
		}
		for(auto x: c) {
			int v = lcm(x, a[i]);
			if(v < lim) {
				d.push_back(v);
			}
		}
		sort(d.begin(), d.end());
		d.erase(unique(d.begin(), d.end()), d.end());
		c = d;
		for(auto x: c) {
			b[x] = true;
		}
	}

	int ans = 1;
	while(b[ans]) {
		ans++;
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