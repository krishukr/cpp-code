#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <set>

using ll = long long;

constexpr int MAX_N = 400050;

int a[MAX_N];
std::multiset<int> s;

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n, m, q;
    read(n, m, q);
    ll sum{};
    for (int i = 1; i <= n; i++) {
        read(a[i]);
        s.insert(a[i]);
        sum += a[i];
    }
    std::cout << std::max((ll)(*(s.rbegin())), (ll)(std::ceil(1.0 * sum / m)))
              << '\n';

    while (q--) {
        int p, c;
        read(p, c);
        sum = sum - a[p] + c;
        s.erase(s.find(a[p]));
        s.insert(c);
        std::cout << std::max((ll)(*(s.rbegin())),
                              (ll)(std::ceil(1.0 * sum / m)))
                  << '\n';
        a[p] = c;
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