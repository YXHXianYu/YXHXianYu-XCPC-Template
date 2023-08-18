// Computation Geometry Template refer to dyh
#include <bits/stdc++.h>
#define int long long
using namespace std;

/* 基础板子 */

typedef double db; // 换longdouble时，需要同时替换alpha函数和getTheta函数
const db EPS = 1e-9;

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

    db distTo(P p) { return (*this-p).abs(); }
    // return value in [-pi, pi]; longdouble ver is atan2l(y, x)
    db alpha() { return atan2(y, x); }
    void read() { cin >> x >> y; }
    db abs() { return sqrt(abs2()); }
    db abs2() { return x * x + y * y; }
    P unit() { return *this / abs(); }
    P rot90() { return P(-y, x); }
    P rot(db an) { return {x*cos(an) - y*sin(an), x*sin(an) + y*cos(an)}; }
    int quad() const { return sign(y) == 1 || (sign(y) == 0 && sign(x) >= 0); }
};

#define cross(p1, p2, p3) ((p2.x-p1.x)*(p3.y-p1.y)-(p3.x-p1.x)*(p2.y-p1.y))
#define crossOp(p1, p2, p3) (sign(cross(p1, p2, p3)))

// 判断 直线p1p2 和 直线q1q2 是否严格相交
// => crossOp(p1, p2, q1) * crossOp(p1, p2, q2) < 0

// 判断 直线p1p2 和 直线q1q2 是否相交
bool isLL(P p1, P p2, P q1, P q2) {
    db a1 = cross(q1, q2, p1), a2 = -cross(q1, q2, p2);
    return sign(a1 + a2) != 0;
}

// 求交点
P getLL(P p1, P p2, P q1, P q2) {
    db a1 = cross(q1, q2, p1), a2 = -cross(q1, q2, p2);
    return (p1 * a2 + p2 * a1) / (a1 + a2);
}

// 判断区间是否相交
bool intersect(db l1, db r1, db l2, db r2) {
    if(l1 > r1) swap(l1, r1); if(l2 > r2) swap(l2, r2);
    return !( cmp(r1, l2) == -1 || cmp(r2, l1) == -1 );
}

// 线段相交
bool isSS(P p1, P p2, P q1, P q2) {
    return intersect(p1.x, p2.x, q1.x, q2.x)
        && intersect(p1.y, p2.y, q1.y, q2.y)
        && crossOp(p1, p2, q1) * crossOp(p1, p2, q2) <= 0
        && crossOp(q1, q2, p1) * crossOp(q1, q2, p2) <= 0;
}

// 线段严格相交(不能交于端点)
bool isSS_strict(P p1, P p2, P q1, P q2) {
    return crossOp(p1, p2, q1) * crossOp(p1, p2, q2) < 0
        && crossOp(q1, q2, p1) * crossOp(q1, q2, p2) < 0;
}

// 点m 是否在 a 和 b 之间
bool isMiddle(db m, db a, db b) {
    if(a > b) swap(a, b);
    return cmp(a, m) <= 0 && cmp(m, b) <= 0;
}

// 点m 是否在 点a 和 点b 之间
bool isMiddle(P m, P a, P b) {
    return isMiddle(m.x, a.x, b.x) && isMiddle(m.y, a.y, b.y);
}

// 点q 是否在 直线p1p2 上
// => crossOp(p1, p2, q) == 0

// 点q 是否在 线段p1p2 上
bool onSeg(P p1, P p2, P q) {
    return crossOp(p1, p2, q) == 0 && isMiddle(q, p1, p2);
}

// 点q 是否在 线段p1p2 上(严格)
bool onSeg_strict(P p1, P p2, P q) {
    return crossOp(p1, p2, q) == 0 && sign((q-p1).dot(p1-p2)) * sign((q-p2).dot(p1-p2));
}

// 求 q 到 直线p1p2 的投影(垂足)
P proj(P p1, P p2, P q) {
    P dir = p2 - p1;
    return p1 + dir * (dir.dot(q - p1) / dir.abs2());
}

// 求 q 以 直线p1p2 为轴的反射
P reflect(P p1, P p2, P q) {
    return proj(p1, p2, q) * 2 - q;
}

