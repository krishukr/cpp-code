#include <climits>
#include <cstdio>
#include <iostream>

constexpr int MAX_N = 100050;

int map[MAX_N], ux[MAX_N], uy[MAX_N], dx[MAX_N], dy[MAX_N];
bool vis[MAX_N];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

#define L(x, y) (((x)-1) * m + (y))
#define M(x, y) (map[L((x), (y))])

int main() {
    std::ios::sync_with_stdio(false);

    int n, m, k;
    read(n, m, k);
    std::fill(dx, dx + k + 1, INT_MAX);
    std::fill(dy, dy + k + 1, INT_MAX);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            read(map[L(i, j)]);
            if (!M(i, j)) {
                continue;
            }
            ux[M(i, j)] = std::max(ux[M(i, j)], i);
            uy[M(i, j)] = std::max(uy[M(i, j)], j);
            dx[M(i, j)] = std::min(dx[M(i, j)], i);
            dy[M(i, j)] = std::min(dy[M(i, j)], j);
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (!M(i, j)) {
                continue;
            }
            if (vis[M(i, j)]) {
                continue;
            }
            for (int l = 1; l <= k; l++) {
                if (M(i, j) == l) {
                    continue;
                }
                if (dx[l] <= i and i <= ux[l] and dy[l] <= j and j <= uy[l]) {
                    vis[M(i, j)] = true;
                    break;
                }
            }
        }
    }

    int res{k};
    for (int i = 1; i <= k; i++) {
        res -= vis[i];
    }
    res -= n == m and n == 1;
    std::cout << res << '\n';

    std::cout << std::flush;
    return 0;
}

#undef L
#undef M

template <typename T>
T read() {
    T x{}, f{1};
    int ch = getchar_unlocked();
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