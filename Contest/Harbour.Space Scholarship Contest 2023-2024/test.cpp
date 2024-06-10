/**
 * Created by YXH_XianYu on 2023.8.27
 * Blog: https://yxhxianyu.fun
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'


#define int long long
typedef long double db;

db mySqrt(db x, int t) {
	db l = 0;
	db r = x;
	for(int i = 1; i <= t; i++) {
		db md = (l + r) / 2.0L;
		if(md * md <= x) l = md;
		else r = md;
	}
	return l;
}

void work() {
	auto fm = clock();

	int lim = 1e7;
	int cnt = 0;
	for(int i = 1; i <= lim; i++) {
		// 1st case
		cnt += sqrtl(i);
		// 2nd case
		// cnt += mySqrt(i, 30);
	}

	auto ed = clock();

	cout << fixed << setprecision(3);
	cout << cnt << " | ";
	cout << 1.0 * (ed - fm) / CLOCKS_PER_SEC << " sec" << endl;
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