// 求 q 到 线段p1p2 的最小距离
db nearest(P p1, P p2, P q) {
    if(p1 == p2) return p1.distTo(q);
    P h = proj(p1, p2, q);
    if(isMiddle(h, p1, p2)) return h.distTo(q);
    return min(p1.distTo(q), p2.distTo(q));
}

// 求 线段p1p2 与 线段q1q2 的距离
db disSS(P p1, P p2, P q1, P q2) {
    if(isSS(p1, p2, q1, q2)) return 0;
    return min(
        min(nearest(p1, p2, q1), nearest(p1, p2, q2)),
        min(nearest(q1, q2, p1), nearest(q1, q2, p2))
    );
}

// 极角排序
void polarSort() {
    int n = 50;
    P p[100];
    sort(p + 1, p + n + 1, [&](P& a, P& b) {
        int qa = a.quad(), qb = b.quad();
        if(qa != qb) return qa < qb;
        else return sign(a.det(b)) > 0;
    });
}

/* 多边形 */
/* 重要约定，每个vector大小必须等于size+1，且index从1开始 */

// 求简单多边形面积（测过）
db area(vector<P>& ps) {
    int n = ps.size() - 1;
    db ret = 0;
    for(int i = 1; i <= n; i++) {
        ret += ps[i].det(ps[i % n + 1]);
    }
    return ret / 2;
}

// 求点包含（测过）
// 2:inside, 1:on_seg, 0:outside
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

// 凸包（测过）
vector<P> convexHull(vector<P>& ps) {
    int n = ps.size() - 1;
    if(n <= 1) return ps;
    sort(ps.begin() + 1, ps.begin() + n + 1); // normal sort
    vector<P> qs(2 * n + 1);
    int cnt = 0;
    for(int i = 1; i <= n; qs[++cnt] = ps[i++]) {
        while(cnt > 1 && crossOp(qs[cnt - 1], qs[cnt], ps[i]) <= 0) cnt--;
    }
    for(int i = n - 1, t = cnt; i >= 1; qs[++cnt] = ps[i--]) {
        while(cnt > t && crossOp(qs[cnt - 1], qs[cnt], ps[i]) <= 0) cnt--;
    }
    qs.resize(cnt); // 去除了最后一个重复的点
    return qs;
}

// 不严格凸包(考虑共线)
// 使用前必须对点进行去重
vector<P> convexHullNonStrict(vector<P>& ps) {
    int n = ps.size() - 1;
    if(n <= 1) return ps;
    sort(ps.begin() + 1, ps.begin() + n + 1); // normal sort
    vector<P> qs(2 * n + 1);
    int cnt = 0;
    for(int i = 1; i <= n; qs[++cnt] = ps[i++]) {
        while(cnt > 1 && crossOp(qs[cnt - 1], qs[cnt], ps[i]) < 0) cnt--;
    }
    for(int i = n - 1, t = cnt; i >= 1; qs[++cnt] = ps[i--]) {
        while(cnt > t && crossOp(qs[cnt - 1], qs[cnt], ps[i]) < 0) cnt--;
    }
    qs.resize(cnt); // 去除了最后一个重复的点
    return qs;
}

// 直线切凸多边形（测过）
// convexCut是用 直线cut出直线的左半边（即叉积为正的点集）
// 所以 convexCut(r, p[i], p[i] o (p[1 - i] - p[i]).rot90());
// 若 o 为 +，则表示 p[1 - i] 到 p[i] 的外侧（不包含 p[1 - i] 的区域）；
// 若 o 为 -，则表示 p[1 - i] 到 p[i] 的内测（包含 p[1 - i] 的区域）；
vector<P> convexCut(const vector<P>& ps, P q1, P q2) {
    vector<P> qs(1);
    int n = ps.size() - 1;
    for(int i = 1; i <= n; i++) {
        P p1 = ps[i], p2 = ps[i % n + 1];
        int d1 = crossOp(q1, q2, p1), d2 = crossOp(q1, q2, p2);
        if(d1 >= 0) qs.push_back(p1);
        if(d1 * d2 < 0) qs.push_back(getLL(p1, p2, q1, q2));
    }
    return qs;
}

