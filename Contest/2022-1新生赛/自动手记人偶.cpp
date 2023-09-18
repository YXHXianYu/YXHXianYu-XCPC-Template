#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;

int n;
int s[maxn];

void work() {
	
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> s[i];

	map<int, int> f;
	int ans = 0;
	for(int i = 1; i <= n; i++) {
		if(f.count(s[i]) == 0) {
			f[s[i]] = 1;
			ans += s[i];
		}
	}
	ans <<= 1;
	cout << ans << endl;

}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int t = 1;
	// cin >> t;
	while(t--) {
		work();
	}
	
	return 0;
}
