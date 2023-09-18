#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;

int n, k, s;
int a[maxn];
int b[maxn];
int cnt[maxn];

void work() {
    cin >> n >> k >> s;
    for(int i = 1; i <= s; i++) {
        cin >> a[i] >> b[i];
        cnt[a[i]] += b[i];
    }
    int ans = 0;
    for(int i = 1; i <= n; i++) {
        if(cnt[i] < k)
            ans++;
    }
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
