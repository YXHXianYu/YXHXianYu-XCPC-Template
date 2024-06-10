#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;

int n;
int a[maxn];
int b[maxn];



void work() {
	
	cin >> n;
	for(int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	for(int i = 1; i <= n; i++) {
		cin >> b[i];
	}
	
	int mxN = max(a[n], b[n]);
	int mnN = min(a[n], b[n]);
	for(int i = 1; i < n; i++) {
		int mx = max(a[i], b[i]);
		int mn = min(a[i], b[i]);
		if(mx <= mxN && mn <= mnN) {
			continue;
		}
		cout << "No" << endl;
		return;
	}
	
	cout << "Yes" << endl;
	return;
	
	
	
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
