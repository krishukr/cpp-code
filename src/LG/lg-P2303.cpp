#include <cstdio>
#include <iostream>

using ll = long long;

ll calc(ll n);

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    ll n;
    read(n);
    std::cout << calc(n) << '\n';

    return 0;
}

ll calc(ll n) {
    ll r{n};
    for (ll i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            ll j{};
            while (n % i == 0) {
                j++;
                n /= i;
            }
            r /= i;
            r *= j * i - j + i;
        }
    }
    if (n > 1) {
        r /= n;
        r *= n + n - 1;
    }
    return r;
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