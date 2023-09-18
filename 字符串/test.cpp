#include<bits/stdc++.h>
using namespace std;
typedef long long LL;

const int M = 26;

struct SAM {
    struct Node {
        int len, link;
        int nxt[M];
    };
    vector<Node> t;
    vector<int> f;
    int N, lst;

    SAM(int n = 0) { init(n); }
    void init(int n) {
        t.resize(2 * n);
        f.resize(2 * n);
        N = 1;
        t[N] = t[0];
        lst = N;
    }

    void add(char c) {
        c -= 'a';

        int x = ++N;
        t[N] = t[0];
        t[N].len = t[lst].len + 1;

        f[x] += 1;

        int p = lst;
        lst = x;
        for(; p && !t[p].nxt[c]; p = t[p].link) t[p].nxt[c] = x;

        if(!p) {
            t[x].link = 1;
        } else {
            int q = t[p].nxt[c];
            if(t[p].len + 1 == t[q].len) {
                t[x].link = q;
            } else {
                int cl = ++N;
                t[cl] = t[q];
                t[cl].len = t[p].len + 1;
                for(; p && t[p].nxt[c] == q; p = t[p].link) t[p].nxt[c] = cl;
                t[q].link = t[x].link = cl;
            }
        }
    }

    LL solve() {
        vector<int> a;
        for(int i = 2; i <= N; i++) a.push_back(i);

        sort(a.begin(), a.end(), [&](int a, int b) {
            return t[a].len > t[b].len;
        });

        LL ans = 0;
        for(auto i: a) {
            if(f[i] >= 2) ans = max(ans, 1ll * f[i] * t[i].len);
            f[t[i].link] += f[i];
        }

        return ans;
    }
};

void work() {
    string s;
    cin >> s;
    int n = s.size();
    s = " " + s;

    SAM sam(n);
    for(int i = 1; i <= n; i++) {
        sam.add(s[i]);
    }

    cout << sam.N << endl;

    cout << sam.solve() << endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t = 1;
    while(t--) {
        work();
    }

    return 0;
}
