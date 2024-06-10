/**
 * Created by YXH_XianYu on 2023.9
 * Blog: https://yxhxianyu.fun
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'


void work() {
	int n, k;
	cin >> n >> k;

	auto query = [&](int x) {
		assert(x <= n - k + 1);
		cout << "? " << x << endl;
		cout.flush();
		int y;
		cin >> y;
		return y;
	};
	auto answer = [&](int x) {
		cout << "! " << x << endl;
		cout.flush();
		return;
	};
	
	int ans = 0;
	int len = n;
	int i;
	for(i = 1; len >= 2 * k; i += k, len -= k) {
		ans ^= query(i);
	}

	if(len == k) {
		ans ^= query(n - k + 1);
		answer(ans);
		return;
	}

	// k < len < 2k
	assert((3 * k - len) % 2 == 0);
	int olp = (3 * k - len) / 2;

	vector<int> v(3);

	for(int j = 0; j <= 2; j++) {
		v[j] = query(i);
		i = i + k - olp;
	}

	ans ^= v[0] ^ v[1] ^ v[2];

	answer(ans);
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