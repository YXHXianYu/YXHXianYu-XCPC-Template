#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;


void work() {
	int n, m;
	cin >> n >> m;

	vector<int> cnt(m + 1);
	vector<pair<int, int>> edge(m + 1);
	vector<int> deg(n + 1);
	vector<vector<pair<int, int>>> e(n + 1, vector<pair<int, int>>());
	for(int i = 1; i <= m; i++) {
		int u, v, y;
		cin >> u >> v >> y;
		e[u].push_back({v, i});
		e[v].push_back({u, i});
		cnt[i] = y;
		deg[u]++;
		deg[v]++;
		edge[i] = {u, v};
	}

	if(deg[n] == 0) {
		cout << "inf" << endl;
		return;
	}

	vector<pair<string, int>> ans;
	vector<bool> S(n + 1, 1);
	vector<int> tag(m + 1);

	S[n] = 0;
	for(auto [y, i]: e[n]) {
		tag[i] = 1;
	}

	int T = 0;
	while(true) {
		int flag = true;
		int lim = 0;
		for(int i = 1; i <= m; i++) {
			if(tag[i] == 1) {
				if(lim == 0 || cnt[lim] > cnt[i]) {
					lim = i;
				}
				flag = false;
			}
		}
		if(flag) break;
		// stage 2
		string ans1 = "";
		for(int i = 1; i <= n; i++) {
			ans1.push_back(S[i] ? '1' : '0');
		}
		int ans2 = cnt[lim];
		T += ans2;
		vector<int> tag2 = tag;
		for(int i = 1; i <= m; i++) {
			if(tag[i] == 1) {
				cnt[i] -= ans2;
				if(cnt[i] == 0) {
					S[edge[i].first] = 0;
					S[edge[i].second] = 0;
					for(auto [y, idx]: e[edge[i].first]) {
						if(tag2[idx] == 0) {
							tag2[idx] = 1;
						}
					}
					for(auto [y, idx]: e[edge[i].second]) {
						if(tag2[idx] == 0) {
							tag2[idx] = 1;
						}
					}
					tag2[i] = 2;
				}
			}
		}
		tag = tag2;
		ans.push_back({ans1, ans2});
		if(S[1] == 0) {
			break;
		}
	}

	if(S[1] == 1) {
		cout << "inf" << endl;
		return;
	}

	cout << T << " " << ans.size() << endl;
	for(auto& [ans1, ans2]: ans) {
		cout << ans1 << " " << ans2 << endl;
	}
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
