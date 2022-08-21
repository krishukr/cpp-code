#include <cstdio>
#include <iostream>

constexpr int MAX_N = 1050;

struct {
    bool a, b, c;
} mp[MAX_N][MAX_N];

int lp[MAX_N][MAX_N], rp[MAX_N][MAX_N];
int ls[MAX_N][MAX_N], rs[MAX_N][MAX_N];

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
        for (int j = 1; j <= i; j++) {
            int a, b, c;
            read(a, b, c);
            mp[i][j] = {(bool)a, (bool)b, (bool)c};
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            if (mp[i][j].a) {
                lp[i][j] = lp[i - 1][j] + 1;
            }
            if (mp[i][j].b) {
                rp[i][j] = rp[i - 1][j - 1] + 1;
            }
        }
    }
    for (int i = n; i >= 1; i--) {
        for (int j = i; j >= 1; j--) {
            if (mp[i + 1][j].b) {
                ls[i][j] = ls[i + 1][j + 1] + 1;
            }
            if (mp[i + 1][j + 1].a) {
                rs[i][j] = rs[i + 1][j] + 1;
            }
        }
    }

    int a{};
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            for (int k = j; k <= n and mp[i][k].c and (k - j + 1) <= lp[i][j];
                 k++) {
                if ((k - j + 1) <= rp[i][k]) {
                    a++;
                }
            }
            for (int k = j; k <= n and mp[i][k].c and (k - j + 1) <= ls[i][j];
                 k++) {
                if ((k - j + 1) <= rs[i][k]) {
                    a++;
                }
            }
        }
    }
    std::cout << a << '\n';

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