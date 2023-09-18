#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 3e5 + 10;


void work() {

    int n;
    cin >> n;
    
    vector<int> a(n + 2);
    for(int i = 1; i <= n; i++) cin >> a[i];

    vector<int> b(n + 2);
    for(int i = 1; i <= n; i++) b[i] = a[i];
    sort(b.begin() + 1, b.begin() + n + 1);
    map<int, int> g;
    for(int i = 1; i <= n; i++) g[b[i]] = i;
    for(int i = 1; i <= n; i++) a[i] = g[a[i]];

    for(int i = 1; i <= n; i++) b[a[i]] = i;

    vector<int> f(n + 2);
    for(int i = 1; i <= n; i++) f[i] = 1;

    vector<vector<int>> h(n + 2);
    for(int i = 1; i <= n; i++) {
        h[i].resize(n + 2);
        for(int j = 1; j <= n; j++) h[i][j] = 0;
    }


    auto calc = [&](int L, int R) {
        return (L + R) * (R - L + 1) / 2;
    };

    int ans = 0;
    for(int i = 1; i <= n; i++) {

        int sum = 0;
        int cnt = 0;
        int lst = 0;
        for(int j = b[i] - 1; j >= 1; j--) {
            if(f[j] > 0) {
                cnt = b[i] - j;
                lst = 0;
                h[j][b[i]] = cnt;
            } else {
                lst += 1;
                h[j][b[i]] = cnt + h[j][j+lst-1];
                // cout << "(" << j << ", " << lst << ", " << h[j][j+lst-1] << ")" << endl;
            }
            sum += h[j][b[i]];

            // cout << b[i] << ", " << j << ": " << h[j][b[i]] << endl;
        }

        ans += sum;

        // cout << i << ": " << sum << endl;

        f[b[i]] = 0;
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