/**
 * Created by YXH_XianYu on 2023.8.31
 * Blog: https://yxhxianyu.fun
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'

/*
f[i]: max(f[i-j], j in [1, c-1])
f[i]: max(f[i-c] + mn(i-c+1,i))
*/

void work() {
	int n, c;
	cin >> n >> c;

	vector<int> a(n + 1);
	for(int i = 1; i <= n; i++) cin >> a[i];

	if(c == 1) {
		int ans = 0;
		for(int i = 1; i <= n; i++) ans += a[i];
		cout << ans << endl;
		return;
	}

	vector<int> f(n + 1);
	vector<array<int, 2>> stkf(n + 1), stka(n + 1);
	int topf = 0, topa = 0;
	int btnf = 1, btna = 1;
	for(int i = 1; i < c; i++) {
		while(topa >= btna && i-stka[btna][1] >= c) btna++;
		while(topa >= btna && stka[topa][0] >= a[i]) topa--;
		stka[++topa] = {a[i], i};

		while(topf >= btnf && i-stkf[btnf][1] >= c) btnf++;
		while(topf >= btnf && stkf[topf][0] <= f[i]) topf--;
		stkf[++topf] = {f[i], i};
	}
	
	int ans = 0;
	for(int i = c; i <= n; i++) {
		while(topa >= btna && i-stka[btna][1] >= c) btna++;
		while(topf >= btnf && i-stkf[btnf][1] >= c) btnf++;

		while(topa >= btna && stka[topa][0] >= a[i]) topa--;
		stka[++topa] = {a[i], i};

		if(topa >= btna) f[i] = max(f[i], f[i-c] + stka[btna][0]);
		if(topf >= btnf) f[i] = max(f[i], stkf[btnf][0]);

		while(topf >= btnf && stkf[topf][0] <= f[i]) topf--;
		stkf[++topf] = {f[i], i};

		ans = max(ans, f[i]);
	}

	cout << ans << endl;
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