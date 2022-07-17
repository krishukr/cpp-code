#include <cstdio>
#include <iostream>

constexpr int MAX_N = 1000050;

int a[MAX_N], v[MAX_N];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n, m, al{}, ar{}, c{}, t{MAX_N};
    read(n, m);
    for (int i = 1; i <= n; i++) {
        read(a[i]);
    }

    int l, r;
    for (l = r = 1; r <= n; r++) {
        if (!v[a[r]]) {
            c++;
        }
        v[a[r]]++;
        while (v[a[l]] > 1) {
            v[a[l]]--;
            l++;
        }
        if (c == m) {
            if (t > r - l + 1) {
                t = r - l + 1;
                al = l;
                ar = r;
            }
        }
    }
    std::cout << al << ' ' << ar << '\n';

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