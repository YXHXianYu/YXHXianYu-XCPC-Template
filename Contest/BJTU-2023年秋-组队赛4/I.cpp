/**
 * Created by YXH_XianYu in 2023.10
 * Blog: https://yxhxianyu.fun
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'

/*
(x1, y1), (x2, y2)
g = (x1, y1)

x2/g * (x1, y1) - x1/g * (x2, y2) = (0, t) = (0, x2/g*y1 - x1/g*y2)

*/

void work() {
	int n;
	cin >> n;

	function<int(int, int, int&, int&)> exgcd = [&](int n, int m, int &x, int &y) -> int {
		if(m == 0) {
			x = 1;
			y = 0;
			return n;
		}
		int g = exgcd(m, n % m, x, y);
		int z = x;
		x = y;
		y = z - n / m * y;
		return g;
	};

	auto merge = [&](array<int, 2>& a, array<int, 2>& b) {
		int g = __gcd(a[0], b[0]);
		int t = b[0]/g*a[1] - a[0]/g*b[1];
		

	};

	int ans = 0;
	vector<array<int, 2>> a;
	for(int T = 1; T <= n; T++) {
		int opt, x, y;
		cin >> opt >> x >> y;
		if(opt == 1) {
			if(a.size() == 0) {
				a.push_back({x, y});
			} else if(a.size() == 1) {

			} else if(a.size() == 2) {
				
			}
		} else if(opt == 2) {
			int w;
			cin >> w;

		} else assert(false);
	}
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