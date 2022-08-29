#include <cmath>
#include <cstdio>
#include <iostream>

using ll = long long;

ll ex_gcd(ll a, ll b, ll& x, ll& y);

template <typename T>
void out(const T& t);

template <typename T, typename... Args>
void out(const T& t, const Args&... rest);

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
        ll a, b, c, x{}, y{};
        read(a, b, c);
        const auto g = ex_gcd(a, b, x, y);
        if (c % g) {
            out(-1);
            continue;
        }

        x = x * c / g;
        y = y * c / g;
        const auto tx = b / g, ty = a / g;
        const ll k = std::ceil((1.0 - x) / tx);
        x += tx * k;
        y -= ty * k;
        if (y <= 0) {
            out(x, y + ty * (ll)std::ceil((1.0 - y) / ty));
        } else {
            out((y - 1) / ty + 1, x, (y - 1) % ty + 1, x + (y - 1) / ty * tx,
                y);
        }
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
void out(const T& t) {
    std::cout << t << '\n';
}

template <typename T, typename... Args>
void out(const T& t, const Args&... rest) {
    std::cout << t << ' ';
    out(rest...);
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