#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;

int w, d, h;
int a, b, f, g;

void work() {
	
	cin >> w >> d >> h;
	cin >> a >> b >> f >> g;
	
	int ans = b + g + abs(a - f) + h;
	ans = min(ans, d - b + d - g + abs(a - f) + h);
	ans = min(ans, abs(b - g) + a + f + h);
	ans = min(ans, abs(b - g) + w + w - a - f + h);
	
	cout << ans << endl;
	
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
