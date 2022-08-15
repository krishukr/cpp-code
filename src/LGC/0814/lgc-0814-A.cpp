#include <cstdio>
#include <iostream>

constexpr int MAX_N = 200050;

int a[MAX_N];
int r[MAX_N];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n, L;
    read(n, L);
    for (int i = 1; i <= n; i++) {
        read(a[i]);
    }

    int ans{1}, cnt{};
    for (int i = n; i > 0; i--) {
        if (cnt + a[i] > L) {
            cnt = a[i];
            ans++;
        } else {
            cnt += a[i];
        }
        r[i] = ans;
    }
    for (int i = 1; i <= n; i++) {
        std::cout << r[i] << ' ';
    }
    std::cout << '\n';

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