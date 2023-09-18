#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;

int n, m;
int a[maxn];
int b[maxn];

bool check(int x) {
    int cnt = 0;
    for(int i = 1; i <= n && cnt < m; i++) {
        int t = x / (a[i] + b[i]);
        int d = x % (a[i] + b[i]);

        cnt += t * a[i] + min(d, a[i]);
    }
    return cnt >= m;
}

void work() {
	
    cin >> n >> m;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= n; i++) {
        cin >> b[i];
    }

    int l = 1, r = 1LL << 60;
    int ans = 0;
    while(l <= r) {
        int mid = l + r >> 1;
        if(check(mid)) {
            r = mid - 1;
            ans = mid;
        } else {
            l = mid + 1;
        }
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
