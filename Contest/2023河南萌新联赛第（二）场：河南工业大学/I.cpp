/**
 * Created by YXH_XianYu on 2023.8.31
 * Blog: https://yxhxianyu.fun
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'


void work() {
	int n;
	cin >> n;
	int N = n;

	int cnt = 0;
	int len = 0;
	while(n) {
		if(n & 1) cnt += 1;
		len++;
		n >>= 1;
	}

	int ans = 1LL << len - 1;
	cnt -= 1;
	for(int i = 0; i < cnt; i++) {
		ans |= 1LL << i;
	}
	cout << N - ans << endl;
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