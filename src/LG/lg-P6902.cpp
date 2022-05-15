#include <algorithm>
#include <cstdio>
#include <iostream>

constexpr int MAX_N = 1000050;
constexpr int MAX_L = 26;

struct Q {
    int l;
    int r;
} q[MAX_N];

int p[MAX_L][MAX_N << 1];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n, k;
    read(n, k);

    for (int i = 1; i <= k; i++) {
        int l, r;
        read(l, r);
        if (l > r) {
            r += n;
        }
        q[i] = {l, r};
    }
    std::sort(q + 1, q + k + 1, [](const Q& x, const Q& y) {
        return x.l == y.l ? x.r < y.r : x.l < y.l;
    });

    for (int i = 1, j = 1, r = 0; i <= n + n; i++) {
        for (; j <= k and q[j].l <= i; j++) {
            r = std::max(r, q[j].r + 1);
        }
        p[0][i] = r;
    }

    for (int j = 0; j + 1 < MAX_L; j++) {
        for (int i = 1; i <= n + n; i++) {
            p[j + 1][i] = p[j][p[j][i]];
        }
    }

    int ans{0x3f3f3f3f};
    for (int i = 1; i <= n + n; i++) {
        int x = i, r = 0;
        for (int j = MAX_L - 1; j >= 0; j--) {
            if (n > p[j][x] - i) {
                x = p[j][x];
                r += (1 << j);
            }
        }
        x = p[0][x];
        r++;
        if (n <= x - i) {
            ans = std::min(ans, r);
        }
    }
    if (ans == 0x3f3f3f3f) {
        std::cout << "impossible" << '\n';
    } else {
        std::cout << ans << '\n';
    }

    return 0;
}

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