#include<bits/stdc++.h>
using namespace std;
#define int long long

void work() {
    int n, a, b;
    cin >> n >> a >> b;

    for(int i = 1, j = 0; i <= n; i++, j = (j + 1) % b) {
        cout << ((char)('a' + j));
    }
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