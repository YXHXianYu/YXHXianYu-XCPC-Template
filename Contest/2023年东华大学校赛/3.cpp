#include <bits/stdc++.h>
using namespace std;
#define int long long

vector<pair<int, int>> M = {
    {65, 80}, {72, 61}, {61, 55}, {47, 80}
};
vector<pair<int, int>> L = {
    {47, 80}, {61, 55}, {54, 36}, {41, 40}, {35, 67}
};
vector<pair<int, int>> S = {
    {35, 67}, {41, 40}, {16, 30}, {7, 57}
};
vector<pair<int, int>> I = {
    {93, 37}, {93, 19}, {65, 4}, {58, 26}
};

int X, Y;

void work() {

    auto crossProduct = [&](int x, int y, int a, int b) {
        return (x * b - y * a) > 0;
    };

    auto inside = [&](int x, int y, const vector<pair<int, int>>& s) {
        int n = s.size();
        int result = crossProduct(x-s[n-1].first, y-s[n-1].second,
                                  s[0].first-s[n-1].first, s[0].second-s[n-1].second);
        for(int i = 1; i < n; i++) {
            int ret = crossProduct(x-s[i-1].first, y-s[i-1].second,
                                   s[i].first-s[i-1].first, s[i].second-s[i-1].second);
            if(result != ret) return false;
        }
        return true;
    };

    if(inside(X, Y, M)) {
        cout << "Mondstadt" << endl;
    } else if(inside(X, Y, L)) {
        cout << "Liyue" << endl;
    } else if(inside(X, Y, S)) {
        cout << "Sumeru" << endl;
    } else if(inside(X, Y, I)) {
        cout << "Inazuma" << endl;
    } else {
        assert(false);
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    while(cin >> X >> Y) {
        work();
    }

    return 0;
}