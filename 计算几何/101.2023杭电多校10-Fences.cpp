// Computation Geometry Template refer to dyh
#include <bits/stdc++.h>
#define int long long
using namespace std;

typedef double db;
const db EPS = 1e-9;

inline int sign(db a) { return a < -EPS ? -1 : a > EPS; }

inline int cmp(db a, db b) { return sign(a - b); }

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

    bool operator==(P p) const {
        return cmp(x, p.x) == 0 && cmp(y, p.y) == 0;
    }
    bool operator!=(P p) const {
        return cmp(x, p.x) != 0 || cmp(y, p.y) != 0;
    }

    db dot(P p) { return x * p.x + y * p.y; }
    db det(const P& p) const { return x * p.y - y * p.x; }

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
    qs.resize(cnt);
    return qs;
}

void work() {
    int n, k;
    cin >> n >> k;
    
    vector<P> a(n + 1);
    for(int i = 1; i <= n; i++) {
        int x, y;
        cin >> x >> y;
        a[i].x = x;
        a[i].y = y;
    }

    auto aa = a;
    auto an = n;

    P origin = a[k];
    for(int i = 1; i <= n; i++) a[i] = a[i] - origin;
    
    auto hull = convexHullNonStrict(a);
    int N = hull.size() - 1;
    
    db sum = 0;
    for(int i = 1; i <= N; i++) {
        int u = i, v = i % N + 1;
        sum += hull[u].distTo(hull[v]);
    }

    origin = {0.0, 0.0};
    for(int i = 1; i <= N; i++) {
        if(hull[i] == origin) {
            cout << fixed << setprecision(3) << sum << endl;
            return;
        }
    }

    int nn = 0;
    for(int i = 1; i <= n; i++) if(a[i] != origin) a[++nn] = a[i];
    n = nn;
    a.resize(n + 1);

    sort(a.begin() + 1, a.end(), [](const P& a, const P& b) {
        if(a == P{0, 0}) return true;
        if(b == P{0, 0}) return false;
        int qa = a.quad(), qb = b.quad();
        if(qa != qb) return qa < qb;
        else return sign(a.det(b)) > 0;
    });

    
    int n2 = n * 2;
    a.resize(n2 + 1);
    for(int i = 1; i <= n; i++) a[n+i] = a[i];

    db ans = 1e18;
    int L = 1, R = 1;
    
    vector<db> f(n2 + 1);
    vector<db> g(n2 + 1);
    vector<P> stk(n2 + 1);
    
    for(int i = 1; i <= N; i++) {
        int t0 = (i == 1 ? N : i - 1);
        int t1 = i;
        int t2 = i % N + 1;
        int t3 = t2 % N + 1;
        
        while(a[L] != hull[t1] && L <= n2) L++;
        R = L + 1;
        while(a[R] != hull[t2] && R <= n2) R++;
        
        int top = 0;
        db cnt = 0;
        stk[++top] = hull[t0];
        stk[++top] = a[L];
        f[L] = cnt;
        for(int j = L + 1; j < R; j++) {
            while(top > 1 && crossOp(stk[top - 1], stk[top], a[j]) < 0) {
                cnt -= stk[top - 1].distTo(stk[top]);
                top--;
            }
            stk[++top] = a[j];
            cnt += stk[top - 1].distTo(stk[top]);
            f[j] = cnt;
        }
        
        top = 0;
        cnt = 0;
        stk[++top] = hull[t3];
        stk[++top] = a[R];
        g[R] = cnt;
        for(int j = R - 1; j > L; j--) {
            while(top > 1 && crossOp(stk[top - 1], stk[top], a[j]) > 0) {
                cnt -= stk[top - 1].distTo(stk[top]);
                top--;
            }
            stk[++top] = a[j];
            cnt += stk[top - 1].distTo(stk[top]);
            g[j] = cnt;
        }
        
        cnt = sum - hull[t1].distTo(hull[t2]);
        for(int j = L; j < R; j++) {
            db v = f[j] + g[j + 1] + a[j].abs() + a[j + 1].abs();

            ans = min(ans, v + cnt);
        }
    }
    
    cout << fixed << setprecision(3) << ans << endl;
}

signed main() {
//    myassert(false);
    // freopen("1.in", "r", stdin);
    // freopen("1.out", "w", stdout);
    
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        work();
    }

    return 0;
}