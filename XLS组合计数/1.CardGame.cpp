/**
 * Created by YXH_XianYu on 2023.8.25
 * Blog: https://yxhxianyu.fun
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'

const int MAXN = 100;
const int MOD = 998244353;
vector<int> fac(MAXN + 1);
vector<int> inv(MAXN + 1);

int Pow(int a, int n) {
	int ans = 1;
	while(n) {
		if(n & 1) ans = ans * a % MOD;
		a = a * a % MOD;
		n >>= 1;
	}
	return ans;
}
int Inv(int a) {
	return Pow(a, MOD - 2);
}
int C(int n, int m) {
	assert(n >= m);
	return fac[n] * inv[m] % MOD * inv[n - m] % MOD;
}

void upd(int &a, int b) {
	a += b;
	if(a >= MOD) a -= MOD;
}

void work() {
	int n;
	cin >> n;

	int ans1 = 0;
	int ans2 = 0;
	for(int i = n, j = 0; i - j - 1 >= 1; j = (j + 1) % 4) {
		if(j == 0) {
			upd(ans1, C(i - j - 1, (i >> 1) - 1));
		} else if(j == 1) {
			upd(ans2, C(i - j - 1, (i >> 1)));
		} else if(j == 2) {
			upd(ans2, C(i - j - 1, (i >> 1) - 1));
		} else if(j == 3) {
			upd(ans1, C(i - j - 1, (i >> 1) - 3));
			i -= 4;
		} else assert(false);
	}
	int sum = C(n, n >> 1);
	int ans3 = (sum - ans1 - ans2 + MOD + MOD) % MOD;
	assert(ans3 == 1);
	cout << ans1 << " " << ans2 << " " << 1 << endl;
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	fac[0] = 1;
	for(int i = 1; i <= MAXN; i++) fac[i] = fac[i - 1] * i % MOD;
	inv[MAXN] = Inv(fac[MAXN]);
	for(int i = MAXN - 1; i >= 0; i--) inv[i] = inv[i + 1] * (i + 1) % MOD;
	assert(inv[0] == 1);
	
	int t = 1;
	cin >> t;
	while(t--) {
		work();
	}
	
	return 0;
}