#include <bits/stdc++.h>
using namespace std;
#define int long long

#define endl "\n"


void work() {

    int n, m, q;
    cin >> n >> m >> q;

    vector<vector<int>> pro(n + 2);
    vector<set<pair<int, int>>> res(m + 2);
    vector<map<int, int>> res_in(m + 2);
    vector<int> res_cnt(m + 2);

    while(q--) {
        int p, r;
        char opt;
        cin >> p >> opt;

        if(opt == 'L') {
            cin >> r;
            if(res[r].size() == 0) {
                pro[p].push_back(r);
                res[r].insert({++res_cnt[r], p});
                res_in[r][p] = res_cnt[r];
                cout << p << ": acquired: " << r << endl;
            } else if(res[r].begin()->second == p) {
                cout << p << ": already acquired: " << r << endl;
            } else {
                // waiting
                int haveWaiting = res_in[r].count(p) > 0;
                if(haveWaiting) {
                    cout << p << ": already in pending: " << r << endl;
                } else {
                    pro[p].push_back(r);
                    res[r].insert({++res_cnt[r], p});
                    res_in[r][p] = res_cnt[r];
                    cout << p << ": pending: " << r << endl;
                }
            }
        } else if(opt == 'E') {
            cout << p << ": exiting" << endl;
            for(auto it = pro[p].rbegin(); it != pro[p].rend(); it++) {
                r = *it;
                if(res[r].begin()->second == p) {
                    res_in[r].erase(p);
                    res[r].erase(res[r].begin());
                    cout << p << ": releasing: " << r << endl;
                    if(res[r].empty())
                        cout << r << ": no pending processes" << endl;
                    else
                        cout << res[r].begin()->second << ": acquired: " << r << endl;
                } else {
                    int haveWaiting = res_in[r].count(p) > 0;
                    if(haveWaiting) {
                        res[r].erase({res_in[r].at(p), p});
                        res_in[r].erase(p);
                        cout << p << ": exit without acquiring: " << r << endl;
                    } else {
                        // TODO: 如果多次申请，则释放时要做什么？
                    }
                }
            }
        } else {
            assert(false);
        }
    }
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