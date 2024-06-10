#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;


void work() {
    
    int t = 100000;
    srand(time(0));

    auto random = [](int L, int R) {
        return rand() % (R - L + 1) + L;
    };

    freopen("1.txt", "w", stdout);

    cout << t << endl;
    for(int T = 1; T <= t; T++) {
        int n = 20;
        vector<int> a(n + 1);
        for(int i = 1; i <= n; i++) a[i] = random(-20, 20);
        cout << n << endl;
        for(int i = 1; i <= n; i++) cout << a[i] << " ";
        cout << endl;
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