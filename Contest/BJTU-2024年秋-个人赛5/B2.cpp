// #include<bits/stdc++.h>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <cassert>

struct Point {
    long long x, y;
    Point(long long _x, long long _y) {
        x = _x; y = _y;
    }
};

Point solve(long long n, long long v) {
    if (n == 0) return Point(0, 0);

    long long len = 1LL << (2 * n - 2);
    long long len2 = 1LL << (n - 1);
    long long len3 = 1LL << n;
    Point x = solve(n - 1, v % len);
    
    long long t = v / len;
    if (t == 0) {
        return Point(x.y, x.x);
    } else if (t == 1) {
        return Point(x.x, x.y + len2);
    } else if (t == 2) {
        return Point(x.x + len2, x.y + len2);
    } else if (t == 3) {
        return Point(len3 - 1 - x.y, len2 - 1 - x.x);
    } else {
        assert(false);
    }
}

void work() {
    long long n, h, o;
    std::cin >> n >> h >> o;

    if (h == o) {
        std::cout << 0 << '\n';
        return;
    }

    assert(n <= 31);
    // assert(n <= 30) will lead to RuntimeError

    Point hv = solve(n, h - 1);
    Point ov = solve(n, o - 1);

    /*
    __int128 dx = hv.x - ov.x;
    __int128 dy = hv.y - ov.y;
    __int128 target = dx * dx + dy * dy;

    target *= 10000;

    __int128 L = 0, R = 303700050000;
    while(R - L > 1) {
        __int128 mid = (L + R) >> 1;
        if (mid * mid <= target) {
            L = mid;
        } else {
            R = mid;
        }
    }
    L = (L + 5) / 10;
    std::cout << (unsigned long long)L << '\n';
    */

    long double dx = hv.x - ov.x;
    long double dy = hv.y - ov.y;
    std::cout << (long long)(10.0 * sqrt(dx * dx + dy * dy)) << '\n';
}

int main() {
    //std::ios::sync_with_stdio(false);
    //std::cin.tie(0);

    long long t = 1;
    std::cin >> t;
    while (t--) {
        work();
    }

    return 0;
}

