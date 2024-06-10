#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;


void work() {
    int n;
    cin >> n;

    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];
    
    int m;
    cin >> m;
    vector<pair<int, int>> opt(m + 1);
    for(int i = 1; i <= m; i++) cin >> opt[i].first >> opt[i].second;
    // sort(opt.begin() + 1, opt.begin() + m + 1);

    for(int j = 1; j <= n; j++) cout << a[j] << " "; cout << endl;
    for(int i = 1; i <= m; i++) {
        a[opt[i].first] += a[opt[i].second];
        for(int j = 1; j <= n; j++) cout << a[j] << " "; cout << endl;
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