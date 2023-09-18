#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;

int n;
map<int, int> L;
map<int, int> R;
map<int, int> Both;
set<int> f;

void work() {
    cin >> n;
    int x;
    char y;
    int num;
    int sum = 0;
    for(int i = 1; i <= n; i++) {
        cin >> x >> y >> num;
        if(y == 'L') {
            L[x] += num;
        } else if(y == 'R') {
            R[x] += num;
        } else if(y == '*') {
            Both[x] += num;
        }
        f.insert(x);
        sum += num;
    }

    int ans = 0;
    for(auto x: f) {
        int yL = 0;
        int yR = 0;
        int yBoth = 0;
        if(L.count(x) != 0) {
            yL = L[x];
        }
        if(R.count(x) != 0) {
            yR = R[x];
        }
        if(Both.count(x) != 0) {
            yBoth = Both[x];
        }

        if(yL != 0 || yR != 0) {
            ans += max(yL, yR);
        } else if(yBoth != 0) {
            ans += 1;
        }
    }
    
    if(ans == sum) {
        cout << -1 << endl;
    } else {
        cout << ans + 1 << endl;
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
