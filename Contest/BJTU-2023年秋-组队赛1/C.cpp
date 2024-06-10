#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'

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
    // P cross(P p) { return {y*p.z - z*p.y, z*p.x - x*p.z, x*p.y - y*p.x}; }

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

void work() {
    int n, L, Q;
    cin >> n >> L >> Q;

    P t(L, 0);
    P o(0, 0);
    db ans0 = L;

    vector<P> a(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i].x >> a[i].y;

    vector<db> d(n + 1);
    for(int i = 1; i <= n; i++) d[i] = a[i].distTo(t);
    for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) if(i != j) {
        if(a[i].y < 0
            && a[j].y < 0
            && crossOp(t, a[i], a[j]) >= 0
            && crossOp(o, a[i], a[j]) >= 0) {
            d[i] = max(d[i], a[i].distTo(a[j]) + a[j].distTo(t));
        } 

        if(a[i].y > 0
            && a[j].y > 0
            && crossOp(t, a[i], a[j]) <= 0
            && crossOp(o, a[i], a[j]) <= 0) {
            d[i] = max(d[i], a[i].distTo(a[j]) + a[j].distTo(t));
        }

        if((a[i].y > 0) != (a[j].y > 0)
            && crossOp(a[i], a[j], o) == crossOp(a[i], a[j], t)) {

            cout << fixed << setprecision(12);
            while(Q--) {
                cout << ans0 << endl;
            }
            return;
        }
    }

    // for(int i = 1; i <= n; i++) {
    //     cout << i << ": " << a[i].x << ", " << a[i].y << endl;
    // }

    cout << fixed << setprecision(12);

    while(Q--) {
        int u, v;
        cin >> u >> v;

        db ans = 0;

        if((a[u].y > 0) != (a[v].y > 0)) {
            ans = min(
                a[u].abs() + min(
                    a[u].distTo(a[v]) + a[v].distTo(t),
                    d[u]
                ),
                a[v].abs() + min(
                    a[v].distTo(a[u]) + a[u].distTo(t),
                    d[v]
                )
            );
        } else {
            ans = ans0;
        }

        cout << ans << endl;
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

  	   	  	 	  	  		 							   	