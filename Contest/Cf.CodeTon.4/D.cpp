#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;
const int INF = 1000000000000000000LL;

//#define endl "\n"

int q;

void work() {
	
	cin >> q;
	
	int opt, a, b, n;
	
	int mn = 1;
	int mx = INF;
	
	while(q--) {
		cin >> opt;
		if(opt == 1) {
			cin >> a >> b >> n;
			
			int d = a - b;
			if(n == 1) {
				int mx1 = min(mx, a),
					mn1 = mn;
				if(mn1 > mx1) {
					cout << 0 << " ";
					continue;
				}
				mx = mx1;
			} else {
				int v = d * (n - 1) + a;
				int mx1 = min(mx, v),
					mn1 = max(mn, v - d + 1);
				if(mn1 > mx1) { // ignore it
					cout << 0 << " ";
					continue;
				}
				mx = mx1;
				mn = mn1;
			}
			cout << 1 << " "; // adopt
			
		} else if(opt == 2) {
			cin >> a >> b;
			int d = a - b;
			if(a >= mx) {
				cout << 1 << " ";
				continue;
			} else {
				int mnv = (mn - a - 1) / d + 2;
				if(a >= mn) mnv = 1;
				int mxv = (mx - a - 1) / d + 2;
				if(mnv == mxv) {
					cout << mxv << " ";
					continue;
				} else {
					cout << -1 << " ";
					continue;
				}
			}
		} else {
			assert(false);
		}
	}
	cout << endl;
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
