/**
 * Created by YXH_XianYu in 2023.10
 * Blog: https://yxhxianyu.fun
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long
// #define endl '\n'

/*
(x1, y1), (x2, y2)
g = (x1, y1)

x2/g * (x1, y1) - x1/g * (x2, y2) = (0, t) = (0, x2/g*y1 - x1/g*y2)

Ax1 + By1 = g
Ax2 + By2 = dy
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

	vector<array<int, 2>> a(2);

	auto merge = [&](int x, int y) {
		if(x == 0) {
			a[1][1] = __gcd(a[1][1], y);
			return;
		}

		int A, B;
		int g = exgcd(a[0][0], x, A, B);
		int t = abs(x * a[0][1] - a[0][0] * y) / g;
		a[0][0] = g;
		a[0][1] = A * a[0][1] + B * y;
		a[1][1] = __gcd(a[1][1], t);
		if(a[1][1]) {
			a[0][1] %= a[1][1];
		}
	};

	int ans = 0;
	for(int T = 1; T <= n; T++) {
		int opt, x, y;
		cin >> opt >> x >> y;
		if(opt == 1) {
			if(x == 0 && y == 0) continue;
			merge(x, y);
		} else if(opt == 2) {
			int w;
			cin >> w;

			if(x == 0) {
				if(y == 0) { ans += w; continue; }
				if(a[1][1] > 0 && y % a[1][1] == 0) { ans += w; continue; }
			} else {
				if(a[0][0] == 0) continue;
				if(x % a[0][0] != 0) continue;
				int t = x / a[0][0];
				y = y - t * a[0][1];
				if(y == 0) { ans += w; continue; }
				if(a[1][1] == 0) continue;
				if(y % a[1][1] == 0) { ans += w; continue; }
			}
		} else assert(false);
	}

	cout << ans << endl;
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int t = 1;
	cin >> t;
	for(int i = 1; i <= t; i++) {
		cout << "Case #" << i << ": ";
		work();
	}
	
	return 0;
}