#include <algorithm>
#include <climits>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>

using ll = long long;

constexpr int MAX_N = 200050;

struct Q {
    int x, y, p, q;
} a[MAX_N];

std::vector<int> b[MAX_N], idx[MAX_N];
ll f[MAX_N];
int cnt;

int A, B, C;

inline int calc(int x);

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n, m;
    read(n, m, A, B, C);
    for (int i = 1; i <= m; i++) {
        read(a[i].x, a[i].y, a[i].p, a[i].q);
        b[a[i].y].push_back(a[i].q);
    }
    b[1].push_back(0);

    for (int i = 1; i <= n; i++) {
        std::sort(b[i].begin(), b[i].end());
        b[i].resize(std::unique(b[i].begin(), b[i].end()) - b[i].begin());
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= b[i].size(); j++) {
            idx[i].push_back(++cnt);
        }
    }

    std::fill(f, f + m + 10, LLONG_MAX >> 1);
    f[1] = 0;
    std::sort(a + 1, a + m + 1,
              [](const Q& x, const Q& y) { return x.p < y.p; });

    for (int i = 1; i <= m; i++) {
        int x = a[i].x, y = a[i].y, crt;
        for (int j = 0; j < b[y].size(); j++) {
            if (b[y][j] == a[i].q) {
                crt = idx[y][j];
            }
        }
        for (int j = 0; j < b[x].size(); j++) {
            if (a[i].p < b[x][j]) {
                break;
            }
            f[crt] = std::min(f[crt], f[idx[x][j]] + calc(a[i].p - b[x][j]));
        }
    }

    ll ans = LLONG_MAX;
    for (int i = 0; i < b[n].size(); i++) {
        ans = std::min(ans, f[idx[n][i]] + b[n][i]);
    }
    std::cout << ans << '\n';

    return 0;
}

inline int calc(int x) { return A * x * x + B * x + C; }

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