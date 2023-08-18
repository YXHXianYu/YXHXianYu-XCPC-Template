#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;

const int B = 60;
struct LinearBasis {
	vector<int> a = vector<int>(B, 0);
	bool insert(int x) {
		for(int i = B - 1; i >= 0; i--) if(x & (1LL << i)) {
			if(a[i] == 0) { a[i] = x; return true; }
			x ^= a[i];
		}
		return false;
	}
	int queryMin(int x) {
		for(int i = B - 1; i >= 0; i--) {
			x = min(x, x ^ a[i]);
		}
		return x;
	}
	int queryMax(int x) {
		for(int i = B - 1; i >= 0; i--) {
			x = max(x, x ^ a[i]);
		}
		return x;
	}
};

void work() {
	int n, k;
	cin >> n >> k;

	vector<int> a(n + 1);
	for(int i = 1; i <= n; i++) cin >> a[i];

	LinearBasis b;
	int cnt0 = 0;
	for(int i = 1; i <= n; i++) {
		if(!b.insert(a[i])) {
			cnt0++;
		}
	}

	// 为什么是向下取整呢？因为有第0小的数，所以是向下取整
	k = k / (1LL << cnt0);
	// k >>= cnt0;

	int ans = 0;
	int cnt = 0;
	for(int i = 0; i < B; i++) {
		if(b.a[i] == 0) continue;
		cnt++;
	}
	cnt--;
	for(int i = B - 1; i >= 0; i--) {
		if(b.a[i] == 0) continue;
		if(k >= (1LL << cnt)) {
			k -= 1LL << cnt;
			ans = max(ans, ans ^ b.a[i]);
		} else {
			ans = min(ans, ans ^ b.a[i]);
		}
		cnt--;
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
