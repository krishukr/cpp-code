#include <cstdio>
#include <iostream>
#include <unordered_map>

constexpr int MAX_N = 200050;

int a[MAX_N];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    std::unordered_map<int, int> m;
    int n, c;
    read(n, c);
    for (int i = 1; i <= n; i++) {
        read(a[i]);
        m[a[i]]++;
        a[i] -= c;
    }

    long long ans{};
    for (int i = 1; i <= n; i++) {
        ans += m[a[i]];
    }
    std::cout << ans << '\n';

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