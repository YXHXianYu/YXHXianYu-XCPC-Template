#include<bits/stdc++.h>
using namespace std;
#define int long long

void work() {
	int n;
	cin >> n;

	// bit
	const int MAXN = 1e6;
	vector<int> bit(MAXN + 1);
	#define lowbit(x) (x&-x)
	auto add = [&](int x, int v) {
		for(; x <= MAXN; x += lowbit(x)) bit[x] += v;
	};
	auto query = [&](int x) {
		int ans = 0; for(; x; x -= lowbit(x)) ans += bit[x]; return ans;
	};

	// solve
	vector<int> a(n + 2, MAXN + 1);
	int top = 0;

	vector<int> pos(MAXN + 2, n + 1);
	vector<array<int, 4>> q;

	auto change = [&](int x, int y) {
		add(pos[x], -1);
		pos[x] = y;
		add(pos[x], 1);
	};
	
	for(int i = 1; i <= n; i++) {
		char opt;
		cin >> opt;
		if(opt == '+') {
			int x;
			cin >> x;
			top += 1;
			q.push_back({x, pos[x], a[top], pos[a[top]]});
			if(pos[a[top]] == top) {
				change(a[top], MAXN + 1);
			}
			if(pos[x] > top) {
				change(x, top);
			}
			a[top] = x;

		} else if(opt == '-') {
			int k;
			cin >> k;

			top -= k;
			q.push_back({-1, k});

		} else if(opt == '?') {
			cout << query(top) << '\n';
			cout.flush();

		} else if(opt == '!') {
			auto [x, y, z, w] = q.back();
			q.pop_back();

			if(x == -1) {
				top += y;
			} else {
				a[top] = z;
				if(pos[x] != y) {
					change(x, y);
				}
				if(pos[z] != w) {
					change(z, w);
				}
				top -= 1;
			}

		} else assert(false);
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
