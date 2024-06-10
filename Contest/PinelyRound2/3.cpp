/**
 * Created by YXH_XianYu on 2023.8.29
 * Blog: https://yxhxianyu.fun
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'


void work() {
	int n, k;
	cin >> n >> k;

	vector<int> a(n + 1);
	for(int i = 1; i <= n; i++) cin >> a[i];

	vector<int> vis(n + 1);
	for(int i = 1; i <= n; i++) vis[a[i]] = 1;

	for(int i = 0; i <= n; i++) if(vis[i] == 0) {
		a[0] = i;
		break;
	}

	k %= n + 1;

	for(int i = (-k+n+2) % (n + 1), j = 1; j <= n; i = (i + 1) % (n + 1), j++) {
		cout << a[i] << " ";
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