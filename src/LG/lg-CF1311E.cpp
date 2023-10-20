#include <cstdio>
#include <iostream>
#include <memory>

constexpr int MAX_N = 5050;

class Solution {
    int dep[MAX_N], fa[MAX_N], chn[MAX_N];
    bool lef[MAX_N];

   public:
    void solve();
};

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int T;
    read(T);
    while (T--) {
        auto solution = std::make_unique<Solution>();
        solution->solve();
    }

    std::cout << std::flush;
    return 0;
}

void Solution::solve() {
    int n, d, m{};
    read(n, d);
    for (int i = 2; i <= n; i++) {
        fa[i] = i >> 1;
        dep[i] = dep[fa[i]] + 1;
        d -= dep[i];
        m = std::max(m, dep[i]);
    }
    if (d < 0) {
        std::cout << "NO\n";
        return;
    }

    for (int i = n; i; i = fa[i]) {
        lef[i] = true;
        chn[dep[i]] = i;
    }
    for (int i = n - 1; i >= 1; i--) {
        if (lef[i]) {
            continue;
        }
        int x{m};
        while (d and dep[fa[i]] < x) {
            fa[i] = chn[dep[fa[i]] + 1];
            dep[i] = dep[fa[i]] + 1;
            if (m < dep[i]) {
                m++;
                chn[m] = i;
                lef[i] = true;
            }
            d--;
        }
    }

    if (d) {
        std::cout << "NO\n";
        return;
    }
    std::cout << "YES\n";
    for (int i = 2; i <= n; i++) {
        std::cout << fa[i] << ' ';
    }
    std::cout << '\n';
}

template <typename T>
T read() {
    T x{}, f{1};
    int ch = getchar();
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