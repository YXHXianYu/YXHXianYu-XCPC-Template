#include <bits/stdc++.h>
using namespace std;
#define int long long


void work() {

    int n, D;
    cin >> n >> D;

    auto cmp = [&](const pair<int,int>& a, const pair<int,int>& b) {
        if(a.first != b.first) return a.first > b.first;
        return a.second > b.second;
    };

    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> pq(cmp);

    for(int i = 1; i <= n; i++) {
        int a;
        cin >> a;
        pq.push({a, i});
    }

    int cnt = 0;
    int ans = 0;
    while(!pq.empty()) {
        auto pr = pq.top();
        pq.pop();

        // cout << " - " << pr.first << ", " << pr.second << endl;

        if(!cnt) {
            pq.push({pr.first + D, pr.second});
        }
        cnt ^= 1;
        ans = max(ans, pr.first);
    }

    cout << ans << endl;

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