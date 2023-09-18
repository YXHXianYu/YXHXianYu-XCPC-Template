#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'

typedef long double db;

int read() {
	int ans = 0, sign = 1; char ch = getchar();
	while((ch < '0' || '9' < ch) && ch != '-') ch = getchar();
	if(ch == '-') sign = -1, ch = getchar();
	while('0' <= ch && ch <= '9') ans = 10 * ans + ch - '0', ch = getchar();
	return sign * ans;
}

void work() {
	// int x11, y11, x12, y12;
	// int x21, y21, x22, y22;
	
	// scanf("%lld%lld%lld%lld", &x11, &y11, &x12, &y12);
	// scanf("%lld%lld%lld%lld", &x21, &y21, &x22, &y22);

	// db x11, y11, x12, y12;
	// db x21, y21, x22, y22;
	
	// scanf("%Lf%Lf%Lf%Lf", &x11, &y11, &x12, &y12);
	// scanf("%Lf%Lf%Lf%Lf", &x21, &y21, &x22, &y22);

	int x11 = read(), y11 = read(), x12 = read(), y12 = read();
	int x21 = read(), y21 = read(), x22 = read(), y22 = read();
	
	db xo1, yo1;
	db xo2, yo2, r2;
	
	xo1 = 1.0 * (x11 + x12) / 2.0;
	yo1 = 1.0 * (y11 + y12) / 2.0;
	
	xo2 = 1.0 * (x21 + x22) / 2.0;
	yo2 = 1.0 * (y21 + y22) / 2.0;
	r2 = sqrt((x21-x22)*(x21-x22) + (y21-y22)*(y21-y22)) / 2.0;
	
	db ansx = xo2;
	db ansy = yo2;
	
	if(xo1 < xo2) {
		ansx -= r2 / sqrt(2);
	} else {
		ansx += r2 / sqrt(2);
	}
	
	if(yo1 < yo2) {
		ansy -= r2 / sqrt(2);
	} else {
		ansy += r2 / sqrt(2);
	}
	
	db ans = abs(ansx - xo1) + abs(ansy - yo1);
	
	// cout << fixed << setprecision(10) << ans << endl;
	printf("%.10Lf\n", ans);
	
}

signed main() {
	// ios::sync_with_stdio(0);
	// cin.tie(0);
	
	int t = 1;
	t = read();
	while(t--) {
		work();
	}
	
	return 0;
}
