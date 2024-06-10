#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;


void work() {
    string L, R;
    cin >> L >> R;

    int n = max(L.size(), R.size());
    int ans = 0;

    vector<int> a(n + 1);
    vector<int> b(n + 1);
    for(int i = n, j = L.size() - 1; j >= 0; i--, j--) {
        a[i] = L[j] - '0';
    }
    for(int i = n, j = R.size() - 1; j >= 0; i--, j--) {
        b[i] = R[j] - '0';
    }

    // for(int i = 1; i <= n; i++) cout << a[i]; cout << endl;
    // for(int i = 1; i <= n; i++) cout << b[i]; cout << endl;

    int flag = false;
    for(int i = 1; i <= n; i++) {
        if(a[i] == b[i] && !flag) continue;
        if(!flag) {
            flag = true;
            ans += abs(a[i] - b[i]);
        } else {
            ans += 9;
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