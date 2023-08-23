/**
 * Created by YXH_XianYu on 2023.8.23
 * Blog: https://yxhxianyu.fun
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'

void work() {
	int n, m;
	cin >> n >> m;

	vector<int> a(n + 1);
	for(int i = 1; i <= n; i++) cin >> a[i];

	const int B = 5e4 / sqrt(5e4);
	// O(n/B * n + m * B) => B = n / sqrt(m)

	int N = (n - 1) / B + 1;
	vector<int> L(N + 1), R(N + 1), id(n + 1);
	for(int i = 1; i <= n; i++) {
		id[i] = (i - 1) / B + 1;
		if(L[id[i]] == 0) L[id[i]] = i;
		R[id[i]] = i;
	}

	vector<array<int, 3>> opt(m + 1);
	for(int i = 1; i <= m; i++) cin >> opt[i][0] >> opt[i][1], opt[i][2] = i;
	sort(opt.begin() + 1, opt.begin() + m + 1, [&](const array<int, 3>& a, const array<int, 3>& b) {
		if(id[a[1]] != id[b[1]]) return id[a[1]] < id[b[1]];
		return a[0] < b[0];
	});

	int l = 1, r = 0;
	vector<int> cnt(n + 1);
	vector<int> ansRec(m + 1);
	vector<int> ansRec2(m + 1);
	int ans = 0;

	auto add = [&](int x) {
		ans += cnt[a[x]];
		cnt[a[x]]++;
	};
	auto sub = [&](int x) {
		cnt[a[x]]--;
		ans -= cnt[a[x]];
	};

	for(int i = 1; i <= m; i++) { // 先扩再缩
		while(r < opt[i][1]) r++, add(r);
		while(opt[i][0] < l) l--, add(l);
		while(r > opt[i][1]) sub(r), r--;
		while(opt[i][0] > l) sub(l), l++;
		ansRec[opt[i][2]] = ans;
		ansRec2[opt[i][2]] = opt[i][1] - opt[i][0] + 1;
	}
	for(int i = 1; i <= m; i++) {
		int x = ansRec[i];
		int y = ansRec2[i] * (ansRec2[i] - 1) / 2;
		if(x == 0) { cout << "0/1" << endl; continue; }
		int gcd = __gcd(x, y);
		x /= gcd, y /= gcd;
		cout << x << "/" << y << endl;
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