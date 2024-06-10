/**
 * Created by YXH_XianYu on 2023.8.31
 * Blog: https://yxhxianyu.fun
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'


void work() {
	
	int n = 4, k = 3;

	vector<int> a(n + 1);
	int ans = 0;
	function<void(int)> dfs = [&](int x) {
		if(x > n) {
			vector<int> rec;
			vector<int> cnt(k + 1);
			int sum = 0;
			for(int i = 1; i < k; i++) {
				if(cnt[a[i]] == 0) sum++;
				cnt[a[i]]++;
			}
			for(int i = k; i <= n; i++) {
				if(cnt[a[i]] == 0) sum++;
				cnt[a[i]]++;
				
				if(sum == k) rec.push_back(i);
				
				cnt[a[i-k+1]]--;
				if(cnt[a[i-k+1]] == 0) sum--;
			}

			if(rec.size() == 0) return;

			for(int i = 1; i <= n; i++) cout << a[i] << " ";
			cout << " ||| ";
			cout << rec.size() << ": ";
			for(auto y: rec) cout << y << " "; cout << endl;

			ans += rec.size();

			return;
		}

		for(int i = 1; i <= k; i++) {
			a[x] = i;
			dfs(x + 1);
		}
	};

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