#include <cstdio>
#include <iostream>

using ll = long long;

bool cmp(ll a, ll b);

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
        ll n, r;
        read(n);
        r = n;
        while (n % 25 == 0) {
            if (cmp(r, r * 4)) {
                r = r * 4;
            }
            n /= 25;
        }
        while (n % 5 == 0) {
            if (cmp(r, r * 4)) {
                r = r * 4;
            }
            n /= 5;
        }
        std::cout << r << '\n';
    }

    return 0;
}

bool cmp(ll a, ll b) {
    ll at{a}, bt{b};
    int ac{};
    while (a % 10 == 0) {
        ac++;
        a /= 10;
    }
    int bc{};
    while (b % 10 == 0) {
        bc++;
        b /= 10;
    }
    return ac < bc ? true : at > bt;
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