#include<bits/stdc++.h>
using namespace std;
// #define int long long

void work() {
    int n;
    cin >> n;

    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];
    vector<int> b(n + 1);
    for(int i = 1; i <= n; i++) b[i] = a[i];
    vector<int> c(n + 1);
    for(int i = 1; i <= n; i++) c[i] = a[i];
    
	int mx = 1;
	int mn = 1;
	for(int i = 2; i <= n; i++) {
		mx = a[i] > a[mx] ? i : mx;
		mn = a[i] < a[mn] ? i : mn;
	}

	vector<pair<int, int>> ans;

	auto add = [&](int i, int j) {
		a[i] += a[j];
		ans.push_back({i, j});
	};

	if(a[mx] == 0 && a[mn] == 0) {
		cout << 0 << endl;
		return;
	}
	
	auto ans1 = ans; ans1.resize(100);
	auto ans2 = ans; ans2.resize(100);

	if(a[mx] > 0) {
		while(a[mx] < (-a[mn])) add(mx, mx);
		for(int i = 1; i <= n; i++) if(a[i] < 0) add(i, mx);
		for(int i = 2; i <= n; i++) add(i, i-1);

		ans1 = ans;
		for(int i = 1; i <= n; i++) a[i] = b[i];
		ans.clear();
	}

	if(a[mn] < 0) {
		while(a[mn] > (-a[mx])) add(mn, mn);
		for(int i = 1; i <= n; i++) if(a[i] > 0) add(i, mn);
		for(int i = n - 1; i >= 1; i--) add(i, i+1);

		ans2 = ans;
		for(int i = 1; i <= n; i++) a[i] = b[i];
		ans.clear();
	}

	ans = ans1.size() <= ans2.size() ? ans1 : ans2;

	cout << ans.size() << endl;
	for(auto& pr: ans) cout << pr.first << " " << pr.second << endl;

}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	// freopen("1.txt", "r", stdin);
	// freopen("1out.txt", "w", stdout);
	
	int t = 1;
	cin >> t;
	for(int i = 1; i <= t; i++) {
		// if(i % 10000 == 0) cerr << i << endl;
		work();
	}
	
	return 0;
}