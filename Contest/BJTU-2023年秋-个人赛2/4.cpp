#include<bits/stdc++.h>
using namespace std;
#define int long long

void work() {
    int n;
    cin >> n;

    if(n & 1) {
        cout << 7;
        n -= 3;
    } else {
        cout << 1;
        n -= 2;
    }

    while(n >= 2) cout << 1, n -= 2;
    cout << endl;


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