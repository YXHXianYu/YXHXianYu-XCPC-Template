#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;


void work() {
	int n;
	cin >> n;

	vector<int> a(n + 1);
	for(int i = 1; i <= n; i++) cin >> a[i];

	vector<int> f(n + 1), g(n + 1), h(n + 1);
	for(int i = 1; i <= n; i++) {
		if(h[a[i]] == 0) {
			f[i] = 0;
			g[i] = max(g[i - 1], f[i]);
			h[a[i]] = i;
		} else {
			int j = h[a[i]];
			f[i] = i-j+1 + g[j-1];
			g[i] = max(g[i - 1], f[i]);
			// cout << i << ": " << f[i] << ", " << g[i] << ", " << h[a[i]] << endl;
			if(g[i - 1] + 1 > f[i]) {
				h[a[i]] = i;
			}
		}
	}

	// for(int i = 1; i <= n; i++) cout << f[i] << " "; cout << endl;
	// for(int i = 1; i <= n; i++) cout << g[i] << " "; cout << endl;
	// for(int i = 1; i <= n; i++) cout << h[i] << " "; cout << endl;

	cout << g[n] << endl;
		
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
