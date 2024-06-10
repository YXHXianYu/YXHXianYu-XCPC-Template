#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;
const int INF = 1000000000000000000LL;

int n, c, d;
int a[maxn];

void work() {
	
	cin >> n >> c >> d;
	for(int i = 1; i <= n; i++) cin >> a[i];
	
	sort(a + 1, a + n + 1);
	
	int ans = INF;
	int cnt = 0;
	
	int j = 1;
	for(int i = 1; i <= n; i++) {
		while(a[j] < i && j <= n) {
			cnt += c; // remove
			j += 1;
		}
		if(j <= n && a[j] == i) {
			ans = min(ans, cnt + (n - j) * c); // remove left
			j += 1;
		} else {
			ans = min(ans, cnt + (n - j + 1) * c + d);
			cnt += d;
		}
	}
	int ed = n;
	for(; j <= n; j++) {
		if(a[j] == ed) {
			cnt += c;
			continue;
		}
		cnt += (a[j] - ed - 1) * d;
		ans = min(ans, cnt + (n - j) * c);
		ed = a[j];
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
