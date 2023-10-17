#include <cstdio>
#include <iostream>
#include <numeric>

using ll = long long;

constexpr int MAX_N = 1050;
constexpr int MAX_M = MAX_N * MAX_N;
constexpr int MOD = 1e9 + 7;

bool map[MAX_N][MAX_N];

#define L(x, y) ((x - 1) * m + y)

int fa[MAX_M], vis[MAX_M];

int find(int x) { return fa[x] == x ? x : (fa[x] = find(fa[x])); }

void merge(int x, int y);

ll dp[MAX_M];

template <typename T>
T read();

template <>
char read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n, m;
    read(n, m);
    std::iota(fa + 1, fa + n * m + 1, 1);
    std::fill(dp + 1, dp + n * m + 1, 1);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            map[i][j] = read<char>() == '.';
        }
    }

    for (int i = n - 1; i > 1; i--) {
        for (int j = 2; j < m; j++) {
            if (map[i][j]) {
                if (map[i + 1][j]) {
                    merge(L(i + 1, j), L(i, j));
                }
                if (map[i][j + 1]) {
                    merge(L(i, j + 1), L(i, j));
                }
            }
        }
        for (int j = 2; j < m; j++) {
            if (map[i][j]) {
                const auto fx = find(L(i, j));
                if (vis[fx] != i) {
                    dp[fx]++;
                    vis[fx] = i;
                }
            }
        }
    }

    ll ans{1};
    for (int i = 2; i < n; i++) {
        for (int j = 2; j < m; j++) {
            const auto l = L(i, j);
            if (find(l) == l) {
                ans *= dp[l];
                ans %= MOD;
            }
        }
    }
    std::cout << ans << '\n';

    std::cout << std::flush;
    return 0;
}

void merge(int x, int y) {
    const auto fx = find(x), fy = find(y);
    if (fx != fy) {
        fa[fx] = fy;
        dp[fy] = dp[fx] * dp[fy] % MOD;
    }
}

#undef L

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

template <>
char read() {
    char ch = getchar_unlocked();
    while (ch != '.' and ch != '#') {
        ch = getchar_unlocked();
    }
    return ch;
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
