#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 6e5 + 10;

int n;
int a[maxn];

int f[maxn]; // f[i] <= 2
int g[maxn];
int h[maxn];

void work() {
	
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> a[i];
	
	g[n + 1] = 0; 
	if(a[n] == 0) {
		g[n] = 1;
	} else {
		g[n] = 0;
	}
	
	h[n] = 1;
	
	int mx = g[n];
	for(int i = n - 1; i >= 1; i--) {
		
		if(i + a[i] + 1 == n + 1) {
			g[i] = 1;
		} else if(i + a[i] + 1 > (n + 1)) {
			g[i] = 0;
		} else if(g[i + a[i] + 1] > 0) {
			g[i] = g[i + a[i] + 1] + 1;
		} else {
			g[i] = 0;
		}
		
		h[i] = mx + 1;
		if(i + a[i] + 1 <= n && h[i + a[i] + 1] > 0) {
			h[i] = max(h[i], h[i + a[i] + 1] + 1);
		}
		
		if(g[i + 1] == a[i]) {
			f[i] = 0;
		} else if(g[i + 1] > 0) {
			f[i] = 1;
		} else if(mx >= a[i] - 1) {
			f[i] = 1;
		} else if(h[i + 1] >= a[i]) {
			f[i] = 1;
		} else {
			f[i] = 2;
		}
		
		mx = max(mx, g[i]);
	}
	
	for(int i = 1; i < n; i++) {
		cout << f[i] << " ";
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
