#include <cstdio>
#include <iostream>

constexpr int MAX_N = 500050;

int f[MAX_N], l[MAX_N];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n, c, cnt{}, ans{};
    read(n, c);
    for (int i = 1; i <= n; i++) {
        int x;
        read(x);
        if (x == c) {
            cnt++;
        } else {
            f[x] = std::max(f[x] + l[x] - cnt, 0) + 1;
            l[x] = cnt;
            ans = std::max(ans, f[x]);
        }
    }
    std::cout << cnt + ans << '\n';

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