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

	bool operator==(P o) const{
		return cmp(x,o.x) == 0 && cmp(y,o.y) == 0;
	}

	db dot(P p) { return x * p.x + y * p.y; }
	db det(P p) { return x * p.y - y * p.x; }
	 
	db distTo(P p) { return (*this-p).abs(); }
	db alpha() { return atan2(y, x); }
	void read() {
		int x_, y_;
		scanf("%d%d", &x_, &y_);
		x = x_, y = y_;
	}

	void write() {cout<<"("<<x<<","<<y<<")"<<endl;}
	db abs() { return sqrt(abs2());}
	db abs2() { return x * x + y * y; }
	P rot90() { return P(-y,x);}
	P unit() { return *this/abs(); }
	int quad() const { return sign(y) == 1 || (sign(y) == 0 && sign(x) >= 0); }
	P rot(db an){ return {x*cos(an) - y*sin(an),x*sin(an) + y*cos(an)}; }
};

#define cross(p1,p2,p3) ((p2.x-p1.x)*(p3.y-p1.y)-(p3.x-p1.x)*(p2.y-p1.y))
#define crossOp(p1,p2,p3) sign(cross(p1,p2,p3))
 
// 直线 p1p2, q1q2 是否恰有一个交点
bool chkLL(P p1, P p2, P q1, P q2) {
	db a1 = cross(q1, q2, p1), a2 = -cross(q1, q2, p2);
	return sign(a1+a2) != 0;
}

