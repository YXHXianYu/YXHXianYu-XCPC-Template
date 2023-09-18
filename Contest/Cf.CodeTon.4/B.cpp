#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;

int n;

int a[maxn];

void work() {
	
	cin >> n;
	
	// <= 40 times
	
	if(~n&1) {
		cout << -1 << endl;
		return;
	}
	
	int m = 0;
	int x = n;
	while(x) {
		a[++m] = x & 1;
		x >>= 1;
	}
	
	if(m > 41) {
		cout << -1 << endl;
		return;
	}
	
	cout << m - 1<< endl;
	for(int i = m; i > 1; i--) {
		cout << a[i] + 1 << " ";
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
