#include <bits/stdc++.h>
using namespace std;

typedef long long db;
typedef long long ll;
const db EPS = 0;
  
inline int sign(db a) { return a < -EPS ? -1 : a > EPS; }
  
inline int cmp(db a, db b){ return sign(a-b); }
  
struct P {
	db x, y;
	P() {}
	P(db _x, db _y) : x(_x), y(_y) {}
	P operator+(P p) { return {x + p.x, y + p.y}; }
	P operator-(P p) { return {x - p.x, y - p.y}; }
	P operator*(db d) { return {x * d, y * d}; }

	bool operator<(P p) const { 
		int c = cmp(x, p.x);
		if (c) return c == -1;
		return cmp(y, p.y) == -1;
	}

	bool operator==(P o) const{
		return cmp(x,o.x) == 0 && cmp(y,o.y) == 0;
	}

	db dot(P p) { return x * p.x + y * p.y; }
	db det(P p) { return x * p.y - y * p.x; }
	 
	void read() { cin>>x>>y; }
	int quad() const { return sign(y) == 1 || (sign(y) == 0 && sign(x) >= 0); }
};

#define cross(p1,p2,p3) ((p2.x-p1.x)*(p3.y-p1.y)-(p3.x-p1.x)*(p2.y-p1.y))
#define crossOp(p1,p2,p3) sign(cross(p1,p2,p3))
 
// 直线 p1p2, q1q2 是否恰有一个交点
bool chkLL(P p1, P p2, P q1, P q2) {
	db a1 = cross(q1, q2, p1), a2 = -cross(q1, q2, p2);
	return sign(a1+a2) != 0;
}

// 判断区间 [l1, r1], [l2, r2] 是否相交
bool intersect(db l1,db r1,db l2,db r2){
	if (l1>r1) swap(l1,r1); if (l2>r2) swap(l2,r2); 
	return !( cmp(r1,l2) == -1 || cmp(r2,l1) == -1 );
}

// 线段 p1p2, q1q2 相交
bool isSS(P p1, P p2, P q1, P q2){
	return intersect(p1.x,p2.x,q1.x,q2.x) && intersect(p1.y,p2.y,q1.y,q2.y) && 
	crossOp(p1,p2,q1) * crossOp(p1,p2,q2) <= 0 && crossOp(q1,q2,p1)
			* crossOp(q1,q2,p2) <= 0;
}

// 线段 p1p2, q1q2 严格相交  
bool isSS_strict(P p1, P p2, P q1, P q2){
	return crossOp(p1,p2,q1) * crossOp(p1,p2,q2) < 0 && crossOp(q1,q2,p1)
			* crossOp(q1,q2,p2) < 0;
}

// m 在 a 和 b 之间
bool isMiddle(db a, db m, db b) {
	/*if (a > b) swap(a, b);
	return cmp(a, m) <= 0 && cmp(m, b) <= 0;*/
	return sign(a - m) == 0 || sign(b - m) == 0 || (a < m != b < m);
}

bool isMiddle(P a, P m, P b) {
	return isMiddle(a.x, m.x, b.x) && isMiddle(a.y, m.y, b.y);
}

// 点 p 在线段 p1p2 上
bool onSeg(P p1, P p2, P q){
	return crossOp(p1,p2,q) == 0 && isMiddle(p1, q, p2);
}
// q1q2 和 p1p2 的交点 在 p1p2 上？

// 点 p 严格在 p1p2 上
bool onSeg_strict(P p1, P p2, P q){
	return crossOp(p1,p2,q) == 0 && sign((q-p1).dot(p1-p2)) * sign((q-p2).dot(p1-p2)) < 0;
}

const int N = 2010;
P p[N], q[N * 2];
int n;

void solve() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		p[i] = P(x, y);
	}
	ll ans = (ll)n * (n - 1) * (n - 2) / 6;
	for (int i = 0; i < n; i++) {
		int t = 0;
		for (int j = 0; j < n; j++) if (j != i) {
			q[t++] = p[j] - p[i];
		}
		sort(q, q + t, [&](P a, P b) {
			int qa = a.quad(), qb = b.quad();
			if (qa != qb) return qa < qb;
			else return sign(a.det(b)) > 0;
		});
		for (int j = 0; j < t; j++) q[j + t] = q[j];
		int l = -1, r = -1;
		for (int j = 0; j < t; j++) {
			l = max(l, j + 1);
			r = max(r, j + 1);
			auto check1 = [&](P a, P b, int idl) {
				if (q[j].dot(q[l]) > 0) {
					if (q[j].det(q[l]) != 0) return q[j].det(q[l]) > 0;
					else return idl < t;
				}
				return false;
			};
			while (l < j + t && check1(q[j], q[l], l)) l++;
			auto check2 = [&](P a, P b, int idr) { // <= pi
				auto d = a.det(b);
				if (d != 0) return d > 0;
				return idr < t;
			};
			while (r < j + t && check2(q[j], q[r], r)) r++;
			ans -= r - l;
		}
	}
	printf("%lld\n" ,ans);
}
int main() {
	int tc;
	for (scanf("%d", &tc); tc; tc--) {
		solve();
	}
}
