#include <cstdio>
#include <iostream>

using ll = long long;

constexpr int MAX_N = 100050;

int dp[2][MAX_N];
char s[MAX_N];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n;
    ll t;
    read(n, t);
    for (int i = 0; i < n; i++) {
        char ch = getchar();
        while (ch != '0' and ch != '1') {
            ch = getchar();
        }
        s[i] = ch;
        dp[0][i] = (ch == '1');
    }

    int r{0};
    for (int i = 0; i < 63; i++) {
        if (t & (1ll << i)) {
            int sr{int((1ll << i) % n)}, sl{(n - sr) % n};
            for (int j = 0; j < n; j++) {
                dp[r ^ 1][j] = dp[r][sl] ^ dp[r][sr];
                sl = (sl + 1) % n;
                sr = (sr + 1) % n;
            }
            r ^= 1;
        }
    }

    for (int i = 0; i < n; i++) {
        std::cout << dp[r][i];
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