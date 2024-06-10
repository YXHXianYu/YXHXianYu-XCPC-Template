/**
 * Created by YXH_XianYu on 2023.9
 * Blog: https://yxhxianyu.fun
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'


void work() {
	int n, k;
	cin >> n >> k;

	vector<int> b(n + 1);
	for(int i = 1; i <= n; i++) cin >> b[i];

	if(k == 1) {
		for(int i = 1; i <= n; i++) {
			if(b[i] != i) {
				cout << "NO" << endl;
				return;
			}
		}
		cout << "YES" << endl;
		return;
	}

	vector<vector<int>> e(n + 1, vector<int>());
	for(int i = 1; i <= n; i++) {
		e[i].push_back(b[i]);
	}

	vector<int> col(n + 1), q(n + 1);
	vector<vector<int>> a(n + 1, vector<int>());
	
	auto bfs = [&](int st) {
		col[0] += 1;

		int tl = 0;
		q[++tl] = st;
		col[st] = col[0];
		a[col[0]].push_back(st);
		for(int i = 1; i <= tl; i++) {
			int x = q[i];
			for(auto y: e[x]) {
				if(col[y]) continue;
				q[++tl] = y;
				col[y] = col[0];
				a[col[0]].push_back(y);
			}
		}
	};

	for(int i = 1; i <= n; i++) if(!col[i]) bfs(i);

	vector<int> stk(n + 1), instk(n + 1), vis(n + 1), dep(n + 1);
	int haveAns = true;
	int top = 0;

	function<void(int, int)> dfs = [&](int x, int fa) {
		stk[++top] = x;
		instk[x] = 1;
		vis[x] = 1;
		dep[x] = dep[fa] + 1;
		for(auto y: e[x]) {
			// if(y == fa) continue;
			if(vis[y]) {
				if(instk[y]) {
					int del = dep[x] - dep[y] + 1;
					if(del != k) {
						haveAns = false;
						return;
					}
				}
				continue;
			}
			dfs(y, x);
		}
		instk[x] = 0;
		top -= 1;
	};

	for(int i = 1; i <= col[0] && haveAns; i++) {
		dfs(a[i][0], 0);
	}

	cout << (haveAns ? "YES" : "NO") << endl;
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