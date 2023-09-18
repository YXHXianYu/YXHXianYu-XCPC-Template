#include <bits/stdc++.h>
using namespace std;
#define int long long


void work() {

    string str;
    cin >> str;

    vector<std::pair<int, string>> a;
    int cnt = 0;

    cnt++;
    a.push_back({0, ""});
    for(int i = 0; i < str.length(); i++) {
        if(str[i] >= '0' && str[i] <= '9') {
            if(a[cnt - 1].second == "")
                a[cnt - 1].first = a[cnt - 1].first * 10 + str[i] - '0';
            else {
                cnt++;
                a.push_back({str[i] - '0', ""});
            }
        } else {
            a[cnt - 1].second += str[i];
        }
    }

    for(auto pr: a) {
        for(int i = 1; i <= pr.first; i++) {
            cout << pr.second;
        }
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