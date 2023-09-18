#include<bits/stdc++.h>
using namespace std;
#define int long long
#define DBL double
const int maxn = 2e5 + 10;

int n, m;

void work() {
	
	cin >> n >> m;
	
	set<DBL> k;
	
	for(int i = 1; i <= n; i++) {
		int x;
		cin >> x;
		k.insert(x);
	}
	
	while(m--) {
		int a, b, c;
		cin >> a >> b >> c;
		
		DBL ac4 = 4.0 * a * c;
		if(ac4 <= 0.0) {
			cout << "NO" << endl;
			continue;
		}
		
		DBL up = b + sqrt(ac4);
		DBL down = b - sqrt(ac4);
		
		auto it = k.upper_bound(down);
		if(it == k.end() || *it >= up) {
			cout << "NO" << endl;
		} else {
			cout << "YES" << endl;
			int ans = *it;
			cout << ans << endl;
		}
		
	}
	
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
