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
    using Point = std::array<T, N>;     // point[j]: j axis
    using Range = std::array<Point, 2>; // range[i][j]: i=0 min, i=1 max; j axis
    struct Node {
        Node*  l;
        Node*  r;
        size_t id;
        Point  point;
        Range  range;
    };

    KDTree(const std::vector<Point>& points) : m_size(points.size()) {
        assert(m_size > 0);
        auto points_modifiable = points;
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
    void build(std::vector<Point>& points, Node* x, size_t L, size_t R, size_t axis) {
        assert(L <= R);

        // 0. new node
        x = new Node();

        // 1. only 1 point
        if (L == R) {
            x->id    = L;
            x->point = points[L];
            x->range = Range{points[L], points[L]};
            return;
        }

        // 2. choose median of points based on the current axis
        size_t median = (R - L + 1) / 2;
        std::nth_element(points.begin(), points.begin() + median, points.end(), [&](Point& a, Point& b) { return a[axis] < b[axis]; });
        x->id    = L + median;
        x->point = points[L + median];
        x->range = Range{points[L + median], points[L + median]};

        // 3. recursive build
        if (L < median) {
            build(points, x->l, L, median - 1, (axis + 1) % N);
            for (size_t i = 0; i < N; i++) {
                x->range[0][i] = std::min(x->range[0][i], x->l->range[0][i]);
                x->range[1][i] = std::min(x->range[1][i], x->l->range[1][i]);
            }
        }
        if (median < R) {
            build(points, x->r, median + 1, R, (axis + 1) % N);
            for (size_t i = 0; i < N; i++) {
                x->range[0][i] = std::min(x->range[0][i], x->r->range[0][i]);
                x->range[1][i] = std::min(x->range[1][i], x->r->range[1][i]);
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

    const size_t T = 3;

    size_t n;
    std::cin >> n;

    using KDTreeTu = KDTree<uint64_t, T>;

    std::vector<KDTreeTu::Point> points(n);
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < T; j++) {
            std::cin >> points[i][j];
        }
    }

    std::cout << "1" << std::endl;
    KDTreeTu kdtree(points);

    std::cout << "2" << std::endl;

    auto result = kdtree.traverse();
    std::cout << "3" << std::endl;

    for (auto id : result) {
        std::cout << id << " ";
    }
    std::cout << std::endl;

    return 0;
}