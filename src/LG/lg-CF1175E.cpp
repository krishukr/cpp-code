#include <cstdio>
#include <iostream>

constexpr int MAX_N = 500050;

int q[MAX_N], b[20][MAX_N];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n, m, mr{0};
    read(n, m);
    for (int i = 1; i <= n; i++) {
        int l, r;
        read(l, r);
        q[l] = std::max(q[l], r);
        mr = std::max(mr, r);
    }

    for (int i = 1; i <= mr; i++) {
        q[i] = std::max(q[i], q[i - 1]);
    }
    for (int i = 0; i <= mr; i++) {
        b[0][i] = q[i];
    }

    for (int i = 1; i < 20; i++) {
        for (int j = 0; j <= mr; j++) {
            b[i][j] = b[i - 1][b[i - 1][j]];
        }
    }

    for (int i = 1; i <= m; i++) {
        int l, r, res{0};
        read(l, r);
        for (int j = 19; j >= 0; j--) {
            if (b[j][l] < r) {
                res += (1 << j);
                l = b[j][l];
            }
        }

        std::cout << (q[l] >= r ? res + 1 : -1) << '\n';
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