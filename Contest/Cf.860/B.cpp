#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 5e4 + 10;

int m;
int n[maxn];
vector<int> a[maxn];
int ans[maxn];


void work() {
	
	cin >> m;
	for(int i = 1; i <= m; i++) {
		cin >> n[i];
		a[i].resize(n[i] + 1);
		for(int j = 1; j <= n[i]; j++) {
			cin >> a[i][j];
		}
	}
	
	map<int, int> f;
	for(int i = 1; i <= m; i++) ans[i] = -1;
	for(int i = m; i >= 1; i--) {
		for(int j = 1; j <= n[i]; j++) {
			if(f.count(a[i][j]) != 0) {
				continue;
			}
			if(ans[i] == -1) {
				ans[i] = a[i][j];
			}
			f[a[i][j]] = 1;
		}
		if(ans[i] == -1) {
			cout << -1 << endl;
			return;
		}
	}
	
	for(int i = 1; i <= m; i++) {
		cout << ans[i] << " ";
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