// 旋转卡壳
db convexDiameter(vector<P>& ps) {
    int n = ps.size() - 1; if(n <= 1) return 0;
    int is = 1, js = 1;
    for(int k = 2; k <= n; k++) {
        is = ps[k] < ps[is] ? k : is;
        js = ps[js] < ps[k] ? k : js;
    }
    int i = is, j = js;
    db ret = ps[i].distTo(ps[j]);
    do {
        if((ps[i % n + 1] - ps[i]).det(ps[j % n + 1] - ps[j]) >= 0)
            j = j % n + 1;
        else
            i = i % n + 1;
        ret = max(ret, ps[i].distTo(ps[j]));
    } while(i != is || j != is);
    return ret;
}

// 半平面交
db halfPlane(vector<pair<P, P>>& a) {
    int n = a.size() - 1;
    auto compare = [](pair<P, P>& a, pair<P, P>& b) {
        P va = a.second - a.first;
        P vb = b.second - b.first;
        int qa = va.quad();
        int qb = vb.quad();
        if(qa != qb) return qa < qb;
        int v = sign(va.det(vb));
        return v == -1;
    };
    sort(a.begin() + 1, a.begin() + n + 1, [](pair<P, P>& a, pair<P, P>& b) {
        P va = a.second - a.first;
        P vb = b.second - b.first;
        int qa = va.quad();
        int qb = vb.quad();
        if(qa != qb) return qa < qb;
        int v = sign(va.det(vb));
        if(v != 0) return v == -1;
        return crossOp(a.first, a.second, b.second) < 0;
    });
    auto right = [](pair<P,P>& a, pair<P,P>& b, pair<P,P>& c) {
        P p = getLL(b.first, b.second, c.first, c.second);
        return crossOp(a.first, a.second, p) <= 0;
    };
    vector<pair<P, P>> q(n + 1);
    int h = 1, t = 1;
    q[1] = a[1];
    for(int i = 2; i <= n; i++) {
        if(compare(a[i], a[i-1])) continue;
        while(h < t && right(a[i], q[t], q[t-1])) t--;
        while(h < t && right(a[i], q[h], q[h+1])) h++;
        q[++t] = a[i];
    }
    while(h < t && right(q[h], q[t], q[t-1])) t--;

    if(h == t) return 0.0;

    vector<P> ans(1);
    for(int i = h, j = 1; i < t; i++, j++) {
        ans.push_back(getLL(q[i].first, q[i].second, q[i+1].first, q[i+1].second));
        P cp = getLL(q[i].first, q[i].second, q[i+1].first, q[i+1].second);
    }
    ans.push_back(getLL(q[t].first, q[t].second, q[h].first, q[h].second));

    return fabs(area(ans));
    // return ans;
}


/* 圆 */

// 判断两个圆之间的关系
int circleIntersect(P o1, db r1, P o2, db r2) {
    db d = o1.distTo(o2);
    if(cmp(d, r1 + r2) == 1) return 4;      // 相离
    if(cmp(d, r1 + r2) == 0) return 3;      // 外切
    if(cmp(d, abs(r1 - r2)) == 1) return 2; // 相交
    if(cmp(d, abs(r1 - r2)) == 0) return 1; // 内切
    return 0;                               // 内含
}

// 获取圆和直线的交点
vector<P> getCL(P o, db r, P p1, P p2) {
	if (cmp(abs((o-p1).det(p2-p1)/p1.distTo(p2)),r)>0) return {};
	db x = (p1-o).dot(p2-p1), y = (p2-p1).abs2(), d = x * x - y * ((p1-o).abs2() - r*r);
	d = max(d,(db)0.0); P m = p1 - (p2-p1)*(x/y), dr = (p2-p1)*(sqrt(d)/y);
	return {m-dr,m+dr}; //along dir: p1->p2
}

// 获取两个圆的交点
// need to check whether two circles are the same
vector<P> getCC(P o1, db r1, P o2, db r2) {
	db d = o1.distTo(o2); 
	if (cmp(d, r1 + r2) == 1) return {};
	if (cmp(d,abs(r1-r2))==-1) return {};
	d = min(d, r1 + r2);
	db y = (r1 * r1 + d * d - r2 * r2) / (2 * d), x = sqrt(r1 * r1 - y * y);
	P dr = (o2 - o1).unit();
	P q1 = o1 + dr * y, q2 = dr.rot90() * x;
	return {q1-q2,q1+q2}; // along circle 1
}

