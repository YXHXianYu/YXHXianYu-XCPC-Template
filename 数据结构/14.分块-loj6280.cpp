/**
 * Created by YXH_XianYu on 2023.8.23
 * Blog: https://yxhxianyu.fun
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'


const int B = sqrt(5e4);
// const int B = 1;

void work() {
	int n;
	cin >> n;

	vector<int> a(n + 1);
	for(int i = 1; i <= n; i++) {
		cin >> a[i];
	}


	int N = (n - 1) / B + 1;
	vector<int> L(N + 1), R(N + 1), pos(n + 1);
	for(int i = 1; i <= n; i++) {
		pos[i] = (i - 1) / B + 1;
		if(L[pos[i]] == 0) L[pos[i]] = i;
		R[pos[i]] = i;
	}

	vector<int> S(N + 1), LZT(N + 1);
	for(int i = 1; i <= N; i++) {
		for(int j = L[i]; j <= R[i]; j++) {
			S[i] += a[j];
		}
	}

	for(int i = 1; i <= n; i++) {
		int opt, l, r, c;
		cin >> opt >> l >> r >> c;
		if(opt == 0) {
			int Lid = pos[l];
			int Rid = pos[r];
			if(Lid == Rid) {
				for(int j = l; j <= r; j++) { a[j] += c; S[Lid] += c; }
			} else {
				for(int j = l; pos[j] == Lid; j++) { a[j] += c; S[Lid] += c; }
				for(int j = r; pos[j] == Rid; j--) { a[j] += c; S[Rid] += c; }
				for(int j = Lid + 1; j < Rid; j++) { LZT[j] += c; S[j] += c * (R[j] - L[j] + 1); }
			}
		} else if(opt == 1) {
			int ans = 0;
			int Lid = pos[l];
			int Rid = pos[r];
			if(Lid == Rid) {
				for(int j = l; j <= r; j++) { ans += a[j] + LZT[Lid]; }
			} else {
				for(int j = l; pos[j] == Lid; j++) { ans += a[j] + LZT[Lid]; }
				for(int j = r; pos[j] == Rid; j--) { ans += a[j] + LZT[Rid]; }
				for(int j = Lid + 1; j < Rid; j++) { ans += S[j]; }
			}
			cout << ans % (c + 1) << endl;
		} else assert(false);
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
