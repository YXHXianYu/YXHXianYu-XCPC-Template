#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 4e5 + 10;

int n;
int a[maxn];
int b[maxn];

int f[maxn];

void work() {
	
	cin >> n;
	for(int i = 1; i <= n; i++) {
		cin >> a[i] >> b[i];
	}
	
	for(int i = 1; i <= n; i++) {
		f[i] = a[i] * b[i];
	}
	
	int ans = 1;
	for(int i = 2; i <= n; i++) {
		int gcd = __gcd(f[i - 1], f[i]);
		if(gcd >= b[i - 1] && gcd >= b[i] && gcd % b[i - 1] == 0 && gcd % b[i] == 0) {
			f[i] = gcd;
			b[i] = b[i - 1] * b[i] / __gcd(b[i - 1], b[i]);
		} else {
			ans++;
		}
	}
	
	cout << ans << endl;
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
