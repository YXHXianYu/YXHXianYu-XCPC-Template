#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;

int n;

void work() {
    cin >> n;
    if(n == 0) {
        cout << "0" << endl;
        return;
    }
    cout << "0.";
    for(int i = 1; i <= n; i++) {
        cout << "0";
    }
    cout << endl;
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
