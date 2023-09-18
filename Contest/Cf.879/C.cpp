#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;


void work() {
    int n;
    cin >> n;

    string A, B;
    cin >> A >> B;
    A = " " + A;
    B = " " + B;

    int ans1 = 0;
    for(int i = 1; i <= n; i++) {
        if(A[i] != B[i]) {
            ans1++;
        }
    }
    int ans2 = 0;
    for(int i = 1, j = n; i <= n; i++, j--) {
        if(A[i] != B[j]) {
            ans2++;
        }
    }

    int ans = 2 * n; // inf
    if(ans1 == 0) {
        ans = 0;
    } else if(ans1 & 1) {
        ans = min(ans, 2 * ans1 - 1);
    } else {
        ans = min(ans, 2 * ans1);
    }

    if(ans2 == 0) {
        ans = min(ans, 2ll);
    } else if(ans2 & 1) {
        ans = min(ans, 2 * ans2);
    } else {
        ans = min(ans, 2 * ans2 - 1);
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