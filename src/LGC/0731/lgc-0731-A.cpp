#include <cstdio>
#include <iostream>

using ll = long long;

constexpr int a[] = {13, 1, 2, 3, 5, 4, 4, 2, 2, 2};

ll calc(ll x);

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
        ll n, k;
        read(n, k);
        if (k < 100) {
            for (int i = 1; i <= k; i++) {
                n = calc(n);
            }
            std::cout << n << '\n';
            continue;
        }

        for (int i = 1; i <= 100; i++) {
            n = calc(n);
        }
        if (n == 1 or n == 2 or n == 3) {
            std::cout << n << '\n';
        } else if (n == 4) {
            n += (k - 100) & 1;
            std::cout << n << '\n';
        } else if (n == 5) {
            n -= (k - 100) & 1;
            std::cout << n << '\n';
        }
    }

    return 0;
}

ll calc(ll x) {
    ll r{};
    while (x) {
        r += a[x % 10];
        x /= 10;
    }
    if (!r and !x) {
        r += a[0];
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