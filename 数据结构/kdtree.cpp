#include <algorithm>
#include <array>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <vector>

/**
 * By YXHXianYu, 2024.6.11
 * Support: Build, Traversal
 */
template <typename T, size_t N> class KDTree {
public:
    // data structure
    using Point   = std::array<T, N>;         // point[j]: j axis
    using Range   = std::array<Point, 2>;     // range[i][j]: i=0 min, i=1 max; j axis
    using PointID = std::pair<Point, size_t>; // Point + ID
    struct Node {
        Node*  l = nullptr;
        Node*  r = nullptr;
        size_t id;
        Point  point;
        Range  range;
    };

    KDTree(const std::vector<PointID>& points) : m_size(points.size()) {
        assert(m_size > 0);
        auto points_modifiable = points;
        m_root                 = new Node();
        build(points_modifiable, m_root, 0, m_size - 1, 0);
    }

    std::vector<size_t> traverse() {
        std::vector<size_t> result(m_size);
        int                 count = 0;
        traverse(result, count, m_root);
        return result;
    }

private:
    size_t m_size;
    Node*  m_root;

private:
    void build(std::vector<PointID>& points, Node* x, size_t L, size_t R, size_t axis) {
        assert(L <= R);

        // 1. only 1 point
        if (L == R) {
            x->id    = points[L].second;
            x->point = points[L].first;
            x->range = Range{points[L].first, points[L].first};
            return;
        }

        // 2. choose median of points based on the current axis
        size_t median = (R - L + 1) / 2;
        std::nth_element(points.begin() + L, points.begin() + median, points.begin() + R + 1, [&](PointID& a, PointID& b) {
            if (a.first[axis] != b.first[axis]) { return a.first[axis] < b.first[axis]; }
            for (size_t i = 1; i < N; i++) {
                size_t idx = (axis + i) % N;
                if (a.first[idx] != b.first[idx]) { return a.first[idx] < b.first[idx]; }
            }
            return false;
        });

        size_t mid = L + median;
        x->id      = points[mid].second;
        x->point   = points[mid].first;
        x->range   = Range{points[mid].first, points[mid].first};

        // 3. recursive build
        if (L < mid) {
            x->l = new Node();
            build(points, x->l, L, mid - 1, (axis + 1) % N);
            for (size_t i = 0; i < N; i++) {
                x->range[0][i] = std::min(x->range[0][i], x->l->range[0][i]);
                x->range[1][i] = std::max(x->range[1][i], x->l->range[1][i]);
            }
        }

        if (mid < R) {
            x->r = new Node();
            build(points, x->r, mid + 1, R, (axis + 1) % N);
            for (size_t i = 0; i < N; i++) {
                x->range[0][i] = std::min(x->range[0][i], x->r->range[0][i]);
                x->range[1][i] = std::max(x->range[1][i], x->r->range[1][i]);
            }
        }
    }

    void traverse(std::vector<size_t>& result, int& count, Node* x) {
        if (x == nullptr) return;
        result[count++] = x->id;
        traverse(result, count, x->l);
        traverse(result, count, x->r);
    }
};

int main() {

    // freopen("input1.txt", "r", stdin);

    const size_t T = 3;

    size_t n;
    std::cin >> n;

    using KDTreeTu = KDTree<int64_t, T>;

    std::vector<KDTreeTu::PointID> points(n);
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < T; j++) {
            std::cin >> points[i].first[j];
        }
        points[i].second = i;
    }

    KDTreeTu kdtree(points);

    auto result = kdtree.traverse();

    for (auto id : result) {
        std::cout << id + 1 << " ";
    }
    std::cout << std::endl;

    return 0;
}