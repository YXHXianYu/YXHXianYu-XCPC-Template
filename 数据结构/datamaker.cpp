#include <bits/stdc++.h>
using namespace std;

int main() {
    srand(time(0));

    freopen("input1.txt", "w", stdout);

    size_t n = 20;
    std::cout << n << std::endl;

    const int M = -1000;

    for (int i = 0; i < n; i++) {
        std::cout << i + M << " " << i + M << " " << i + M << '\n';
    }

    return 0;
}