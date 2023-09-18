#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;


void work() {
	int n;
	cin >> n;

	vector<int> a(n + 1);
	for(int i = 1; i <= n; i++) cin >> a[i];

	int lim = log2(n);
	vector<vector<pair<int, int>>> mx(lim + 1, vector<pair<int, int>>(n + 1));
	vector<vector<pair<int, int>>> mn(lim + 1, vector<pair<int, int>>(n + 1));
	for(int i = 1; i <= n; i++) mx[0][i] = {a[i], i};
	for(int i = 1; i <= n; i++) mn[0][i] = {a[i], i};
	for(int k = 1; k <= lim; k++) {
		int lim2 = n - (1 << k) + 1;
		for(int i = 1; i <= lim2; i++) {
			mx[k][i] = max(mx[k-1][i], mx[k-1][i+(1<<k-1)]);
			mn[k][i] = min(mn[k-1][i], mn[k-1][i+(1<<k-1)]);
		}
	}

	vector<int> log2f(n + 1);
	for(int i = 1; i <= n; i++) log2f[i] = log2(i);

	auto queryMx = [&](int L, int R) {
		int k = log2f[R - L + 1];
		return (max(mx[k][L], mx[k][R-(1<<k)+1])).second;
	};
	auto queryMn = [&](int L, int R) {
		int k = log2f[R - L + 1];
		return (min(mn[k][L], mn[k][R-(1<<k)+1])).second;
	};

	int ans = 0;
	function<void(int, int)> solve = [&](int L, int R) {
		// cout << L << ", " << R << endl;
		if(R - L <= 0) return;
		int mxpos = queryMx(L, R);
		int mnpos = queryMn(L, R);
		// cout << L << ", " << R << ": " << mnpos << ", " << mxpos << endl;
		if(mxpos < mnpos) {
			// ans += (mxpos - mnpos) << 1;
			// mxpos
			int mnp = mxpos - 1;
			for(int i = mxpos; i < mnpos; i++) {
				while(a[mnp] > a[i] && mnp >= L) mnp--;
				if(mnp < L) break;
				
				ans += (mnp - L + 1);
			}
			// mnpos
			int mxp = mnpos + 1;
			for(int i = mnpos; i > mxpos; i--) {
				while(a[i] > a[mxp] && mxp <= R) mxp++;
				if(mxp > R) break;

				ans += (R - mxp + 1);
			}
			// other
			solve(L, mxpos-1);
			solve(mxpos+1, mnpos-1);
			solve(mnpos+1, R);
		} else if(mnpos < mxpos) {
			ans += (mnpos - L + 1) * (R - mxpos + 1);
			// ans += (mxpos - mnpos - 1) << 1;
			// mxpos
			int mnp = mxpos - 1;
			for(int i = mxpos; i <= R; i++) {
				while(a[mnp] > a[i] && mnp > mnpos) mnp--;
				if(mnp <= mnpos) break;
				// a[mnp] <= a[i] && mnp > mnpos
				ans += (mnp - mnpos);
			}
			// mnpos
			int mxp = mnpos + 1;
			for(int i = mnpos; i >= L; i--) {
				while(a[i] > a[mxp] && mxp < mxpos) mxp++;
				if(mxp >= mxpos) break;
				// a[i] <= a[mxp] && mxp < mxpos
				ans += (mxpos - mxp);
			}
			// other
			solve(L, mnpos-1);
			solve(mnpos+1, mxpos-1);
			solve(mxpos+1, R);
		} else {
			assert(false);
		}
	};

	solve(1, n);

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
