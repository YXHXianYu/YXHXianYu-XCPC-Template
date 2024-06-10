#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e2 + 2;

int n, m;
char s[maxn][maxn];
int a[maxn][maxn];

int v[maxn][maxn];

void work() {

    for(int i = 1; i <= n; i++) {
        cin >> (s[i] + 1);
        for(int j = 1; j <= m; j++) {
            a[i][j] = s[i][j] == '#' ? 1 : 0;
        }
    }
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            v[i][j] = 0;
        }
    }

    int mx[4] = {0, 0, 1, -1};
    int my[4] = {1, -1, 0, 0};

    auto bfs1 = [&](int stx, int sty, int type) {
        queue<pair<int, int>> q;
        
        q.push({stx, sty});
        v[stx][sty] = 1;
        while(!q.empty()) {
            int x = q.front().first;
            int y = q.front().second;
            q.pop();
            for(int i = 0; i <= 3; i++) {
                int cx = x + mx[i];
                int cy = y + my[i];
                if(cx < 1 || cx > n || cy < 1 || cy > m) continue;
                if(v[cx][cy]) continue;
                
                if(a[cx][cy] == type) {
                    q.push({cx, cy});
                    v[cx][cy] = 1;
                }
            }
        }
    };

    int ansA = 0;
    int ansB = 0;
    int ansC = 0;

    auto bfs2 = [&](int stx, int sty, int type) {
        queue<pair<int, int>> q;
        int cnt = 0; 
        q.push({stx, sty});
        v[stx][sty] = 1;
        while(!q.empty()) {
            int x = q.front().first;
            int y = q.front().second;
            q.pop();
            for(int i = 0; i <= 3; i++) {
                int cx = x + mx[i];
                int cy = y + my[i];
                if(cx < 1 || cx > n || cy < 1 || cy > m) continue;
                if(v[cx][cy]) continue;
                
                if(a[cx][cy] == type) {
                    q.push({cx, cy});
                    v[cx][cy] = 1;
                } else {
                    bfs1(cx, cy, type ^ 1);
                    cnt++;
                }
            }
        }
        return cnt;
    };

    bfs1(1, 1, 0);

    // for(int i = 1; i <= n; i++) {
    //     for(int j = 1; j <= m; j++)
    //         cout << v[i][j];
    //     cout << endl;
    // }

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            if(v[i][j]) continue;
            // assert(a[i][j] == 1);
            int res = bfs2(i, j, 1);
            if(res == 0) ansC++;
            else if(res == 1) ansA++;
            else if(res == 2) ansB++;
            // cout << "(" << i << ", " << j << ")" << ": " << res << endl;
        }
    }

    cout << ansA << " " << ansB << " " << ansC << endl;

    


}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    while(cin >> n >> m) {
        work();
    }

    return 0;
}