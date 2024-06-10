#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;

int n, k;
char s[maxn];
int a[maxn];

vector<int> ans;

int d;
int q[10];

const int lim_bt = 2;
const int lim_up = 2;

void dfs(int x, int left) { // every seg length <= d + 2
//	cout << " - " << x << ", " << left << ", " << (k-x+2) << endl;
	if(left <= 0) return;
	
	int v = left / (k - x + 2);
	if(v > d + lim_up) return; // v <= d + 2 (guess)
	
	if(x > k) {
		q[k + 1] = n;
		
//		cout << "!" << endl;
		
		vector<int> tmp(d + 10);
		for(int p = 1; p <= k + 1; p++) {
//			assert(q[p] - q[p - 1] <= d + 2);
			for(int i = q[p], j = 1; i > q[p - 1]; i--, j++) {
				tmp[j] += a[i];
				if(tmp[j] >= 10) {
					tmp[j + 1] += tmp[j] / 10;
					tmp[j] %= 10;
					tmp[0] = max(tmp[0], j + 1);
				}
				tmp[0] = max(tmp[0], j);
			}
		}
		for(int j = 1; j <= tmp[0]; j++) {
			if(tmp[j] >= 10) {
				tmp[j + 1] += tmp[j] / 10;
				tmp[j] %= 10;
				tmp[0] = max(tmp[0], j + 1);
			}
		}
		
//		if(tmp[0] <= 5) {
//			cout << " - ";
//			for(int i = tmp[0]; i >= 1; i--) {
//				cout << tmp[i];
//			}
//			cout << endl;
//		}
		
		
		if(tmp[0] < ans[0] || ans[0] == -1) {
			ans = tmp;
		} else if(tmp[0] == ans[0]) {
			for(int i = tmp[0]; i >= 1; i--) {
				if(tmp[i] < ans[i]) {
					ans = tmp;
					break;
				} else if(tmp[i] > ans[i]) {
					break;
				}
			}
		}
		
		return;
	}
	
	for(int i = max(1ll, d - lim_bt); i <= d + lim_up; i++) {
		q[x] = q[x - 1] + i;
		dfs(x + 1, left - i);
	}
}


void work() {
	
	cin >> n >> k;
	cin >> (s + 1);
	for(int i = 1; i <= n; i++) a[i] = s[i] - '0';
	
	// a[i] in [1, 9]
	
	ans.resize(d + 10);
	ans[0] = -1;
	
	d = n / (k + 1);
	dfs(1, n);
	
//	cout << " d = " << d << endl;
	for(int i = ans[0]; i >= 1; i--) {
		cout << ans[i];
	}
	cout << endl;
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	freopen("F2.in", "r", stdin);
	
	int t = 1;
	cin >> t;
	while(t--) {
		work();
	}
	
	return 0;
}
