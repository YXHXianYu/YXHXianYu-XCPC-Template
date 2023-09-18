#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 300 + 10;
const int maxm = 200000 + 10;
const int MOD = 998244353;

int n;
int a[maxn];

const int M = 90000;
int f[2][maxm];

void work() {
	
	cin >> n;
	for(int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	
	int lim = M << 1;
	for(int i = 0; i <= lim; i++) f[0][i] = f[1][i] = 0;
	
	int S = 0, T;
	
	// f[S][y] => f[T][y + a[i]]
	// f[S][y] => f[T][y - a[i]]
	
	f[S][M] = 1;
	
	for(int i = 2; i < n; i++) {
		T = S ^ 1;
		for(int j = -M; j <= M; j++) {
			if(f[S][M + j] == 0) continue;
			
			f[T][M + j + a[i]] = (f[T][M + j + a[i]] + f[S][M + j]) % MOD;
			if(j - a[i] != 0) f[T][M + j - a[i]] = (f[T][M + j - a[i]] + f[S][M + j]) % MOD;
			
			f[S][M + j] = 0;
		}
		S ^= 1;
	
//		for(int j = -5; j <= 5; j++) {
//			if(j == 0) cout << "(" << f[S][M + j] << ") ";
//			else cout << f[S][M + j] << " ";
//		}
//		cout << endl;
	}
	
	int ans = 0;
	for(int j = -M; j <= M; j++) ans = (ans + f[S][M + j]) % MOD;
	
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
