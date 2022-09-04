#include <cstdio>
#include <iostream>

using ll = long long;

constexpr int MAX_N = 1000050;

int n, m;
int fra[MAX_N], inv[MAX_N];
int siz[MAX_N];
int ans{1};

template <typename T>
T quick_pow(T a, T b);

int combination(int a, int b);

int lucas(int a, int b);

void dfs(int x);

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    read(n, m);
    const auto k = std::min(n, m - 1);
    fra[0] = 1;
    for (int i = 1; i <= k; i++) {
        fra[i] = 1ll * fra[i - 1] * i % m;
    }
    inv[k] = (int)quick_pow<ll>(fra[k], m - 2);
    for (int i = k - 1; i >= 0; i--) {
        inv[i] = 1ll * inv[i + 1] * (i + 1) % m;
    }

    dfs(1);
    std::cout << ans << '\n';

    return 0;
}

template <typename T>
T quick_pow(T a, T b) {
    T r{1};
    while (b) {
        if (b & 1) {
            r = r * a % m;
        }
        a = a * a % m;
        b >>= 1;
    }
    return r;
}

int combination(int a, int b) {
    if (a < b) {
        return 0;
    } else {
        return 1ll * fra[a] * inv[b] % m * inv[a - b] % m;
    }
}

int lucas(int a, int b) {
    if (b == 0) {
        return 1;
    } else {
        return lucas(a / m, b / m) * combination(a % m, b % m) % m;
    }
}

#define lc (x << 1)
#define rc ((x << 1) | 1)

void dfs(int x) {
    siz[x] = 1;
    if (lc <= n) {
        dfs(lc);
        siz[x] += siz[lc];
    }
    if (rc <= n) {
        dfs(rc);
        siz[x] += siz[rc];
    }
    if (lc <= n) {
        ans = 1ll * ans * lucas(siz[x] - 1, siz[lc]) % m;
    }
}

#undef lc
#undef rc

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