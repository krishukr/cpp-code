#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>

constexpr int MAX_N = 100050;

int a[MAX_N], b[MAX_N];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n;
    read(n);
    for (int i = 1; i <= n; i++) {
        a[read<int>()] = i;
    }
    for (int i = 1; i <= n; i++) {
        b[i] = a[read<int>()];
    }

    std::vector<int> f;
    for (int i = 1; i <= n; i++) {
        if (f.empty() or f.back() < b[i]) {
            f.push_back(b[i]);
        } else {
            *std::lower_bound(f.begin(), f.end(), b[i]) = b[i];
        }
    }
    std::cout << f.size() << '\n';

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