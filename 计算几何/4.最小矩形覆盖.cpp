#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;

/* 基础板子 */

typedef double db;
const db EPS = 1e-9;

inline int sign(db a) { return a < -EPS ? -1 : a > EPS; }

inline int cmp(db a, db b) { return sign(a - b); }

// 点P
struct P {
    db x, y;
    P() {}
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

    // return value in [-pi, pi]; longdouble ver is atan2l(y, x)
    db alpha() { return atan2(y, x); }

    db distTo(P p) { return (*this-p).abs(); }
    db abs() { return sqrt(abs2()); }
    db abs2() { return x * x + y * y; }
    P unit() { return *this / abs(); }
    P rot90() { return P(-y, x); }
    P rot(db an) { return {x*cos(an) - y*sin(an), x*sin(an) + y*cos(an)}; }

    int quad() const { return sign(y) == 1 || (sign(y) == 0 && sign(x) >= 0); }
};

#define cross(p1, p2, p3) ((p2.x-p1.x)*(p3.y-p1.y)-(p3.x-p1.x)*(p2.y-p1.y))
#define crossOp(p1, p2, p3) (sign(cross(p1, p2, p3)))

// 判断直线(p2-p1)和(q2-q1)是否相交
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
/* 重要约定，每个vector大小必须等于size+1 */

// 求简单多边形面积 (index start from 1)
db area(vector<P>& ps) {
    int n = ps.size() - 1;
    db ret = 0;
    for(int i = 1; i <= n; i++) {
        ret += ps[i].det(ps[i % n + 1]);
    }
    return ret / 2;
}

// 求点包含 (index start from 1) 2:inside, 1:on_seg, 0:outside
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

// 凸包 (index start from 1)
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

// 不严格凸包(考虑共线) (index start from 1)
// 使用前必须对点进行去重
vector<P> convexHullNonStrict(vector<P>& ps) {
    int n = ps.size() - 1;
    if(n <= 1) return ps;
    sort(ps.begin() + 1, ps.begin() + n + 1); // normal sort
    vector<P> qs(2 * n + 1);
    int cnt = 0;
    for(int i = 1; i <= n; qs[++cnt] = ps[i++]) {
        while(cnt > 1 && crossOp(qs[cnt - 2], qs[cnt - 1], ps[i]) < 0) cnt--;
    }
    for(int i = n - 1, t = cnt; i >= 1; qs[++cnt] = ps[i--]) {
        while(cnt > t && crossOp(qs[cnt - 2], qs[cnt - 1], ps[i]) < 0) cnt--;
    }
    qs.resize(cnt); // 去除了最后一个重复的点
    return qs;
}

// 直线切凸多边形
vector<P> convexCut(const vector<P>& ps, P q1, P q2) {
    auto qs = vector<P>(1);
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

void work() {
	int n;
	cin >> n;
	

	vector<P> p(n + 1);
	for(int i = 1; i <= n; i++) {
		cin >> p[i].x >> p[i].y;
	}
	p = convexHull(p);
	n = p.size() - 1;

	// cout << "ConvexHull: " << endl;
	// for(int i = 1; i <= n; i++) {
	// 	cout << p[i].x << ", " << p[i].y << endl;
	// }

	p.resize(2 * n + 1);
	for(int i = 1; i <= n; i++) p[i + n] = p[i];

	P d0 = p[2] - p[1];
	int R = 1, L = 1, U = 1;
	for(int i = 2; i <= n; i++) {
		P di = p[i] - p[1];
		while(d0.dot(di) > d0.dot(p[R] - p[1])) R = i;
		while(d0.dot(di) < d0.dot(p[L] - p[1])) L = i;
		while(d0.det(di) > d0.det(p[U] - p[1])) U = i;
	}

	// cout << R << ", " << L << ", " << U << endl;

	int n2 = 2 * n;
	db ans = 1e18;
	vector<P> result(4);
	for(int i = 1; i <= n; i++) {
		P d = p[i + 1] - p[i];
		while(R + 1 <= n2 && d.dot(p[R + 1] - p[i]) > d.dot(p[R] - p[i])) R++;
		while(L + 1 <= n2 && d.dot(p[L + 1] - p[i]) < d.dot(p[L] - p[i])) L++;
		while(U + 1 <= n2 && d.det(p[U + 1] - p[i]) > d.det(p[U] - p[i])) U++;

		db s1 = d.dot(p[R] - p[L]) / d.abs();
		db s2 = d.det(p[U] - p[i]) / d.abs();
		db S = s1 * s2;
		if(S < ans) {
			ans = S;
			// down: p[i], p[i]+d
			// up  : p[u], p[u]+d
			// righ: p[r], p[r]+d.rot90()
			// left: p[l], p[l]+d.rot90()
			result[0] = getLL(p[i], p[i] + d, p[L], p[L] + d.rot90());
			result[1] = getLL(p[i], p[i] + d, p[R], p[R] + d.rot90());
			result[2] = getLL(p[U], p[U] + d, p[R], p[R] + d.rot90());
			result[3] = getLL(p[U], p[U] + d, p[L], p[L] + d.rot90());
		}
	}

	int mnp = 0;
	for(int i = 1; i <= 3; i++) {
		if(cmp(result[i].y, result[mnp].y) < 0) {
			mnp = i;
		} else if(cmp(result[i].y, result[mnp].y) == 0 && cmp(result[i].x, result[mnp].x) < 0) {
			mnp = i;
		}
	}

	cout << fixed << setprecision(7) << ans << endl;
	for(int i = 0; i <= 3; i++) {
		cout << result[(i+mnp)%4].x << " " << result[(i+mnp)%4].y << endl;
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
