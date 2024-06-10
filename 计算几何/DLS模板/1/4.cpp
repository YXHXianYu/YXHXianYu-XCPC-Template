#include <bits/stdc++.h>
using namespace std;

typedef long long db;
const db EPS = 0;
  
inline int sign(db a) { return a < -EPS ? -1 : a > EPS; }
  
inline int cmp(db a, db b){ return sign(a-b); }
  
struct P {
	db x, y;
	P() {}
	P(db _x, db _y) : x(_x), y(_y) {}
	P operator+(P p) { return {x + p.x, y + p.y}; }
	P operator-(P p) { return {x - p.x, y - p.y}; }

	db dot(P p) { return x * p.x + y * p.y; }
	db det(P p) { return x * p.y - y * p.x; }
	void read() {
		int x_, y_;
		scanf("%d%d", &x_ ,&y_);
		x = x_;
		y = y_;
	}
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


bool check(P mid, P l, P r) {
	if (l.det(r) >= 0) {
		return l.det(mid) > 0 && r.det(mid) < 0;
	} else {
		return !(r.det(mid) >= 0 && l.det(mid) <= 0);
	}
}

bool cmp(P a, P b) {
	int qa = a.quad(), qb = b.quad();
	if (qa != qb) return qa < qb;
	else return sign(a.det(b)) > 0;
}
pair<P, int> p[10];

int solve() {
	P a, b, c, d, e, f;
	a.read(); b.read();
	c.read(); d.read();
	e.read(); f.read();
	if (!isSS(a, b, c, d) && !isSS(a, b, e, f)) return 0;
	if (!isSS_strict(c, d, e, f)) return 1;
	if (crossOp(c, d, a) * crossOp(c, d, b) >= 0) return 1;
	if (crossOp(e, f, a) * crossOp(e, f, b) >= 0) return 1;
	if (crossOp(c, d, a) < 0) swap(c, d);
	if (crossOp(e, f, a) < 0) swap(e, f);
	if ((d - c).det(f - e) > 0) swap(c, e), swap(d, f);
	P la = d - a, ra = e - a;
	P lb = c - b, rb = f - b;
	int t = 0;
	p[t++] = make_pair(la, 1);
	p[t++] = make_pair(ra, -1);
	p[t++] = make_pair(lb, 1);
	p[t++] = make_pair(rb, -1);
	int cur = cmp(ra, la) + cmp(rb, lb);
	sort(p, p + t, [&](pair<P, int> &a, pair<P, int> &b) {
		int qa = a.first.quad(), qb = b.first.quad();
		if (qa != qb) return qa < qb;
		auto d = a.first.det(b.first);
		if (d != 0) return d > 0;
		else return a.second < b.second;
	});
	if (cur >= 2) return 1;
	for (int i = 0; i < t; i++) {
		cur += p[i].second;
		if (cur >= 2) return 1;
	}
	return 2;
	/*
	if (check(d - a, c - b, f - b)) return 1;
	if (check(e - a, c - b, f - b)) return 1;
	if (check(c - b, d - a, e - a)) return 1;
	if (check(f - b, d - a, e - a)) return 1;
	return 2;*/
}

int main() {
	int tc;
	for (scanf("%d", &tc); tc; tc--) {
		printf("%d\n", solve());
	}
}