#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 3e5 + 10;

int n;
int a[maxn]; 

void work() {
	
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> a[i];
	
	if(n & 1) {
		cout << "YES" << endl;
		return;
	}
	
	for(int i = 2; i < n; i++) {
		int d = a[i - 1] - a[i];
		a[i] += d;
		a[i + 1] += d;
	}
	
//	for(int i = 1; i <= n; i++) cout << a[i] << " "; cout << endl;
	
	if(a[n - 1] > a[n]) {
		cout << "NO" << endl;
		return;
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
