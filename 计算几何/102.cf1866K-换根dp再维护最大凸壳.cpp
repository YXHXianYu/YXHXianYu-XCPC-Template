/**
 * Created by YXH_XianYu on 2023.8.31
 * Blog: https://yxhxianyu.fun
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'

typedef __int128_t db; // 换longdouble时，需要同时替换alpha函数和getTheta函数
const db EPS = 0;

inline int sign(db a) { return a < -EPS ? -1 : a > EPS; }

inline int cmp(db a, db b) { return sign(a - b); }

// 点P
struct P {
    db x, y;
    P(): x(0), y(0) {}
    P(db _x, db _y): x(_x), y(_y) {}
    P operator+(P p) { return {x + p.x, y + p.y}; }
    P operator-(P p) { return {x - p.x, y - p.y}; }
    P operator*(db d) { return {x * d, y * d}; }
    P operator/(db d) { return {x / d, y / d}; }

    bool operator<(P p) const {
        int c = cmp(x, p.x);
        if(c) return c == -1;
        return cmp(y, p.y) == -1;
    }

    // 这里的比较可能不满足传递性，因为这是基于EPS的比较
    bool operator==(P p) const {
        return cmp(x, p.x) == 0 && cmp(y, p.y) == 0;
    }

    db dot(P p) { return x * p.x + y * p.y; }
    db det(P p) { return x * p.y - y * p.x; }
};

#define cross(p1, p2, p3) ((p2.x-p1.x)*(p3.y-p1.y)-(p3.x-p1.x)*(p2.y-p1.y))
#define crossOp(p1, p2, p3) (sign(cross(p1, p2, p3)))


void work() {
	int n;
	cin >> n;

	vector<vector<array<int, 2>>> e(n + 1, vector<array<int, 2>>());
	for(int i = 1; i < n; i++) {
		int u, v, w;
		cin >> u >> v >> w;

		e[u].push_back({v, w});
		e[v].push_back({u, w});
	}

	int rt = 1;

	// part1

	vector<int> fa(n + 1);
	vector<int> f(n + 1); // f[i]: 子树i内最长距离
	vector<int> g(n + 1); // g[i]: 子树fa[i] 除了子树i 以外的最长距离
	int diameter = 0;

	auto dfs1 = [&](auto self, int x) -> void {
		for(auto [y, w]: e[x]) {
			if(y == fa[x]) continue;
			fa[y] = x;
			self(self, y);
			diameter = max(diameter, f[x] + f[y] + w);
			f[x] = max(f[x], f[y] + w);
		}
	};
	dfs1(dfs1, rt);

	auto dfs2 = [&](auto self, int x) -> void {
		int deg = e[x].size();
		vector<int> pre(deg), suf(deg);
		for(int i = 0; i < deg - 1; i++) {
			auto [y, w] = e[x][i];
			pre[i + 1] = max(pre[i], (y == fa[x] ? g[x] : f[y]) + w);
		}
		for(int i = deg - 1; i > 0; i--) {
			auto [y, w] = e[x][i];
			suf[i - 1] = max(suf[i], (y == fa[x] ? g[x] : f[y]) + w);
		}
		for(int i = 0; i < deg; i++) {
			auto [y, w] = e[x][i];
			if(y == fa[x]) continue;
			g[y] = max(pre[i], suf[i]);
			self(self, y);
		}
	};
	dfs2(dfs2, rt);

	// part 2

	vector<vector<P>> h1(n + 1), h2(n + 1);
	
	auto cmp = [&](const P& a, const P& b) {
		return a.x < b.x || (a.x == b.x && a.y < b.y);
	};
	auto add = [&](auto& h, P p, auto& tmp) {
		while(h.size() >= 2 && crossOp(h[h.size()-2], h.back(), p) >= 0) {
			tmp.push_back(h.back());
			h.pop_back();
		}
		h.push_back(p);
	};

	for(int x = 1; x <= n; x++) {
		vector<P> a;
		for(auto [y, w]: e[x]) {
			a.push_back({(db)w, (db)(y == fa[x] ? g[x]: f[y])});
		}
		sort(a.begin(), a.end(), cmp);

		vector<P> b;
		for(auto p: a) {
			add(h1[x], p, b);
		}
		sort(b.begin(), b.end(), cmp);
		for(auto p: b) {
			add(h2[x], p, a);
		}
	}

	auto get = [&](auto& h, P p) {
		if(h.empty()) return -1ll;
		int L = 0, R = h.size();
		while(R - L >= 2) {
			int mid = L + R >> 1;
			if(p.dot(h[mid - 1]) < p.dot(h[mid])) {
				L = mid;
			} else {
				R = mid;
			}
		}
		return L;
	};

	int Q;
	cin >> Q;

	for(int T = 1; T <= Q; T++) {
		int x, k;
		cin >> x >> k;

		int ans = diameter;

		vector<int> a;
		P p(k, 1);

		auto idx = get(h1[x], p);
		if(idx != -1) {
			a.push_back(p.dot(h1[x][idx]));
			if(idx > 0) {
				a.push_back(p.dot(h1[x][idx-1]));
			}
			if(idx < h1[x].size() - 1) {
				a.push_back(p.dot(h1[x][idx+1]));
			}
		}

		idx = get(h2[x], p);
		if(idx != -1) {
			a.push_back(p.dot(h2[x][idx]));
		}

		sort(a.begin(), a.end(), greater());
		a.resize(2);

		ans = max(ans, a[0] + a[1]);

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