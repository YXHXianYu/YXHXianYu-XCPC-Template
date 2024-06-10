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

	auto b = a;

	vector<array<int, 4>> qopt(m + 1);
	int qcnt = 0;
	vector<array<int, 3>> mopt(m + 1);
	int mcnt = 0;
	for(int i = 1; i <= m; i++) {
		char ch;
		cin >> ch;
		if(ch == 'Q') {
			qcnt++;
			cin >> qopt[qcnt][0] >> qopt[qcnt][1];
			qopt[qcnt][2] = mcnt;
			qopt[qcnt][3] = qcnt;
		} else if(ch == 'R') {
			int pos, col;
			cin >> pos >> col;

			mcnt++;
			mopt[mcnt][0] = pos;
			mopt[mcnt][1] = b[pos];
			b[pos] = col;
			mopt[mcnt][2] = b[pos];
		}
	}

	// block
	// 序列长度为n，m个询问，t个修改
	// B = n^(2/3) * t^(1/3) / m^(1/3)
	int B = pow(1.3e5, 2.0/3.0);
	int N = (n - 1) / B + 1;
	vector<int> L(N + 1), R(N + 1), id(n + 1);
	for(int i = 1; i <= n; i++) {
		id[i] = (i - 1) / B + 1;
		if(L[id[i]] == 0) L[id[i]] = i;
		R[id[i]] = i;
	}

	// sort
	sort(qopt.begin() + 1, qopt.begin() + qcnt + 1, [&](const array<int, 4>& a, const array<int, 4>& b) {
		if(id[a[0]] != id[b[0]]) return id[a[0]] < id[b[0]];
		if(id[a[1]] != id[b[1]]) return id[a[1]] < id[b[1]];
		return a[2] < b[2];
	});

	// solve
	vector<int> cnt(1e6 + 10);
	vector<int> ans(qcnt + 1);
	int anscnt = 0;
	auto add = [&](int x) {
		cnt[a[x]]++;
		if(cnt[a[x]] == 1) anscnt++;
	};
	auto del = [&](int x) {
		if(cnt[a[x]] == 1) anscnt--;
		cnt[a[x]]--;
	};
	auto forwd = [&](int l, int r, int t) {
		if(l <= mopt[t][0] && mopt[t][0] <= r) {
			if(cnt[mopt[t][1]] == 1) anscnt--;
			cnt[mopt[t][1]]--;
			cnt[mopt[t][2]]++;
			if(cnt[mopt[t][2]] == 1) anscnt++;
		}
		a[mopt[t][0]] = mopt[t][2];
	};
	auto back = [&](int l, int r, int t) {
		if(l <= mopt[t][0] && mopt[t][0] <= r) {
			if(cnt[mopt[t][2]] == 1) anscnt--;
			cnt[mopt[t][2]]--;
			cnt[mopt[t][1]]++;
			if(cnt[mopt[t][1]] == 1) anscnt++;
		}
		a[mopt[t][0]] = mopt[t][1];
	};

	int l = 1, r = 0, t = 0;
	for(int i = 1; i <= qcnt; i++) {
		while(r < qopt[i][1]) ++r, add(r);
		while(l > qopt[i][0]) --l, add(l);
		while(r > qopt[i][1]) del(r), r--;
		while(l < qopt[i][0]) del(l), l++;
		while(t < qopt[i][2]) t++, forwd(l, r, t);
		while(t > qopt[i][2]) back(l, r, t), t--;
		ans[qopt[i][3]] = anscnt;
	}

	for(int i = 1; i <= qcnt; i++) cout << ans[i] << endl;
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