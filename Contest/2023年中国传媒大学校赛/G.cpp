#include<bits/stdc++.h>
using namespace std;
#define int long long
#define DBL double
const int maxn = 1e5 + 10;

int n, m, q;

struct Node {
    DBL p;
    int r;
    int id;
} a[maxn];

int b[maxn];
int c[maxn];

Node st[18][maxn];

void work() {
    
    cin >> n >> m >> q;

    for(int i = 1; i <= n; i++) {
        cin >> a[i].p >> a[i].r;
        a[i].id = i - 1;
    }

    sort(a + 1, a + n + 1, [&](const Node&a, const Node&b){
        return a.r < b.r;
    });

    for(int i = 1; i <= m; i++) cin >> b[i];
    sort(b + 1, b + m + 1);

    for(int i = 1; i <= n; i++) {
        c[i] = a[i].r;
    }

    for(int i = 1; i <= n; i++) {
        st[0][i].p = a[i].p;
        st[0][i].r = a[i].r;
        st[0][i].id = a[i].id;
    }
    int lim = log2(n);
    for(int k = 1; k <= lim; k++) {
        for(int i = 1, lim2 = n - (1 << k) + 1; i <= lim2; i++) {
            if(st[k - 1][i].p != st[k - 1][i + (1 << k - 1)].p) {
                if(st[k - 1][i].p > st[k - 1][i + (1 << k - 1)].p) {
                    st[k][i] = st[k - 1][i];
                } else {
                    st[k][i] = st[k - 1][i + (1 << k - 1)];
                }
            } else if(st[k - 1][i].r != st[k - 1][i + (1 << k - 1)].r) {
                if(st[k - 1][i].r > st[k - 1][i + (1 << k - 1)].r) {
                    st[k][i] = st[k - 1][i];
                } else {
                    st[k][i] = st[k - 1][i + (1 << k - 1)];
                }
            } else {
                if(st[k - 1][i].id < st[k - 1][i + (1 << k - 1)].id) {
                    st[k][i] = st[k - 1][i];
                } else {
                    st[k][i] = st[k - 1][i + (1 << k - 1)];
                }
            }
        }
    }

    while(q--) {
        int S, K;
        cin >> S >> K;
        K = m - K + 1;
        int tar = b[K];
        int delta = tar - S;

        int pos = lower_bound(c + 1, c + n + 1, delta) - c;

        // cout << "pos = " << pos << endl;

        if(pos > n) {
            cout << -1 << endl;
            continue;
        }

        int k = log2(n - pos + 1);
        int ans = 0;
        if(st[k][pos].p != st[k][n-(1<<k)+1].p) {
            if(st[k][pos].p > st[k][n-(1<<k)+1].p) {
                ans = st[k][pos].id;
            } else {
                ans = st[k][n-(1<<k)+1].id;
            }
        } else if(st[k][pos].r != st[k][n-(1<<k)+1].r) {
            if(st[k][pos].r > st[k][n-(1<<k)+1].r) {
                ans = st[k][pos].id;
            } else {
                ans = st[k][n-(1<<k)+1].id;
            }
        } else {
            if(st[k][pos].id < st[k][n-(1<<k)+1].id) {
                ans = st[k][pos].id;
            } else {
                ans = st[k][n-(1<<k)+1].id;
            }
        }
        cout << ans << endl;
    }

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
