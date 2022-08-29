#include <cstdio>
#include <iostream>

using ll = long long;

ll ex_gcd(ll a, ll b, ll& x, ll& y);

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    ll x, y, m, n, l, xx{}, yy{};
    read(x, y, m, n, l);
    ll a = x - y, b = n - m;
    if (b < 0) {
        a = -a;
        b = -b;
    }
    const auto g = ex_gcd(b, l, xx, yy);
    if (a % g) {
        std::cout << "Impossible\n";
    } else {
        const auto p = l / g;
        std::cout << ((xx * (a / g)) % p + p) % p << '\n';
    }

    return 0;
}

ll ex_gcd(ll a, ll b, ll& x, ll& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll ans = ex_gcd(b, a % b, y, x);
    y -= (a / b) * x;
    return ans;
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