// 求两个圆的切线
// extanCC(r2>0); intanCC(r2<0); tanCP(r2=0)
vector<pair<P, P>> tanCC(P o1, db r1, P o2, db r2) {
	P d = o2 - o1;
	db dr = r1 - r2, d2 = d.abs2(), h2 = d2 - dr * dr;
	if (sign(d2) == 0|| sign(h2) < 0) return {};
	h2 = max((db)0.0, h2);
	vector<pair<P, P>> ret;
	for (db sign : {-1, 1}) {
		P v = (d * dr + d.rot90() * sqrt(h2) * sign) / d2;
		ret.push_back({o1 + v * r1, o2 + v * r2});
	}
	if (sign(h2) == 0) ret.pop_back();
	return ret;
}

// 求三角形内心
P inCenter(P A, P B, P C) {
	double a = (B - C).abs(), b = (C - A).abs(), c = (A - B).abs();
	return (A * a + B * b + C * c) / (a + b + c);
}

// 求三角形外心
P circumCenter(P a, P b, P c) {
	P bb = b - a, cc = c - a;
	double db = bb.abs2(), dc = cc.abs2(), d = 2 * bb.det(cc);
	return a - P(bb.y * dc - cc.y * db, cc.x * db - bb.x * dc) / d;
}

// 求三角形垂心
P othroCenter(P a, P b, P c) {
	P ba = b - a, ca = c - a, bc = b - c;
	double Y = ba.y * ca.y * bc.y,
	A = ca.x * ba.y - ba.x * ca.y,
	x0 = (Y + ca.x * ba.y * b.x - ba.x * ca.y * c.x) / A,
	y0 = -ba.x * (x0 - c.x) / ba.y + ca.y;
	return {x0, y0};
}

// 最小圆覆盖
pair<P, db> min_circle(vector<P>& ps) {
    random_shuffle(ps.begin(), ps.end());
    int n = ps.size() - 1;
    P o = ps[0]; db r = 0;
    for(int i = 2; i <= n; i++) if(o.distTo(ps[i]) > r + EPS) {
        o = ps[i]; r = 0;
        for(int j = 1; j < i; j++) if(o.distTo(ps[j]) > r + EPS) {
            o = (ps[i] + ps[j]) / 2; r = o.distTo(ps[i]);
            for(int k = 1; k < j; k++) if(o.distTo(ps[k]) > r + EPS) {
                o = circumCenter(ps[i], ps[j], ps[k]);
                r = o.distTo(ps[i]);
            }
        }
    }
    return {o, r};
}

// 求两个向量的夹角
db getTheta(P p1, P p2) {
    return atan2(p1.det(p2), p1.dot(p2));
}

// 求圆和三角形的交的有向面积
// 如果要求圆和简单多边形的面积，需要将圆心置于原点，然后再划分简单多边形求和
db areaCT(db r, P p1, P p2){
	vector<P> is = getCL(P(0,0),r,p1,p2);
	if(is.empty()) return r*r*getTheta(p1,p2)/2;
	bool b1 = cmp(p1.abs2(),r*r) == 1, b2 = cmp(p2.abs2(), r*r) == 1;
	if(b1 && b2){
		P md=(is[0]+is[1])/2;
		if(sign((p1-md).dot(p2-md)) <= 0) 
			return r*r*(getTheta(p1,is[0]) + getTheta(is[1],p2))/2 + is[0].det(is[1])/2;
		else return r*r*getTheta(p1,p2)/2;
	}
	if(b1) return (r*r*getTheta(p1,is[0]) + is[0].det(p2))/2;
	if(b2) return (p1.det(is[1]) + r*r*getTheta(is[1],p2))/2;
	return p1.det(p2)/2;
}

// 圆的面积并
//   利用格林公式，将面积信息转换为边界信息

// 欧拉公式
//   V - E + F = 1 + C
//   V顶点 E边 F面 C连通块


void work() {
    int T;
    cin >> T;
    vector<pair<P, P>> a(1);
    for(int i = 1; i <= T; i++) {
        int n;
        cin >> n;
        vector<P> b(n + 1);
        for(int j = 1; j <= n; j++) {
            b[j].read();
        }
        for(int j = 1; j <= n; j++) {
            a.push_back({b[j], b[j%n+1]});
        }
    }
    cout << fixed << setprecision(3) << halfPlane(a) << endl;
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