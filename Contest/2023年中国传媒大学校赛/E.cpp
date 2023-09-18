#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;

int n = 3;
int m = 3;
int a[10][10];
int b[10][10];

int ans = 0;
int q[20];
void dfs(int k) {
    if(k > 9) {

        for(int i = 1; i <= 3; i++) {
            for(int j = 1; j <= 3; j++) {
                b[i][j] = a[i][j];
            }
        }
        if(q[1] == 1) {b[1][1] ^= 1; b[1][2] ^= 1; b[2][1] ^= 1;}
        if(q[2] == 1) {b[1][1] ^= 1; b[1][2] ^= 1; b[1][3] ^= 1; b[2][2] ^= 1;}
        if(q[3] == 1) {b[1][2] ^= 1; b[1][3] ^= 1; b[2][3] ^= 1;}

        if(q[4] == 1) {b[2][1] ^= 1; b[2][2] ^= 1; b[1][1] ^= 1; b[3][1] ^= 1;}
        if(q[5] == 1) {b[2][1] ^= 1; b[2][2] ^= 1; b[2][3] ^= 1; b[1][2] ^= 1; b[3][2] ^= 1;}
        if(q[6] == 1) {b[2][2] ^= 1; b[2][3] ^= 1; b[1][3] ^= 1; b[3][3] ^= 1;}

        if(q[7] == 1) {b[3][1] ^= 1; b[3][2] ^= 1; b[2][1] ^= 1;}
        if(q[8] == 1) {b[3][1] ^= 1; b[3][2] ^= 1; b[3][3] ^= 1; b[2][2] ^= 1;}
        if(q[9] == 1) {b[3][2] ^= 1; b[3][3] ^= 1; b[2][3] ^= 1;}

        for(int i = 1; i <= 3; i++) {
            for(int j = 1; j <= 3; j++) {
                if(b[i][j] != 0) {
                    return;
                }
            }
        }

        int cnt = 0;
        for(int i = 1; i <= 9; i++) if(q[i] == 1) cnt++;
        if(ans == -1 || ans > cnt) {
            ans = cnt;
        }

        return;
    }
    
    q[k] = 1;
    dfs(k + 1);
    q[k] = 0;
    dfs(k + 1);
}

void work() {
    for(int i = 1; i <= 3; i++) {
        for(int j = 1; j <= 3; j++) {
            cin >> a[i][j];
        }
    }
    ans = -1;
    dfs(1);
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
