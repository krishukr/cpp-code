#include <cstdio>
#include <cstring>
#include <iostream>

using ll = long long;

constexpr int MAX_N = 1050;
constexpr int MOD = 1e9 + 7;

char s[MAX_N];
ll f[MAX_N][MAX_N];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int T;
    read(T);
    while (T--) {
        int n;
        read(n);
        for (int i = 1; i <= n; i++) {
            char ch = getchar();
            while (ch != 'F' and ch != 'P') {
                ch = getchar();
            }
            s[i] = ch;
        }
        if (s[n] == 'F') {
            std::cout << 0 << '\n';
            continue;
        }

        f[0][0] = 1;
        for (int i = 1; i <= n; i++) {
            if (s[i - 1] == 'F') {
                for (int j = 1; j < n; j++) {
                    f[i][j] = f[i - 1][j - 1];
                }
            } else {
                for (int j = i - 1; j >= 0; j--) {
                    f[i][j] = (f[i][j + 1] + f[i - 1][j]) % MOD;
                }
            }
        }

        ll a{};
        for (int i = 0; i < n; i++) {
            a += f[n][i];
            a %= MOD;
        }
        std::cout << a << '\n';
        memset(f, 0, sizeof(f));
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