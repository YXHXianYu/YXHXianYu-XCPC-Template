#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;

int n, k;
char s[maxn];
int a[maxn];

vector<int> ans;
vector<int> tmp[10];

int d;
int q[10];

const int lim_bt = 6;
const int lim_up = 2;

void dfs(int x, int left) { // every seg length <= d + 2
//	cout << " - " << x << ", " << left << ", " << (k-x+2) << endl;
	if(left <= 0) return;
	
	int v = left / (k - x + 2);
	if(v > d + lim_up || (v == d + lim_up && (left % (k - x + 2) != 0))) return; // v <= d + 1 (guess)
	
	if(x > k) {
		q[x] = n;

		tmp[x][0] = max(tmp[x - 1][0], q[x] - q[x - 1]);
		tmp[x][1] = 0;
		for(int pos = q[x], j = 1; j <= tmp[x][0]; pos--, j++) {
			tmp[x][j + 1] = 0;
			if(pos > q[x - 1])
				tmp[x][j] += tmp[x - 1][j] + a[pos];
			else
				tmp[x][j] += tmp[x - 1][j];
			if(tmp[x][j] >= 10) {
				tmp[x][j + 1] += tmp[x][j] / 10;
				tmp[x][j] %= 10;
				tmp[x][0] = max(tmp[x][0], j + 1);
			}
		}
		
//		for(int i = tmp[x][0]; i >= 1; i--) {
//			cout << tmp[x][i];
//		}cout << endl;
		
		if(tmp[x][0] < ans[0] || ans[0] == -1) {
			ans = tmp[x];
		} else if(tmp[x][0] == ans[0]) {
			for(int i = tmp[x][0]; i >= 1; i--) {
				if(tmp[x][i] < ans[i]) {
					ans = tmp[x];
					break;
				} else if(tmp[x][i] > ans[i]) {
					break;
				}
			}
		}
		
		return;
	}
	
	for(int i = max(1ll, d - lim_bt); i <= d + lim_up; i++) {
		if(ans[0] != -1 && i > ans[0]) continue;
		q[x] = q[x - 1] + i;
		if(ans[0] != -1 && i == ans[0] && a[q[x - 1] + 1] > ans[ans[0]]) continue;
		
//		for(int i = tmp[x-1][0]; i >= 1; i--) {
//			cout << tmp[x-1][i];
//		}cout << " + ";
//		
//		for(int i = q[x-1]+1; i <= q[x]; i++) {
//			cout << a[i];
//		}cout << " = ";
//		
		tmp[x][0] = max(tmp[x - 1][0], q[x] - q[x - 1]);
		tmp[x][1] = 0;
		for(int pos = q[x], j = 1; j <= tmp[x][0]; pos--, j++) {
			tmp[x][j + 1] = 0;
			if(pos > q[x - 1])
				tmp[x][j] += tmp[x - 1][j] + a[pos];
			else
				tmp[x][j] += tmp[x - 1][j];
			if(tmp[x][j] >= 10) {
				tmp[x][j + 1] += tmp[x][j] / 10;
				tmp[x][j] %= 10;
				tmp[x][0] = max(tmp[x][0], j + 1);
			}
		}
		
		if(ans[0] != -1 && tmp[x][0] > ans[0]) continue;
		if(ans[0] != -1 && tmp[x][0] == ans[0]) {
			int j, lim;
			for(j = tmp[x][0], lim = max(tmp[x][0] - 3, 1ll); j >= lim; j--) {
				if(tmp[x][j] > ans[j]) {
					break;
				} else if(tmp[x][j] < ans[j]) {
					j = lim - 1;
					break;
				}
			}
			if(j >= lim) continue;
		}
		
		dfs(x + 1, left - i);
	}
}


void work() {
	
	cin >> n >> k;
	cin >> (s + 1);
	for(int i = 1; i <= n; i++) a[i] = s[i] - '0';
	
	// a[i] in [1, 9]
	
	d = n / (k + 1);
	
	ans.resize(n);
	ans[0] = -1;
	for(int i = 0; i <= k + 1; i++) tmp[i].resize(n);
	
	dfs(1, n);
	
	for(int i = ans[0]; i >= 1; i--) cout << ans[i]; cout << endl;
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
//	freopen("F2.in", "r", stdin);
	
	int t = 1;
	cin >> t;
	while(t--) {
		work();
	}
	
	return 0;
}
