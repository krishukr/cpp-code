#include <cmath>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n, m;
    read(n, m);
    std::vector<int> p;
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            p.push_back(i);
            p.push_back(n / i);
        }
    }

    const auto mx = std::pow(n, m);
    std::vector<int> v;
    if (m == 1) {
        int ans{};
        for (const auto& i : p) {
            for (const auto& j : p) {
                if (i * j <= mx) {
                    ans++;
                }
            }
        }
        std::cout << ans << '\n';
    }

    return 0;
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