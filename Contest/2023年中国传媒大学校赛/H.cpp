#include<bits/stdc++.h>
using namespace std;
#define int long long
#define DBL double
const int maxn = 1e4 + 10;

int n, k;
DBL m;

struct Node {
    int r;
    DBL p;
    DBL e;
} a[maxn];

DBL f[11][1001];

void work() {

    cin >> n >> k >> m;
    for(int i = 1; i <= n; i++) {
        cin >> a[i].r >> a[i].p;
        a[i].e = a[i].r * a[i].p;
    }

    for(int j = 0; j <= k; j++) {
        for(int v = 0; v <= 1000; v++) {
            f[j][v] = -1;
        }
    }
    f[0][0] = 0;

    for(int i = 1; i <= n; i++) {
        for(int j = k; j >= 1; j--) {
            for(int v = a[i].r; v <= 1000; v++) {
                if(f[j - 1][v - a[i].r] != -1) {
                    f[j][v] = max(f[j][v], f[j - 1][v - a[i].r] + a[i].e);
                }
            }
        }
    }

    int ans1 = 0;
    DBL ans2 = 0;
    for(int v = 1000; v >= 1; v--) {
        if(f[k][v] >= m) {
            ans1 = v;
            ans2 = f[k][v];
            break;
        }
    }
    cout << ans1 << " ";
    cout << fixed << setprecision(2) << ans2 << endl;
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
