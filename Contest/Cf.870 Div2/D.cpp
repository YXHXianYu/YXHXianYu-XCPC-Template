#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 1e5 + 10;
const int maxlog = 20;

int n;
int a[maxn];
int b[maxn];
int c[maxn];

int sta[maxlog][maxn];
int stc[maxlog][maxn];

int querya(int L, int R) {
	int k = log2(R - L + 1);
	return max(sta[k][L], sta[k][R-(1<<k)+1]);
}

int queryc(int L, int R) {
	int k = log2(R - L + 1);
	return max(stc[k][L], stc[k][R-(1<<k)+1]);
}

void work() {
	
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> b[i];
	
	for(int i = 1; i <= n; i++) a[i] = b[i] + i;
	for(int i = 1; i <= n; i++) c[i] = b[i] - i;
	
	int lim = log2(n);
	
	for(int i = 1; i <= n; i++) sta[0][i] = a[i];
	for(int k = 1; k <= lim; k++) {
		int lim2 = n - (1 << k) + 1;
		for(int i = 1; i <= lim2; i++) {
			sta[k][i] = max(sta[k - 1][i], sta[k - 1][i + (1 << k - 1)]);
		}
	}
	
	for(int i = 1; i <= n; i++) stc[0][i] = c[i];
	for(int k = 1; k <= lim; k++) {
		int lim2 = n - (1 << k) + 1;
		for(int i = 1; i <= lim2; i++) {
			stc[k][i] = max(stc[k - 1][i], stc[k - 1][i + (1 << k - 1)]);
		}
	}
	
	int ans = 0;
	for(int i = 2; i < n; i++) {
		int v1 = querya(1, i - 1);
		int v3 = queryc(i + 1, n);
		ans = max(ans, v1 + b[i] + v3);
	}
	
	cout << ans << endl;
	
	
	
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
