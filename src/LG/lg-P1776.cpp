#include <cstdio>
#include <iostream>
#include <queue>

constexpr int MAX_N = 800050;

int f[MAX_N];
int v[MAX_N], w[MAX_N];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n, W, cnt{1};
    read(n, W);
    for (int i = 1; i <= n; i++) {
        int x, y, z;
        read(x, y, z);
        for (int j = 1; j <= z; j <<= 1) {
            cnt++;
            v[cnt] = j * x;
            w[cnt] = j * y;
            z -= j;
        }
        if (z) {
            ++cnt;
            v[cnt] = z * x;
            w[cnt] = z * y;
        }
    }

    for (int i = 1; i <= cnt; i++) {
        for (int j = W; j >= w[i]; j--) {
            f[j] = std::max(f[j], f[j - w[i]] + v[i]);
        }
    }
    std::cout << f[W] << '\n';

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