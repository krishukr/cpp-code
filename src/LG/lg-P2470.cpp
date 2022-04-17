#include <cstdio>
#include <cstring>
#include <iostream>

constexpr int MAX_N = 105;

char s[MAX_N];
int dp[MAX_N][MAX_N];

inline bool check(const size_t& l, const size_t& r);

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    memset(dp, 0x3f, sizeof(dp));
    scanf("%s", s + 1);
    auto n = strlen(s + 1);

    dp[1][1] = 1;
    for (size_t i = 1; i <= n; i++) {
        for (size_t j = 1; j < i; j++) {
            dp[i][i] = std::min(dp[i][i], dp[i - 1][j] + 2);
        }
        for (size_t j = 1; j < i; j++) {
            dp[i][j] = dp[i - 1][j] + 1;
            if (check(j, i) and !((j - i + 1) % 2)) {
                dp[i][j] = std::min(dp[i][j], dp[(i + j - 1) >> 1][j] + 1);
            }
        }
    }

    int ans = 0x3f3f3f3f;
    for (size_t j = 0; j < n; j++) {
        ans = std::min(ans, dp[n][j]);
    }
    std::cout << ans << '\n';

    return 0;
}

inline bool check(const size_t& l, const size_t& r) {
    const auto mid = (l + r) >> 1;
    for (size_t i = l, j = mid + 1; i <= mid and j <= r; i++, j++) {
        if (s[i] != s[j]) {
            return false;
        }
    }
    return true;
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