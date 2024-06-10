#include <bits/stdc++.h>
using namespace std;
#define int long long


void work() {
    
    std::string str;
    int n;
    cin >> str;
    n = str.length();

    vector<int> a(n + 2);
    vector<int> s(n + 2);
    for(int i = 1; i <= n; i++) a[i] = str[i - 1] - 'a' + 1;
    for(int i = 1; i <= n; i++) s[i] = (s[i - 1] + a[i] - 1) % 4 + 1;

    vector<vector<int>> f(5);
    for(int i = 1; i <= n; i++) f[s[i]].push_back(i);

    // for(int i = 1; i <= n; i++) cout << s[i] << " "; cout << endl;

    vector<int> ans;

    for(int i = 1, lst; i <= n; i = lst + 1) {
        int pre = s[i - 1];
        for(int j = pre + 1; j <= pre + 4; j++) {
            int tar = (j - 1) % 4 + 1;
            auto it = f[tar].rbegin();
            if(it == f[tar].rend()) continue;
            if(*it < i) continue;
            lst = *it;
            break;
        }
        // cout << i << " - " << lst << endl;
        ans.push_back((s[lst] - pre + 3) % 4 + 1);     
    }

    for(const auto& i: ans) {
        cout << ((char) (i + 'a' - 1));
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