#include <climits>
#include <cstdio>
#include <iostream>

using ll = long long;

constexpr int MAX_N = 200050;

int w[MAX_N], v[MAX_N];
int ql[MAX_N], qr[MAX_N];
ll f[MAX_N], g[MAX_N];
int n, m;
ll ans = LLONG_MAX, S;

bool check(int x);

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    read(n, m, S);
    for (int i = 1; i <= n; i++) {
        read(w[i], v[i]);
    }
    for (int i = 1; i <= m; i++) {
        read(ql[i], qr[i]);
    }

    int l = 0, r = 1000050;
    while (l <= r) {
        const auto mid = (l + r) >> 1;
        if (check(mid)) {
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    std::cout << ans << '\n';

    return 0;
}

bool check(int x) {
    for (int i = 1; i <= n; i++) {
        if (x < w[i]) {
            f[i] = f[i - 1] + 1;
            g[i] = g[i - 1] + v[i];
        } else {
            f[i] = f[i - 1];
            g[i] = g[i - 1];
        }
    }

    ll cnt{S};
    for (int i = 1; i <= m; i++) {
        cnt -= 1ll * (f[qr[i]] - f[ql[i] - 1]) * (g[qr[i]] - g[ql[i] - 1]);
    }
    ans = std::min(ans, std::abs(cnt));
    return cnt < 0;
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