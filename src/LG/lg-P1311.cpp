#include <cstdio>
#include <iostream>

constexpr int MAX_N = 200050;

int s[MAX_N], a[MAX_N];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n, k, p, l{}, r{};
    read(n, k, p);
    for (int i = 1; i <= n; i++) {
        int b;
        read(a[i], b);
        if (b <= p) {
            for (int j = i; j > l; j--) {
                s[a[j]]++;
            }
            l = i;
            r += s[a[i]] - 1;
        } else {
            r += s[a[i]];
        }
    }
    std::cout << r << '\n';

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