/**
 * Created by YXH_XianYu on 2023.8.29
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

	int m;
	cin >> m;

	vector<array<int, 4>> b(m + 1);
	for(int i = 1; i <= m; i++) cin >> b[i][0] >> b[i][1] >> b[i][2], b[i][3] = i;

	// B = n/sqrt(m) = 316
	// int B = 1e5/sqrt(1e5);
	int B = 500;
	int N = (n - 1) / B + 1;
	vector<int> L(N + 1), R(N + 1), id(n + 1);
	for(int i = 1; i <= n; i++) {
		id[i] = (i - 1) / B + 1;
		if(L[id[i]] == 0) L[id[i]] = i;
		R[id[i]] = i;
	}

	sort(b.begin() + 1, b.end(), [&](const array<int, 4>& a, const array<int, 4>& b) {
		if(id[a[0]] != id[b[0]]) return id[a[0]] < id[b[0]];
		return (id[a[0]] & 1 ? a[1] < b[1] : a[1] > b[1]);
	});

	vector<int> freq(100010), cnt(n + 1);
	auto add = [&](int x) {
		cnt[freq[a[x]]]--;
		freq[a[x]]++;
		cnt[freq[a[x]]]++;
	};
	auto del = [&](int x) {
		cnt[freq[a[x]]]--;
		freq[a[x]]--;
		cnt[freq[a[x]]]++;
	};

	int l = 1, r = 0;
	vector<int> ans(m + 1);
	for(int i = 1; i <= m; i++) {
		while(r < b[i][1]) r++, add(r);
		while(b[i][0] < l) l--, add(l);
		while(r > b[i][1]) del(r), r--;
		while(b[i][0] > l) del(l), l++;
		ans[b[i][3]] = cnt[b[i][2]];
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