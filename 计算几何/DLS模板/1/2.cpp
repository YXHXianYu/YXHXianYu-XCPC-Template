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
pair<P, int> evt[2 * N];
P p[N][2];
int n;

ll solve(P o) {
	int t = 0;
	for (int i = 0; i < n; i++) {
		if (p[i][0].y == o.y) continue;
		P p1 = p[i][0] - o, p2 = p[i][1] - o;
		int len = p[i][1].x - p[i][0].x;
		if (p[i][1].y > o.y) {
			evt[t++] = make_pair(p2, len);
			evt[t++] = make_pair(p1, -len);
		} else {
			evt[t++] = make_pair(p1 * (-1), len);
			evt[t++] = make_pair(p2 * (-1), -len);
		}
	}
	sort(evt, evt + t, [&](pair<P, int> &a, pair<P, int> &b) {
		auto d = a.first.det(b.first);
		if (d != 0) return d > 0;
		else return a.second > b.second;
	});
	ll ans = 0, cur = 0;
	for (int i = 0; i < t; i++) {
		cur += evt[i].second;
		ans = max(ans, cur);
	}
	return ans;
}
int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		int x1, x2, y;
		scanf("%d%d%d", &x1, &x2, &y);
		if (x1 > x2) swap(x1, x2);
		p[i][0] = P(x1, y);
		p[i][1] = P(x2, y);
	}
	ll ans = 0;
	for (int i = 0; i < n; i++) {
		ans = max(ans, max(solve(p[i][0]), solve(p[i][1])) + p[i][1].x - p[i][0].x);
	}
	printf("%lld\n", ans);
}

