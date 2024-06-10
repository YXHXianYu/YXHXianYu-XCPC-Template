#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;


void work() {
	int n;
	cin >> n;

	vector<int> a(n + 1);
	for(int i = 1; i <= n; i++) cin >> a[i];

	// lmin[i]: max{j | j < i && a[j] < a[i]}
	vector<int> lmin(n + 1);
	vector<int> stk(n + 1);
	for(int i = 1; i <= n; i++) {
		while(stk[0] && a[stk[stk[0]]] > a[i]) stk[0]--;
		if(stk[0]) lmin[i] = stk[stk[0]];
		else lmin[i] = 0;
		stk[++stk[0]] = i;
	}
	vector<int> rmin(n + 1);
	stk[0] = 0;
	for(int i = n; i >= 1; i--) {
		while(stk[0] && a[stk[stk[0]]] > a[i]) stk[0]--;
		if(stk[0]) rmin[i] = stk[stk[0]];
		else rmin[i] = n + 1;
		stk[++stk[0]] = i;
	}

	// for(int i = 1; i <= n; i++) cout << lmin[i] << " "; cout << endl;
	// for(int i = 1; i <= n; i++) cout << rmin[i] << " "; cout << endl;

	// pos
	vector<int> pos(n + 1);
	for(int i = 1; i <= n; i++) pos[a[i]] = i;

	// solve
	vector<int> len(n + 1);
	// fL[i], fR[i]: 指下标i处区间的长度；若为0则表示区间尚未激活
	int ans = 0;
	for(int i = 1; i <= n; i++) {
		int p = pos[i];
		int L = p;
		int R = p;
		if(L > 1) L -= len[L - 1]; // 考虑左边的区间，这个区间内所有元素小于i
		if(R < n) R += len[R + 1]; // 考虑右边的区间，这个区间内所有元素小于i

		// cout << i << ", " << L << ", " << R << ": " << p << endl;

		int cnt = 0;

		if(R - p <= p - L) { // 右边区间更短
			cnt += p - L;
			int mnp = p + 1;
			for(int i = p + 1; i <= R; i++) {
				mnp = a[i] < a[mnp] ? i : mnp;
				int v = lmin[mnp];
				// cout << "(" << v << ", " << mnp << ", " << v-L+1 << ")" << endl;
				if(L <= v) cnt += v - L + 1;
				else break;
			}
		} else { // 左边区间更短
			int mnp = p - 1;
			for(int i = p - 1; i >= L; i--) {
				mnp = a[i] < a[mnp] ? i : mnp;
				int v = rmin[mnp];
				if(R < v) cnt += R - p + 1;
				else cnt += v - p;
			}
		}

		// cout << " => " << cnt << endl;

		ans += cnt;

		len[L] = R - L + 1;
		len[R] = R - L + 1;
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
