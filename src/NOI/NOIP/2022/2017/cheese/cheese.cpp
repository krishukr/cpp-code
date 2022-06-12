#include <cmath>
#include <cstdio>
#include <iostream>
#include <memory>
#include <numeric>

constexpr int MAX_N = 1050;

class Solution {
   private:
    int fa[MAX_N];

    struct P {
        double x;
        double y;
        double z;

        double operator-(const P& a) const {
            return std::sqrt((x - a.x) * (x - a.x) + (y - a.y) * (y - a.y) +
                             (z - a.z) * (z - a.z));
        }

        void in();
    } p[MAX_N];

    int find(int x) { return (x == fa[x] ? x : (fa[x] = find(fa[x]))); }

    void merge(int a, int b) {
        if (find(a) != find(b)) {
            fa[find(a)] = find(b);
        }
    }

   public:
    Solution() = default;
    ~Solution() = default;

    void solve();
};

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    freopen("cheese.in", "r", stdin);
    freopen("cheese.out", "w", stdout);
    std::ios::sync_with_stdio(false);

    int T;
    read(T);
    while (T--) {
        auto solution = std::make_unique<Solution>();
        solution->solve();
    }

    std::cout << std::flush;
    fclose(stdin);
    fclose(stdout);
    return 0;
}

void Solution::solve() {
    int n, h, r;
    read(n, h, r);
    std::iota(fa, fa + n + 10, 0);

    for (int i = 1; i <= n; i++) {
        p[i].in();
        if (p[i].z - r <= 0) {
            merge(i, 0);
        }
        if (p[i].z + r >= h) {
            merge(i, n + 1);
        }

        for (int j = 1; j < i; j++) {
            if (p[i] - p[j] <= r + r) {
                merge(i, j);
            }
        }
    }

    std::cout << ((find(0) == find(n + 1)) ? "Yes" : "No") << '\n';
}

void Solution::P::in() { ::read(this->x, this->y, this->z); }

template <typename T>
T read() {
    T x = 0, f = 1;
    char ch = getchar();
    while (!isdigit(ch)) {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (isdigit(ch)) {
        x = x * 10 + ch - 48;
        ch = getchar();
    }
    return x * f;
}

template <typename T>
void read(T& t) {
    t = read<T>();
}

template <typename T, typename... Args>
void read(T& t, Args&... rest) {
    t = read<T>();
    read(rest...);
}