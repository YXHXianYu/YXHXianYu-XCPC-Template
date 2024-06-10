#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;


void work() {
	int n, x;
	cin >> n >> x;

	vector<int> a(n + 1);
	vector<int> b(n + 1);
	vector<int> c(n + 1);
	for(int i = 1; i <= n; i++) cin >> a[i];
	for(int i = 1; i <= n; i++) cin >> b[i];
	for(int i = 1; i <= n; i++) cin >> c[i];

	vector<int> A(n + 1);
	vector<int> B(n + 1);
	vector<int> C(n + 1);
	for(int i = 1; i <= n; i++) A[i] = A[i - 1] | a[i];
	for(int i = 1; i <= n; i++) B[i] = B[i - 1] | b[i];
	for(int i = 1; i <= n; i++) C[i] = C[i - 1] | c[i];

	int ta = 0;
	int tb = 0;
	int tc = 0;
	for(int i = 1; i <= n; i++) {
		if((A[i] | x) <= x) {
			ta = i;
		} else {
			break;
		}
	}
	for(int i = 1; i <= n; i++) {
		if((B[i] | x) <= x) {
			tb = i;
		} else {
			break;
		}
	}
	for(int i = 1; i <= n; i++) {
		if((C[i] | x) <= x) {
			tc = i;
		} else {
			break;
		}
	}

	int ans = A[ta] | B[tb] | C[tc];
	if(ans == x) {
		cout << "Yes" << endl;
	} else {
		cout << "No" << endl;
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
