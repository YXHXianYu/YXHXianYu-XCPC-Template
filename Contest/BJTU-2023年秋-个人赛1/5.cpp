#include<bits/stdc++.h>
using namespace std;
#define int long long


void work() {
	int n;
	cin >> n;
	
	vector<vector<int>> a(n + 1, vector<int>());
	for(int i = 1; i <= n; i++) {
		int k;
		cin >> k;
		a[i].resize(k + 1);
		for(int j = 1; j <= k; j++) {
			cin >> a[i][j];
		}
	}
	
	vector<int> v1(n + 1), v2(n + 1);
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j < a[i].size(); j++) {
			if(v2[a[i][j]] == 0) {
				v2[a[i][j]] = 1;
				v1[i] = 1;
				break;
			}
		}
	}
	
	vector<array<int, 2>> ans;
	for(int i = 1, j = 1; i <= n; i++) {
		if(v1[i] == 0) {
			for(; j <= n; j++) {
				if(v2[j] == 0) {
					ans.push_back({i, j});
					break;
				}
			}
		}
	}
	
	if(ans.size() == 0) {
		cout << "OPTIMAL" << endl;
	} else {
		cout << "IMPROVE" << endl;
		for(auto pr: ans) {
			cout << pr[0] << " " << pr[1] << endl;
			return;
		}
	}
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