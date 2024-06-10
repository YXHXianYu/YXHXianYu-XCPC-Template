#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;

int n;
int a[maxn];

void work() {
	
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> a[i];
	
	int i, j;
	for(i = 1, j = n; i < j; i++, j--) {
		if(a[i] != a[j]) {
			break;
		}
	}
	
	if(i >= j) {
		cout << 0 << endl;
		return;
	}
	
	int gcd = abs(a[1] - a[n]);
	for(i = 2, j = n - 1; i < j; i++, j--) {
		if(gcd == 0) { 
			gcd = abs(a[i] - a[j]);
		} else {
			gcd = __gcd(gcd, abs(a[i] - a[j]));
		}
	}
	
	cout << gcd << endl;
	
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
