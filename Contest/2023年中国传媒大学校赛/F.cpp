#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 1e5 + 10;

int n;

pair<pair<int, int>, int> a[maxn];
int b[maxn];

int lim;
int stMin[18][maxn];
int stMax[18][maxn];

int queryMin(int l, int r) {
    int k = log2(r - l + 1);
    return min(stMin[k][l], stMin[k][r-(1<<k)+1]);
}
int queryMax(int l, int r) {
    int k = log2(r - l + 1);
    return max(stMax[k][l], stMax[k][r-(1<<k)+1]);
}

int L[maxn];
int R[maxn];

void work() {

    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> a[i].first.first >> a[i].first.second;
        a[i].second = i;
    }
    sort(a + 1, a + n + 1);

    for(int i = 1; i <= n; i++) {
        b[a[i].second] = i;
    }

    // build st
    lim = log2(n);
    for(int i = 1; i <= n; i++) {
        stMin[0][i] = stMax[0][i] = a[i].first.second;
    }
    for(int k = 1; k <= lim; k++) {
        for(int i = 1; i <= n; i++) {
            stMax[k][i] = max(stMax[k - 1][i], stMax[k - 1][i + (1 << (k - 1))]);
            stMin[k][i] = min(stMin[k - 1][i], stMin[k - 1][i + (1 << (k - 1))]);
        }
    }

    L[1] = 1;
    for(int i = 2; i <= n; i++) {
        if(a[i - 1].first.first == a[i].first.first)
            L[i] = L[i - 1];
        else
            L[i] = i;
    }
    R[n] = n;
    for(int i = n - 1; i >= 1; i--) {
        if(a[i].first.first == a[i + 1].first.first)
            R[i] = R[i + 1];
        else
            R[i] = i;
    }

    int q;
    cin >> q;
    while(q--) {
        int A, B;
        cin >> A >> B;

        A = b[A];
        B = b[B];
        if(a[A].first.first >= a[B].first.first) {
            cout << 0 << endl;
            continue;
        }

        A = L[A];
        B = R[B];

        int xa = a[A].first.first;
        int xb = a[B].first.first;
        int yMax = queryMax(A, B);
        int yMin = queryMin(A, B);

        int ans = (xb - xa) * (yMax - yMin);
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