// 求直线 p1p2, q1q2 的交点
P isLL(P p1, P p2, P q1, P q2) {
	db a1 = cross(q1, q2, p1), a2 = -cross(q1, q2, p2);
	return (p1 * a2 + p2 * a1) / (a1 + a2);
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

// 求 q 到 直线p1p2 的投影（垂足） ⚠️ : p1 != p2
P proj(P p1, P p2, P q) {
	P dir = p2 - p1;
	return p1 + dir * (dir.dot(q - p1) / dir.abs2());
}

// 求 q 以 直线p1p2 为轴的反射
P reflect(P p1, P p2, P q){
	return proj(p1,p2,q) * 2 - q;
}

// 求 q 到 线段p1p2 的最小距离
db nearest(P p1, P p2, P q){
	if (p1 == p2) return p1.distTo(q);
	P h = proj(p1,p2,q);
	if(isMiddle(p1,h,p2))
		return q.distTo(h);
	return min(p1.distTo(q),p2.distTo(q));
}

// 求 线段p1p2 与 线段q1q2 的距离
db disSS(P p1, P p2, P q1, P q2){
	if(isSS(p1,p2,q1,q2)) return 0;
	return min(min(nearest(p1,p2,q1),nearest(p1,p2,q2)), min(nearest(q1,q2,p1),nearest(q1,q2,p2)));
}

db area(vector<P> ps){
	db ret = 0; rep(i,0,ps.size()) ret += ps[i].det(ps[(i+1)%ps.size()]); 
	return ret/2;
}
  
int contain(vector<P> ps, P p){ //2:inside,1:on_seg,0:outside
	int n = ps.size(), ret = 0; 
	rep(i,0,n){
		P u=ps[i],v=ps[(i+1)%n];
		if(onSeg(u,v,p)) return 1;
		if(cmp(u.y,v.y)<=0) swap(u,v);
		if(cmp(p.y,u.y) > 0 || cmp(p.y,v.y) <= 0) continue;
		ret ^= crossOp(p,u,v) > 0;
	}
	return ret*2;
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
  
vector<P> convexHullNonStrict(vector<P> ps) {
	//caution: need to unique the Ps first
	int n = ps.size(); if(n <= 1) return ps;
	sort(ps.begin(), ps.end());
	vector<P> qs(n * 2); int k = 0;
	for (int i = 0; i < n; qs[k++] = ps[i++]) 
		while (k > 1 && crossOp(qs[k - 2], qs[k - 1], ps[i]) < 0) --k;
	for (int i = n - 2, t = k; i >= 0; qs[k++] = ps[i--])
		while (k > t && crossOp(qs[k - 2], qs[k - 1], ps[i]) < 0) --k;
	qs.resize(k - 1);
	return qs;
}
  
db convexDiameter(vector<P> ps){
	int n = ps.size(); if(n <= 1) return 0;
	int is = 0, js = 0; rep(k,1,n) is = ps[k]<ps[is]?k:is, js = ps[js] < ps[k]?k:js;
	int i = is, j = js;
	db ret = ps[i].distTo(ps[j]);
	do{
		if((ps[(i+1)%n]-ps[i]).det(ps[(j+1)%n]-ps[j]) >= 0)
			(++j)%=n;
		else
			(++i)%=n;
		ret = max(ret,ps[i].distTo(ps[j]));
	}while(i!=is || j!=js);
	return ret;
}
  
vector<P> convexCut(const vector<P>&ps, P q1, P q2) {
	vector<P> qs;
	int n = ps.size();
	rep(i,0,n){
		P p1 = ps[i], p2 = ps[(i+1)%n];
		int d1 = crossOp(q1,q2,p1), d2 = crossOp(q1,q2,p2);
		if(d1 >= 0) qs.push_back(p1);
		if(d1 * d2 < 0) qs.push_back(isLL(p1,p2,q1,q2));
	}
	return qs;
}

int type(P o1,db r1,P o2,db r2){
	db d = o1.distTo(o2);
	if(cmp(d,r1+r2) == 1) return 4;
	if(cmp(d,r1+r2) == 0) return 3;
	if(cmp(d,abs(r1-r2)) == 1) return 2;
	if(cmp(d,abs(r1-r2)) == 0) return 1;
	return 0;
}
  
vector<P> isCL(P o,db r,P p1,P p2){
	if (cmp(abs((o-p1).det(p2-p1)/p1.distTo(p2)),r)>0) return {};
	db x = (p1-o).dot(p2-p1), y = (p2-p1).abs2(), d = x * x - y * ((p1-o).abs2() - r*r);
	d = max(d,(db)0.0); P m = p1 - (p2-p1)*(x/y), dr = (p2-p1)*(sqrt(d)/y);
	return {m-dr,m+dr}; //along dir: p1->p2
}
  
vector<P> isCC(P o1, db r1, P o2, db r2) { //need to check whether two circles are the same
	db d = o1.distTo(o2); 
	if (cmp(d, r1 + r2) == 1) return {};
	if (cmp(d,abs(r1-r2))==-1) return {};
	d = min(d, r1 + r2);
	db y = (r1 * r1 + d * d - r2 * r2) / (2 * d), x = sqrt(r1 * r1 - y * y);
	P dr = (o2 - o1).unit();
	P q1 = o1 + dr * y, q2 = dr.rot90() * x;
	return {q1-q2,q1+q2};//along circle 1
}
  
// extanCC, intanCC : -r2, tanCP : r2 = 0
vector<pair<P, P>> tanCC(P o1, db r1, P o2, db r2) {
	P d = o2 - o1;
	db dr = r1 - r2, d2 = d.abs2(), h2 = d2 - dr * dr;
	if (sign(d2) == 0|| sign(h2) < 0) return {};
	h2 = max(0.0, h2);
	vector<pair<P, P>> ret;
	for (db sign : {-1, 1}) {
		P v = (d * dr + d.rot90() * sqrt(h2) * sign) / d2;
		ret.push_back({o1 + v * r1, o2 + v * r2});
	}
	if (sign(h2) == 0) ret.pop_back();
	return ret;
}

db rad(P p1,P p2){
	return atan2l(p1.det(p2),p1.dot(p2));
}

db areaCT(db r, P p1, P p2){
	vector<P> is = isCL(P(0,0),r,p1,p2);
	if(is.empty()) return r*r*rad(p1,p2)/2;
	bool b1 = cmp(p1.abs2(),r*r) == 1, b2 = cmp(p2.abs2(), r*r) == 1;
	if(b1 && b2){
		if(sign((p1-is[0]).dot(p2-is[0])) <= 0 &&
			sign((p1-is[1]).dot(p2-is[1])) <= 0)
		return r*r*(rad(p1,is[0]) + rad(is[1],p2))/2 + is[0].det(is[1])/2;
		else return r*r*rad(p1,p2)/2;
	}
	if(b1) return (r*r*rad(p1,is[0]) + is[0].det(p2))/2;
	if(b2) return (p1.det(is[1]) + r*r*rad(is[1],p2))/2;
	return p1.det(p2)/2;
}

P inCenter(P A, P B, P C) {
	double a = (B - C).abs(), b = (C - A).abs(), c = (A - B).abs();
	return (A * a + B * b + C * c) / (a + b + c);
}
 
P circumCenter(P a, P b, P c) { 
	P bb = b - a, cc = c - a;
	double db = bb.abs2(), dc = cc.abs2(), d = 2 * bb.det(cc);
	return a - P(bb.y * dc - cc.y * db, cc.x * db - bb.x * dc) / d;
}
 
P othroCenter(P a, P b, P c) { 
	P ba = b - a, ca = c - a, bc = b - c;
	double Y = ba.y * ca.y * bc.y,
	A = ca.x * ba.y - ba.x * ca.y,
	x0 = (Y + ca.x * ba.y * b.x - ba.x * ca.y * c.x) / A,
	y0 = -ba.x * (x0 - c.x) / ba.y + ca.y;
	return {x0, y0};
}

pair<P,db> min_circle(vector<P> ps){
    // random_shuffle(ps.begin(), ps.end());
    int n = ps.size();
    P o = ps[0]; db r = 0;
    rep(i,1,n) if(o.distTo(ps[i]) > r + EPS){
        o = ps[i], r = 0;
        rep(j,0,i) if(o.distTo(ps[j]) > r + EPS){
            o = (ps[i] + ps[j]) / 2; r = o.distTo(ps[i]);
            rep(k,0,j) if(o.distTo(ps[k]) > r + EPS){
                 o = circumCenter(ps[i],ps[j],ps[k]);
                 r = o.distTo(ps[i]);
            }
        }
    }
    return {o,r};
}

int n, r[10], f[10];
P o[10];
void solve() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		int x, y, r_;
		scanf("%d%d%d", &x, &y, &r_);
		o[i] = P(x, y);
		r[i] = r_;
	}
	vector<P> pt;
	vector<vector<P>> pts(n);
	for (int i = 0; i < n; i++) {
		pts[i].clear();
		for (int j = 0; j < n; j++) if (i != j) {
			auto ps = isCC(o[i], r[i], o[j], r[j]);
			for (auto p : ps) {
				pts[i].push_back(p);
				pt.push_back(p);
			}
		}
		if (pts[i].empty()) {
			P p = o[i] - P(r[i], 0);
			pts[i].push_back(p);
			pt.push_back(p);
		}
		sort(pts[i].begin(), pts[i].end());
		pts[i].erase(unique(pts[i].begin(), pts[i].end()), pts[i].end());
	}
	sort(pt.begin(), pt.end());
	pt.erase(unique(pt.begin(), pt.end()), pt.end());
	int V = pt.size();
	int E = 0, C = V;
	for (int i = 1; i <= V; i++) f[i] = i;
	function<int(int)> find = [&](int x) {
		return f[x] == x ? x : f[x] = find(f[x]);
	};
	for (int i = 0; i < n; i++) {
		E += pts[i].size();
		int x = lower_bound(pt.begin(), pt.end(), pts[i][0]) - pt.begin() + 1;
		for (auto p : pts[i]) {
			int y = lower_bound(pt.begin(), pt.end(), p) - pt.begin() + 1;
			if (find(x) != find(y)) {
				--C;
				f[find(x)] = find(y);
			}
		}
	}
	int F = E + C + 1 - V;
	printf("%d\n", F);
	// V - E + F = 1 + C
}

int main() {
	int tc;
	scanf("%d", &tc);
	for (; tc; tc--) {
		solve();
	}
}