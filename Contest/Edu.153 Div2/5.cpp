#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'


void work() {
	string s;
	cin >> s;
	int n = s.size();
	s = " " + s;

	int N = 28 * 28;
	vector<vector<array<int, 2>>> e(n + N + 10, vector<array<int, 2>>());
	int n1 = n - 1;
	for(int i = 1; i <= n1; i++) {
		if(i < n1) e[i].push_back({i + 1, 1});
		if(i > 1) e[i].push_back({i - 1, 1});
	}
	for(int i = 0; i <= 25; i++) {
		for(int j = 0; j <= 25; j++) {
			int p = n + i * 26 + j + 1;
			int ch1 = i + 'a';
			int ch2 = j + 'a';
			for(int k = 1; k <= n1; k++) {
				if(ch1 == s[k] && ch2 == s[k + 1]) {
					e[p].push_back({k, 1});
					e[k].push_back({p, 0});
				}
			}
		}
	}


	vector<vector<int>> f(N + 10, vector<int>(n + N + 10));

	const int INF = 1LL << 60;
	auto bfs = [&](int st) {
		for(int i = 1; i <= n + N + 9; i++) f[st][i] = INF;
		deque<int> dq;
		f[st][st] = 0;
		dq.push_back(st);
		while(!dq.empty()) {
			int x = dq.front();
			dq.pop_front();
			for(auto [y, w]: e[x]) {
				if(f[st][y] > f[st][x] + w) {
					f[st][y] = f[st][x] + w;
					if(w == 0) {
						dq.push_front(y);
					} else {
						dq.push_back(y);
					}
				}
			}
		}
	};

	for(int i = 0; i <= 25; i++) {
		for(int j = 0; j <= 25; j++) {
			int p = n + i * 26 + j + 1;
			bfs(p);
		}
	}

	// for(int i = 1; i <= n1; i++) cout << f[75][i] << " "; cout << endl;

	int m;
	cin >> m;
	for(int i = 1; i <= m; i++) {
		int x, y;
		cin >> x >> y;
		int p = n + (s[x]-'a') * 26 + (s[x+1]-'a') + 1;
		int ans = min(f[p][y], f[x][y]);
		if(x == y) {
			cout << 0 << endl;
		} else
		cout << ans << endl;
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
