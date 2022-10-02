#include <cstdio>
#include <iostream>

constexpr int MAX_N = 2056;

class BIT {
    int tree[MAX_N][MAX_N];

   public:
    BIT() = default;
    ~BIT() = default;

    void mod(const int& x, const int& y, const int& v);

    int query(const int& x, const int& y);
} t, ti, tj, tij;

void mod(const int& x, const int& y, const int& v);

int query(const int& x, const int& y);

char ch;
int n, m, a, b, c, d;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> ch >> n >> m;
    while (std::cin >> ch >> a >> b >> c >> d) {
        if (ch == 'L') {
            int delta;
            std::cin >> delta;
            mod(a, b, delta);
            mod(a, d + 1, -delta);
            mod(c + 1, b, -delta);
            mod(c + 1, d + 1, delta);
        } else {
            std::cout << query(c, d) - query(a - 1, d) - query(c, b - 1) +
                             query(a - 1, b - 1)
                      << '\n';
        }
    }

    return 0;
}

void BIT::mod(const int& x, const int& y, const int& v) {
    for (int i = x; i <= MAX_N; i += (i & -i)) {
        for (int j = y; j <= MAX_N; j += (j & -j)) {
            tree[i][j] += v;
        }
    }
}

int BIT::query(const int& x, const int& y) {
    int r{};
    for (int i = x; i >= 1; i -= (i & -i)) {
        for (int j = y; j >= 1; j -= (j & -j)) {
            r += tree[i][j];
        }
    }
    return r;
}

void mod(const int& x, const int& y, const int& v) {
    t.mod(x, y, v);
    ti.mod(x, y, v * x);
    tj.mod(x, y, v * y);
    tij.mod(x, y, v * x * y);
}

int query(const int& x, const int& y) {
    return t.query(x, y) * (x * y + x + y + 1) - ti.query(x, y) * (y + 1) -
           tj.query(x, y) * (x + 1) + tij.query(x, y);
}