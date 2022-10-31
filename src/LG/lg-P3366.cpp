#include <algorithm>
#include <cstdio>
#include <iostream>

constexpr int MAX_N = 200050;

int fa[MAX_N];

struct {
    int x;
    int y;
    int z;
} e[MAX_N];

int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n, m;
    read(n, m);
    for (int i = 1; i <= n; i++) {
        fa[i] = i;
    }
    for (int i = 1; i <= m; i++) {
        int x, y, z;
        read(x, y, z);
        e[i] = {x, y, z};
    }

    std::sort(e + 1, e + m + 1,
              [](const auto& a, const auto& b) { return a.z < b.z; });
    int ans{}, cnt{};
    for (int i = 1; i <= m; i++) {
        const auto x = find(e[i].x), y = find(e[i].y);
        if (x == y) {
            continue;
        }
        ans += e[i].z;
        fa[x] = y;
        cnt++;

        if (cnt == n - 1) {
            std::cout << ans << '\n';
            return 0;
        }
    }
    std::cout << "orz" << '\n';

    return 0;
}

template <typename T>
T read() {
    T x = 0, f = 1;
    char ch = getchar_unlocked();
    while (!isdigit(ch)) {
        if (ch == '-') f = -1;
        ch = getchar_unlocked();
    }
    while (isdigit(ch)) {
        x = x * 10 + ch - 48;
        ch = getchar_unlocked();
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