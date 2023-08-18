#include <bits/stdc++.h>
using namespace std;

typedef double db;
#define rep(i, a, n) for (int i = a; i < n; i++)
const db EPS = 1e-9;
  
inline int sign(db a) { return a < -EPS ? -1 : a > EPS; }

inline int cmp(db a, db b){ return sign(a-b); }
  
struct P {
	db x, y;
	P() {}
	P(db _x, db _y) : x(_x), y(_y) {}
	P operator+(P p) { return {x + p.x, y + p.y}; }
	P operator-(P p) { return {x - p.x, y - p.y}; }
	P operator*(db d) { return {x * d, y * d}; }
	P operator/(db d) { return {x / d, y / d}; }

	bool operator<(P p) const { 
		int c = cmp(y, p.y);
		if (c) return c == -1;
		return cmp(x, p.x) == -1;
	}

	db dot(P p) { return x * p.x + y * p.y; }
	db det(P p) { return x * p.y - y * p.x; }
	P rot90() { return P(-y,x);}
	db abs() { return sqrt(abs2());}
	db abs2() { return x * x + y * y; }

};

#define cross(p1,p2,p3) ((p2.x-p1.x)*(p3.y-p1.y)-(p3.x-p1.x)*(p2.y-p1.y))
#define crossOp(p1,p2,p3) sign(cross(p1,p2,p3))

// 求直线 p1p2, q1q2 的交点
P isLL(P p1, P p2, P q1, P q2) {
	db a1 = cross(q1, q2, p1), a2 = -cross(q1, q2, p2);
	return (p1 * a2 + p2 * a1) / (a1 + a2);
}

vector<P> convexHull(vector<P> ps) {
	int n = ps.size(); if(n <= 1) return ps;
	sort(ps.begin(), ps.end());
	vector<P> qs(n * 2); int k = 0;
	for (int i = 0; i < n; qs[k++] = ps[i++]) 
		while (k > 1 && crossOp(qs[k - 2], qs[k - 1], ps[i]) <= 0) --k;
	for (int i = n - 2, t = k; i >= 0; qs[k++] = ps[i--])
		while (k > t && crossOp(qs[k - 2], qs[k - 1], ps[i]) <= 0) --k;
	qs.resize(k - 1);
	return qs;
}
  
vector<P> p;
int n;
int main() {
	scanf("%d", &n);
	p.resize(n);
	for (int i = 0; i < n; i++) {
		scanf("%lf%lf", &p[i].x, &p[i].y);
	}
	p = convexHull(p);
	n = p.size();
	p.resize(2 * n);
	for (int i = 0; i < n; i++) {
		p[i + n] = p[i];
	}
	int u = -1, l = -1, r = -1;
	P d0 = p[1] - p[0];
	for (int i = 0; i < n; i++) {
		if (r == -1 || d0.dot(p[i]) > d0.dot(p[r])) r = i;
		if (l == -1 || d0.dot(p[i]) < d0.dot(p[l])) l = i;
		if (u == -1 || d0.det(p[i]) > d0.det(p[u])) u = i;
	}
	db ans = 1e10;
	vector<P> ansP;
	for (int i = 0; i < n; i++) {
		P d = p[i + 1] - p[i];
		while (r + 1 < 2 * n && d.dot(p[r + 1]) > d.dot(p[r])) r++;
		while (l + 1 < 2 * n && d.dot(p[l + 1]) < d.dot(p[l])) l++;
		while (u + 1 < 2 * n && d.det(p[u + 1]) > d.det(p[u])) u++;
		db s1 = d.dot(p[r] - p[l]) / d.abs();
		db s2 = d.det(p[u] - p[i]) / d.abs();
		if (s1 * s2 < ans) {
			ans = s1 * s2;
			P p1 = isLL(p[i], p[i] + d, p[r], p[r] + d.rot90());
			P p2 = isLL(p[r], p[r] + d.rot90(), p[u], p[u] - d);
			P p3 = isLL(p[u], p[u] - d, p[l], p[l] - d.rot90());
			P p4 = isLL(p[l], p[l] - d.rot90(), p[i], p[i] + d);
			ansP = vector<P>{p1, p2, p3, p4};
			rotate(ansP.begin(), min_element(ansP.begin(), ansP.end()), ansP.end());
		}
	}
	printf("%.10f\n", ans);
	for (auto p : ansP) {
		printf("%.10f %.10f\n", p.x, p.y);
	}
}