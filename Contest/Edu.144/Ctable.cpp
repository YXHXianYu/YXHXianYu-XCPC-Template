#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;
const int MOD = 998244353;

int l, r;
int ans1;

int solve(int k, int x) {
	if(k <= 0 && x > r) {
		return 1;
	} else if(k <= 0) {
		assert(false);
	} else if(x > r) {
		return 0;
	}
	if(x * (1 << k - 1) > r) {
		return 0;
	}

	int cnt = 0;
	for(int i = 2; i <= 3; i++) {
		cnt += solve(k - 1, x * i);
	}
	
	return cnt;
}

void work() {
	
	
	ans1 = 0;
	for(int i = l; i <= r; i <<= 1) {
		ans1++;
	}
	
	int flag = 0;
	int cnt = 1;
	for(int i = l * 3; i <= r; i << 1) {
		cnt++;
	}
	
	int ans2 = 0;
	int x;
	if(cnt == ans1) {
		x = l;
		for(; x <= r; x <<= 1);
		x >>= 1;
		
		ans2 = (r - x + 1);
		
		x = l * 3;
		for(; x <= r; x <<= 1);
		x >>= 1;
		
		ans2 += (r - x + 1);
		
	} else {
		x = l;
		for(; x <= r; x <<= 1);
		x >>= 1;
		ans2 = (r - x + 1);
	}
	
	cout << ans1 << "-" << ans2 << "  ";
	
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	for(int i = 1; i <= 200; i++) {
		l = 1;
		r = 1000000;
		work();
	}
	
	return 0;
}
