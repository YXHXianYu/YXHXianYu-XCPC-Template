#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'


void work() {
	int a[3], b[3];
	cin >> a[0] >> a[1] >> a[2];
	cin >> b[0] >> b[1] >> b[2];

	a[1] += a[0];
	a[2] += a[1];

	b[1] += b[0];
	b[2] += b[1];

	int ans = 0;
	for(int i = 1; i <= 10; i++) {
		for(int j = 1; j <= 10; j++) {
			int t0 = 0;
			int t1 = 0;
			if(i <= a[0]) t0 = 0;
			else if(i <= a[1]) t0 = 1;
			else t0 = 2;
			if(j <= b[0]) t1 = 0;
			else if(j <= b[1]) t1 = 1;
			else t1 = 2;
			if(t0 == t1) ans++;
		}
	}

	if(ans == 100) {
		cout << "Sorry,NoBruteForce" << endl;
	} else {
		double ansT = 1.0 * ans / 100.0;
		ansT = 1 / (1 - ansT);
		cout << fixed << setprecision(9) << ansT << endl;
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
