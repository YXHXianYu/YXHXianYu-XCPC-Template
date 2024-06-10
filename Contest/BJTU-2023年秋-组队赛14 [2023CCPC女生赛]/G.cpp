#include<bits/stdc++.h>
using namespace std;
#define int long long

struct Node {
    int H, A, B, C, D, E, W, cur;
};

void work() {
    int n, m, K;
    cin >> n >> m >> K;

    vector<Node> a(n);
    vector<Node> b(m);

    for(int i = 0; i < n; i++) {
        cin >> a[i].H >> a[i].A >> a[i].B >> a[i].C >> a[i].D >> a[i].E >> a[i].W;
    }
    for(int i = 0; i < m; i++) {
        cin >> b[i].H >> b[i].A >> b[i].B >> b[i].C >> b[i].D >> b[i].E >> b[i].W;
    }

    auto atk = [&](Node& a, Node& b) {
        int vP = max(0LL, a.A - b.C);
        int vM = max(0LL, a.B - b.D);
        int vW = (a.cur >= a.E ? a.W : 0LL);

        if(vP >= vM && vP >= vW) {
            b.H -= vP;
            a.cur += 1;
        } else if(vM >= vP && vM >= vW) {
            b.H -= vM;
            a.cur += 1;
        } else {
            assert(vW > vP && vW > vM);
            b.H -= vW;
            assert(a.cur >= a.E);
            a.cur -= a.E;
        }
    };

    vector<int> aQ(K + n + 1);
    vector<int> bQ(K + m + 1);

    int aTl = 0;
    int bTl = 0;

    for(int i = 0; i < n; i++) aQ[aTl++] = i;
    for(int i = 0; i < m; i++) bQ[bTl++] = i;

    int aHd = 0;
    int bHd = 0;

    for(int i = 1; i <= K; i++) {
        
        atk(a[aQ[aHd]], b[bQ[bHd]]);

        while(bHd < bTl && b[bQ[bHd]].H <= 0) bHd += 1;
        if(bHd == bTl) { cout << "Alice" << '\n'; return; }

        aQ[aTl++] = aQ[aHd];
        aHd++;

        atk(b[bQ[bHd]], a[aQ[aHd]]);

        while(aHd < aTl && a[aQ[aHd]].H <= 0) aHd += 1;
        if(aHd == aTl) { cout << "Bob" << '\n'; return; }

        bQ[bTl++] = bQ[bHd];
        bHd++;
    }

    cout << "Draw" << '\n';
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

/*
42 - 4 = 38

*/