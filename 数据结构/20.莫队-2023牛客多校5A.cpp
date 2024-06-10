/**
 * Created by YXH_XianYu on 2023.8.29
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

	vector<array<int, 3>> opt(m + 1);
	for(int i = 1; i <= m; i++) cin >> opt[i][0] >> opt[i][1], opt[i][2] = i;

	// bit
	vector<int> bit(n + 1);
	#define lowbit(x) (x&-x)
	auto add = [&](int x, int v) {
		for(; x <= n; x += lowbit(x)) bit[x] += v;
	};
	auto query = [&](int x) {
		int ans = 0; for(; x; x -= lowbit(x)) ans += bit[x]; return ans;
	};

	// precom
	vector<int> s(n + 1); // s[i] = sigma(j, a[j] < a[i])
	for(int i = 1; i <= n; i++) {
		s[i] = query(a[i] - 1);
		add(a[i], 1);
	}

	// MoDui
	int B = sqrt(500000);
	int N = (n - 1) / B + 1;
	vector<int> L(N + 1), R(N + 1), id(n + 1);
	for(int i = 1; i <= n; i++) {
		id[i] = (i - 1) / B + 1;
		if(L[id[i]] == 0) L[id[i]] = i;
		R[id[i]] = i;
	}

	sort(opt.begin() + 1, opt.begin() + m + 1, [&](const array<int, 3>& a, const array<int, 3>& b) {
		if(id[a[0]] != id[b[0]]) return id[a[0]] < id[b[0]];
		return (id[a[0]] & 1 ? a[1] < b[1] : a[1] < b[1]);
	});

	// solve
	vector<int> cnt(n + 1); // cnt[p]: p的出现次数
	vector<int> sum(n + 1); // sum[p]: p == ai == ak 的 (i, j, k) 个数
	int anscnt = 0;
	auto addR = [&](int x) {
		anscnt += cnt[a[x]] * s[x] - sum[a[x]];
		cnt[a[x]]++;
		sum[a[x]] += s[x];
	};
	auto addL = [&](int x) {
		anscnt += sum[a[x]] - cnt[a[x]] * s[x];
		cnt[a[x]]++;
		sum[a[x]] += s[x];
	};
	auto delR = [&](int x) {
		cnt[a[x]]--;
		sum[a[x]] -= s[x];
		anscnt -= cnt[a[x]] * s[x] - sum[a[x]];
	};
	auto delL = [&](int x) {
		cnt[a[x]]--;
		sum[a[x]] -= s[x];
		anscnt -= sum[a[x]] - cnt[a[x]] * s[x];
	};

	int l = 1, r = 0;
	vector<int> ans(m + 1);
	for(int i = 1; i <= m; i++) {
		while(r < opt[i][1]) r++, addR(r);
		while(l > opt[i][0]) l--, addL(l);
		while(r > opt[i][1]) delR(r), r--;
		while(l < opt[i][0]) delL(l), l++;
		ans[opt[i][2]] = anscnt;
	}

	for(int i = 1; i <= m; i++) cout << ans[i] << endl;
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