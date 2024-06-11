// Computation Geometry Template refer to dyh
// https://github.com/YXHXianYu/YXHXianYu-XCPC-Template
#include <bits/stdc++.h>
#define int long long
using namespace std;

/* 基础板子 */

typedef double f64; // 换longdouble时，需要同时替换alpha函数和getTheta函数
const f64 EPS = 1e-9;

inline int sign(f64 a) { return a < -EPS ? -1 : a > EPS; }

inline int cmp(f64 a, f64 b) { return sign(a - b); }

// 点P
struct P {
    f64 x, y;
    P(): x(0), y(0) {}
    P(f64 _x, f64 _y): x(_x), y(_y) {}
    P operator+(P p) const { return {x + p.x, y + p.y}; }
    P operator-(P p) const { return {x - p.x, y - p.y}; }
    P operator*(f64 d) const { return {x * d, y * d}; }
    P operator/(f64 d) const { return {x / d, y / d}; }

    bool operator<(P p) const {
        int c = cmp(x, p.x);
        if(c) return c == -1;
        return cmp(y, p.y) == -1;
    }

    // 这里的比较可能不满足传递性，因为这是基于EPS的比较
    bool operator==(P p) const {
        return cmp(x, p.x) == 0 && cmp(y, p.y) == 0;
    }

    f64 dot(P p) { return x * p.x + y * p.y; }
    f64 det(P p) { return x * p.y - y * p.x; }

    f64 distTo(P p) const { return (*this-p).abs(); }
    // return value in [-pi, pi]; longdouble ver is atan2l(y, x)
    f64 alpha() { return atan2(y, x); }
    void read() { cin >> x >> y; }
    f64 abs() const { return sqrt(abs2()); }
    f64 abs2() const { return x * x + y * y; }
    P unit() { return *this / abs(); }
    P rot90() { return P(-y, x); }
    P rot(f64 an) { return {x*cos(an) - y*sin(an), x*sin(an) + y*cos(an)}; }
    int quad() const { return sign(y) == 1 || (sign(y) == 0 && sign(x) >= 0); }
};

#define cross(p1, p2, p3) ((p2.x-p1.x)*(p3.y-p1.y)-(p3.x-p1.x)*(p2.y-p1.y))
#define crossOp(p1, p2, p3) (sign(cross(p1, p2, p3)))

// 判断 直线p1p2 和 直线q1q2 是否相交
bool isLL(P p1, P p2, P q1, P q2) {
    f64 a1 = cross(q1, q2, p1), a2 = -cross(q1, q2, p2);
    return sign(a1 + a2) != 0;
}

// 求交点
P getLL(P p1, P p2, P q1, P q2) {
    f64 a1 = cross(q1, q2, p1), a2 = -cross(q1, q2, p2);
    return (p1 * a2 + p2 * a1) / (a1 + a2);
}

// 点m 是否在 a 和 b 之间
bool isMiddle(f64 m, f64 a, f64 b) {
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

// Main
void work() {

    // freopen("input.txt", "r", stdin);

    size_t n, m;
    std::cin >> n >> m;

    using AABB = std::array<P, 2>;
    using Ray = std::array<P, 2>;

    std::vector<AABB> aabb(n);
    for (size_t i = 0; i < n; i++) {
        aabb[i][0].read();
        aabb[i][1].read();
    }

    std::vector<Ray> ray(m);
    for (size_t i = 0; i < m; i++) {
        ray[i][0].read();
        ray[i][1].read();
    }

    auto getIntersectionOfEdgeAndRay
        = [&](const P& p1, const P& p2, const Ray& ray) -> std::pair<bool, P> {
        
        P o = ray[0];
        P x = ray[0] + ray[1];

        // o in edge
        if (onSeg(p1, p2, o)) {
            // assert(false);
        }

        // same line (4)
        if (crossOp(o, x, p1) == 0 && crossOp(o, x, p2) == 0) {
            return std::make_pair(false, P());
        }

        // parellel (1)
        if (cmp(cross(o, x, p1), cross(o, x, p2)) == 0 || !isLL(o, x, p1, p2)) {
            return std::make_pair(false, P());
        }

        // get intersection
        P inter = getLL(o, x, p1, p2);

        // inter isn't in segment (1)
        if (!isMiddle(inter, p1, p2)) {
            return std::make_pair(false, P());
        }
        if (sign(ray[1].x) != cmp(inter.x, ray[0].x)) {
            return std::make_pair(false, P());
        }
        if (sign(ray[1].y) != cmp(inter.y, ray[0].y)) {
            return std::make_pair(false, P());
        }

        // (2)
        return std::make_pair(true, inter);
    };

    auto getIntersectionOfAABBAndRay
        = [&](const AABB& aabb, const Ray& ray) -> std::vector<P> {
        // 1. rebuild 4 edge
        P p[4] = {
            aabb[0],
            P(aabb[0].x, aabb[1].y),
            aabb[1],
            P(aabb[1].x, aabb[0].y)
        };

        // 2. iterate 4 edge
        std::vector<P> ans;
        for (size_t i = 0; i < 4; i++) {
            auto res = getIntersectionOfEdgeAndRay(p[i], p[(i+1)%4], ray);
            if (res.first) {
                ans.push_back(res.second);
                // std::cout << " - " << "(" << p[i].x << ", " << p[i].y << ") - (";
                // std::cout << p[(i+1)%4].x << ", " << p[(i+1)%4].y << "): ";
                // std::cout << res.second.x << ", " << res.second.y << std::endl;
            }
        }
        return ans;
    };

    for (size_t i = 0; i < m; i++) {
        std::vector<P> ans;
        for (size_t j = 0; j < n; j++) {
            auto res = getIntersectionOfAABBAndRay(aabb[j], ray[i]);
            for (const auto& x: res) {
                ans.push_back(x);
            }
        }
        if (ans.size() > 0) {
            stable_sort(ans.begin(), ans.end(), [&](const P& a, const P& b) {
                return cmp(ray[i][0].distTo(a), ray[i][0].distTo(b)) < 0;
            });
            ans.erase(std::unique(ans.begin(), ans.end()), ans.end());

            std::cout << ans.size() << " ";
            std::cout << std::fixed << std::setprecision(2);
            for (const auto& x: ans) {
                std::cout << (x.x+EPS) << " " << (x.y+EPS) << " ";
            }
            std::cout << '\n';
        } else {
            std::cout << -1 << '\n';
        }
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
