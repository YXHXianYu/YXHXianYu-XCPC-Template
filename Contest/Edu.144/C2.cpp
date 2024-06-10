#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;
const int MOD = 998244353;

int l, r;
int ans1;

map<pair<int, int>, int> f;

int solve(int k, int x) {
	if(k <= 0 && x > r) {
		return 1;
	} else if(k <= 0) {
		assert(false);
	} else if(x > r) {
		return 0;
	}
	
	if(f.count(make_pair(k, x)) != 0) {
		return f[make_pair(k, x)];
	}
	
	int cnt = 0;
	for(int i = 2; i <= 3; i++) {
		cnt += solve(k - 1, x * i);
	}
	
	return (f[make_pair(k, x)] = cnt);
}

void work() {
	
	cin >> l >> r;
	
	ans1 = 0;
	for(int i = l; i <= r; i <<= 1) {
		ans1++;
	}
	
	f.clear();
	
	int ans2 = 0;
	for(int i = l; i <= r; i++) {
		ans2 = (ans2 + solve(ans1, i)) % MOD;
	}
	
	cout << ans1 << " " << (ans2 / 2) << endl;
	
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int t = 1;
	cin >> t;
	while(t--) {
		work();
	}
	
	return 0;
}
