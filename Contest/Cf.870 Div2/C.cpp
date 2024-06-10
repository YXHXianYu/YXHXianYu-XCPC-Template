#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;

int n, m;

void work() {
	
	cin >> n >> m;
	
	if(n == 1) {
		cout << "YES" << endl;
		return;
	}
	
	if(n <= m) {
		cout << "NO" << endl;
		return;
	}
	
	for(int i = 2, lim = sqrt(n); i <= lim; i++) {
		if(n % i == 0) {
			if(i <= m) {
				cout << "NO" << endl;
				return;
			}
		}
	}
	
	cout << "YES" << endl;
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
