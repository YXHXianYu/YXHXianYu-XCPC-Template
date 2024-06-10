#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 5005;
const int maxm2 = 1e4;
const int MOD = 1e9 + 7;

int m, n;
int f[2][maxm2];

int pow3[20];
vector<int> g;
vector<int> e[maxm2];

void dfs2(int k, int cnt, int lst, int lstLine) {
    if(k > m) {
        e[lstLine].push_back(cnt);
        return;
    }
    if(lst != 0 && ((lstLine/pow3[k-1])%3 != 0)) dfs2(k + 1, cnt + pow3[k - 1] * 0, 0, lstLine);
    if(lst != 1 && ((lstLine/pow3[k-1])%3 != 1)) dfs2(k + 1, cnt + pow3[k - 1] * 1, 1, lstLine);
    if(lst != 2 && ((lstLine/pow3[k-1])%3 != 2)) dfs2(k + 1, cnt + pow3[k - 1] * 2, 2, lstLine);
}

void dfs(int k, int cnt, int lst) {
    if(k > m) {
        g.push_back(cnt);
        dfs2(1, 0, -1, cnt);
        return;
    }
    if(lst != 0) dfs(k + 1, cnt + pow3[k - 1] * 0, 0);
    if(lst != 1) dfs(k + 1, cnt + pow3[k - 1] * 1, 1);
    if(lst != 2) dfs(k + 1, cnt + pow3[k - 1] * 2, 2);
}

void work() {
    
    cin >> m >> n;

    pow3[0] = 1;
    for(int i = 1; i <= m; i++) pow3[i] = pow3[i - 1] * 3;

    dfs(1, 0, -1);

    // int tmp_sum = 0;
    // for(auto i: g) {
    //     tmp_sum += e[i].size();
    // }
    // cout << tmp_sum << endl;

    int S = 0;
    for(auto j: g) {
        f[S][j] = 1;
    }

    for(int i = 2; i <= n; i++) {
        int T = S ^ 1;
        for(auto j: g) {
            f[T][j] = 0;
        }
        for(auto j: g) {
            // S -> j
            for(auto k: e[j]) {
                // T -> k
                f[T][k] = (f[T][k] + f[S][j]) % MOD;
            }
        }
        S ^= 1;
    }

    int ans = 0;
    for(auto j: g) {
        ans = (ans + f[S][j]) % MOD;
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
