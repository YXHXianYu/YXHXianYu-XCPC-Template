#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'

typedef double db;
const db EPS = 1e-9;

inline int sign(db a) { return a < -EPS ? -1 : a > EPS; }

inline int cmp(db a, db b) { return sign(a - b); }

struct P {
	db x, y;
	P(): x(0), y(0) {}
	P(db _x, db _y): x(_x), y(_y) {}
	P operator+(P p) {
		return {x + p.x, y + p.y};
	}
	P operator-(P p) {
		return {x - p.x, y - p.y};
	}
	P operator*(db d) {
		return {x * d, y * d};
	}
	P operator/(db d) {
		return {x / d, y / d};
	}
	
	bool operator==(P p) const {
		return cmp(x, p.x) == 0 && cmp(y, p.y) == 0;
	}
	
	db dot(P p) {
		return x * p.x + y * p.y;
	}
	db det(P p) {
		return x * p.y - y * p.x;
	}
	
	db distTo(P p) {
		return (*this - p).abs();
	}
	db abs() {
		return sqrt(abs2());
	}
	db abs2() {
		return x * x + y * y;
	}
	P unit() {
		return *this / abs();
	}
};

#define cross(p1, p2, p3) ((p2.x-p1.x)*(p3.y-p1.y)-(p3.x-p1.x)*(p2.y-p1.y))
#define crossOp(p1, p2, p3) (sign(cross(p1, p2, p3)))

db nearest(P p1, P p2, P q) {
	if(p1 == p2) return p1.distTo(q);
	P v1 = p2 - p1, v2 = q - p1, v3 = q - p2;
	if(sign(v1.dot(v2)) == -1) return v2.abs();
	if(sign(v1.dot(v3)) == 1) return v3.abs();
	return fabs(v1.det(v2) / v1.abs());
}

bool isMiddle(db m, db a, db b) {
	if(a > b) swap(a, b);
	return cmp(a, m) <= 0 && cmp(m, b) <= 0;
}

bool isMiddle(P m, P a, P b) {
	return isMiddle(m.x, a.x, b.x) && isMiddle(m.y, a.y, b.y);
}

bool onSeg(P p1, P p2, P q) {
	return crossOp(p1, p2, q) == 0 && isMiddle(q, p1, p2);
}

int contain(vector<P>& ps, P p) {
	int n = ps.size() - 1;
	int ret = 0;
	for(int i = 1; i <= n; i++) {
		P u = ps[i], v = ps[i % n + 1];
		if(onSeg(u, v, p)) return 1;
		if(cmp(u.y, v.y) <= 0) swap(u, v);
		if(cmp(p.y, u.y) > 0 || cmp(p.y, v.y) <= 0) continue;
		ret ^= crossOp(p, u, v) > 0;
	}
	return ret * 2;
}

void work() {
	int n, q;
	cin >> n >> q;
	
	vector<P> a(n + 1);
	for(int i = 1; i <= n; i++) {
		int u, v;
		cin >> u >> v;
		a[i].x = u;
		a[i].y = v;
	}
	
	cout << fixed << setprecision(10);
	while(q--) {
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		
		P o = P{(x1 + x2) / 2.0, (y1 + y2) / 2.0};
		db r21 = (P(x1 - x2, y1 - y2)).abs2() / 8.0;
		
		int ret = contain(a, o);
		
		if(ret > 0) {
			cout << r21 << endl;
			continue;
		}
		
		db va = nearest(a[1], a[2], o);
		db ans = va * va;
		
		for(int i = 2; i <= n; i++) {
			int u = i, v = i % n + 1;
			db va = nearest(a[u], a[v], o);
			ans = min(ans, va * va);
		}
		ans += r21;
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
