#include<bits/stdc++.h>
using i64 = long long;

void work() {
    i64 n, h, o;
    std::cin >> n >> h >> o;

    if (h == o) {
        std::cout << 0 << '\n';
        return;
    }

    i64 hx = 0, hy = 0, ox = 0, oy = 0;

    i64 h_cur_dir = 0; // 0left 1up 2right 3down
    i64 o_cur_dir = 0;
    for (i64 i = 0, j = 1LL << (2 * n - 2), k = 1LL << (n - 1); i < n; i++, j >>= 2, k >>= 1) {
        i64 hv = (h - 1) / j % 4;

        i64 tmp = 0;
        if (h_cur_dir == 0) {
            tmp = hv;
        } else if (h_cur_dir == 1) {
            tmp = hv == 0 ? 0 :
                  hv == 1 ? 3 :
                  hv == 2 ? 2 :
                  1;
        } else if (h_cur_dir == 2) {
            tmp = hv == 0 ? 2 :
                  hv == 1 ? 3 :
                  hv == 2 ? 0 :
                  1;
        } else {
            tmp = hv == 0 ? 2 :
                  hv == 1 ? 1 :
                  hv == 2 ? 0 :
                  3;
        }
        if (h_cur_dir == 0) {
            h_cur_dir = hv == 0 ? 1 :
                        hv == 1 ? 0 :
                        hv == 2 ? 0 :
                        3;
        } else if (h_cur_dir == 1) {
            h_cur_dir = hv == 0 ? 0 :
                        hv == 1 ? 1 :
                        hv == 2 ? 1 :
                        2;
        } else if (h_cur_dir == 2) {
            h_cur_dir = hv == 0 ? 2 :
                        hv == 1 ? 3 :
                        hv == 2 ? 0 :
                        1;
        } else {
            h_cur_dir = hv == 0 ? 2 :
                        hv == 1 ? 1 :
                        hv == 2 ? 0 :
                        3;
        }

        // std::cout << i << ", h_cur_dir=" << h_cur_dir << ", hv=" << hv << "; tmp=" << tmp << '\n';

        if (tmp == 0) {
            // do nothing
        } else if (tmp == 1) {
            hx += k;
        } else if (tmp == 2) {
            hx += k;
            hy += k;
        } else { // tmp == 3
            hy += k;
        }

        i64 ov = (o - 1) / j % 4;

        if (o_cur_dir == 0) {
            tmp = ov;
        } else if (o_cur_dir == 1) {
            tmp = ov == 0 ? 0 :
                  ov == 1 ? 3 :
                  ov == 2 ? 2 :
                  1;
        } else if (o_cur_dir == 2) {
            tmp = ov == 0 ? 2 :
                  ov == 1 ? 3 :
                  ov == 2 ? 0 :
                  1;
        } else {
            tmp = ov == 0 ? 2 :
                  ov == 1 ? 1 :
                  ov == 2 ? 0 :
                  3;
        }

        if (o_cur_dir == 0) {
            o_cur_dir = ov == 0 ? 1 :
                        ov == 1 ? 0 :
                        ov == 2 ? 0 :
                        3;
        } else if (o_cur_dir == 1) {
            o_cur_dir = ov == 0 ? 0 :
                        ov == 1 ? 1 :
                        ov == 2 ? 1 :
                        2;
        } else if (o_cur_dir == 2) {
            o_cur_dir = ov == 0 ? 2 :
                        ov == 1 ? 3 :
                        ov == 2 ? 0 :
                        1;
        } else {
            o_cur_dir = ov == 0 ? 2 :
                        ov == 1 ? 1 :
                        ov == 2 ? 0 :
                        3;
        }

        // std::cout << i << ", o_cur_dir=" << o_cur_dir << ", ov=" << ov << " tmp=" << tmp << '\n';

        if (tmp == 0) {
            // do nothing
        } else if (tmp == 1) {
            ox += k;
        } else if (tmp == 2) {
            ox += k;
            oy += k;
        } else { // tmp == 3
            oy += k;
        }
    }

    // std::cout << "(" << hx << ", " << hy << "); (" << ox << ", " << oy << ")\n";

    i64 dx = hx - ox;
    i64 dy = hy - oy;
    dx *= 10;
    dy *= 10;
    double v = dx * dx + dy * dy;
    i64 ans = sqrt(v);

    std::cout << ans << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    i64 t = 1;
    std::cin >> t;
    while (t--) {
        work();
    }

    return 0;
}
