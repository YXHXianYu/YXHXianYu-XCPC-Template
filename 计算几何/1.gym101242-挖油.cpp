#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;

/* 基础板子 */

typedef long long db;
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

    P reflect(P p) {
        return {2 * p.x - x, 2 * p.y - y};
    }

    int quad() const { return sign(y) == 1 || (sign(y) == 0 && sign(x) >= 0); }
};

#define cross(p1, p2, p3) ((p2.x-p1.x)*(p3.y-p1.y)-(p3.x-p1.x)*(p2.y-p1.y))
#define crossOp(p1, p2, p3) (sign(cross(p1, p2, p3)))

// 判断直线(p2-p1)和(q2-q1)是否相交
bool chkLL(P p1, P p2, P q1, P q2) {
    db a1 = cross(q1, q2, p1), a2 = -cross(q1, q2, p2);
    return sign(a1 + a2) != 0;
}

// 求交点
P isLL(P p1, P p2, P q1, P q2) {
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
        && crossOp(p1, p2, q1) * crossOp(p1, p2, q1) <= 0
        && crossOp(q1, q2, p1) * crossOp(q1, q2, p2) <= 0;
}

// 线段严格相交(不能交于端点)
bool isSS_strict(P p1, P p2, P q1, P q2) {
    return crossOp(p1, p2, q1) * crossOp(p1, p2, q1) < 0
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

void work() {
    int n;
    cin >> n;

    vector<pair<P, P>> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i].first.x >> a[i].second.x >> a[i].first.y;
        a[i].second.y = a[i].first.y;
        if(a[i].first.x > a[i].second.x) {
            swap(a[i].first.x, a[i].second.x);
        }
    }

    auto solve = [&](P b) -> db {
        vector<pair<P, int>> c;
        for(int i = 1; i <= n; i++) {
            if(a[i].first.y == b.y) continue;
            if(a[i].first.y < b.y) {
                c.push_back(make_pair(a[i].first.reflect(b), a[i].second.x - a[i].first.x));
                c.push_back(make_pair(a[i].second.reflect(b), -a[i].second.x + a[i].first.x));
            } else {
                c.push_back(make_pair(a[i].second, a[i].second.x - a[i].first.x));
                c.push_back(make_pair(a[i].first, -a[i].second.x + a[i].first.x));
            }
        }
        // a[i].first.y > b.y
        sort(c.begin(), c.end(), [&](pair<P, int>& p, pair<P, int>& q) {
            db v = sign((p.first - b).det((q.first - b)));
            if(v != 0) return v > 0;
            return p.second > q.second;
        });

        // cout << b.x << ", " << b.y << ": " << endl;
        // for(const auto& v: c) {
        //     cout << " - " << v.first.x << ", " << v.first.y << ", " << v.second << endl;
        // }

        int ans = 0;
        int cnt = 0;
        for(const auto& v: c) {
            cnt += v.second;
            ans = max(ans, cnt);
        }
        // cout << ans << endl;
        return ans;
    };

    db ans = 0;
    for(int i = 1; i <= n; i++) {
        ans = max(ans, solve(a[i].first) + a[i].second.x - a[i].first.x);
        ans = max(ans, solve(a[i].second) + a[i].second.x - a[i].first.x);
    }

    cout << ans << endl;
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