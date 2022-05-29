#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>

using ll = long long;

constexpr int MAX_N = 5050;
constexpr ll INF = 0x3f3f3f3f3f3f3f3f;

ll a[MAX_N], s[MAX_N];
ll f[MAX_N][MAX_N];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    freopen("partition.in", "r", stdin);
    freopen("partition.out", "w", stdout);
    std::ios::sync_with_stdio(false);

    int n, _type;
    read(n, _type);
    for (int i = 1; i <= n; i++) {
        read(a[i]);
        s[i] = s[i - 1] + a[i];
    }
    memset(f, 0x3f, sizeof(f));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            if (j == 1) {
                f[i][j] = s[i] * s[i];
            } else {
                for (int k = 1; k < j; k++) {
                    if (s[j - 1] - s[k - 1] <= s[i] - s[j - 1]) {
                        f[i][j] = std::min(
                            f[i][j], f[j - 1][k] +
                                         (s[i] - s[j - 1]) * (s[i] - s[j - 1]));
                    }
                }
            }
        }
    }

    ll ans{INF};
    for (int i = 1; i <= n; i++) {
        ans = std::min(ans, f[n][i]);
    }
    std::cout << ans << '\n';

    std::cout << std::flush;
    fclose(stdin);
    fclose(stdout);
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