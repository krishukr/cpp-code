#include <cstdio>
#include <iostream>

using ll = long long;
using lll = __int128_t;

constexpr int MAX_N = 40000050;
constexpr ll MOD = 1ll << 30;

int b[MAX_N];
ll s[MAX_N], q[MAX_N];
int f[MAX_N];
int h, t;

std::ostream& operator<<(std::ostream& o, const lll& a);

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n, _type;
    read(n, _type);
    if (_type) {
        int x, y, z, m, j{1};
        read(x, y, z, b[1], b[2], m);
        for (int i = 1; i <= m; i++) {
            int p, l, r;
            read(p, l, r);
            for (; j <= p; j++) {
                if (!b[j]) {
                    b[j] =
                        ((1ll * x * b[j - 1] % MOD + 1ll * y * b[j - 2] % MOD) %
                             MOD +
                         z) %
                        MOD;
                }
                s[j] = s[j - 1] + b[j] % (r - l + 1) + l;
            }
        }
    } else {
        for (int i = 1; i <= n; i++) {
            read(s[i]);
            s[i] += s[i - 1];
        }
    }

    for (int i = 1; i <= n; i++) {
        while (h < t and (s[q[h + 1]] * 2 - s[f[q[h + 1]]]) <= s[i]) {
            h++;
        }
        f[i] = q[h];
        while (h < t and (s[i] * 2 - s[f[i]]) <= (s[q[t]] * 2 - s[f[q[t]]])) {
            t--;
        }
        q[++t] = i;
    }
    lll ans{};
    while (n) {
        const lll t = s[n] - s[f[n]];
        ans += t * t;
        n = f[n];
    }
    std::cout << ans << '\n';

    return 0;
}

std::ostream& operator<<(std::ostream& o, const lll& a) {
    if (a < 0) {
        return (o << '-' << (-a));
    }
    if (a > 9) {
        o << (a / 10);
    }
    return (o << (int)(a % 10));
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