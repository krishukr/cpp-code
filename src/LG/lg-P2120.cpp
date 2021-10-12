#include <cstdio>
#include <iostream>

typedef long long ll;

const int MAX_N = 1000050;

int x[MAX_N], p[MAX_N], c[MAX_N], q[MAX_N];
ll s1[MAX_N], s2[MAX_N], dp[MAX_N];

inline double X(int i);
inline double Y(int i);
inline double slope(int i, int j);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>();
    for (int i = 1; i <= n; i++) {
        x[i] = read<int>();
        p[i] = read<int>();
        c[i] = read<int>();

        s1[i] = s1[i - 1] + p[i];
        s2[i] = s2[i - 1] + p[i] * x[i];
    }

    int hck = n;
    while (!p[hck] and hck) {
        hck--;
    }
    if (!hck) {
        std::cout << 0 << '\n';
        return 0;
    }

    int l = 0, r = 0;
    for (int i = 1; i <= n; i++) {
        while (l < r and slope(q[l + 1], q[l]) < x[i]) {
            l++;
        }
        int j = q[l];
        dp[i] = dp[j] + x[i] * (s1[i] - s1[j]) - (s2[i] - s2[j]) + c[i];
        while (l < r and slope(q[r], q[r - 1]) > slope(i, q[r])) {
            r--;
        }
        q[++r] = i;
    }

    ll ans = 0x3f3f3f3f3f3f3f3f;
    for (int i = hck; i <= n; i++) {
        ans = std::min(ans, dp[i]);
    }
    std::cout << ans << '\n';

    return 0;
}

inline double X(int i) { return s1[i]; }
inline double Y(int i) { return dp[i] + s2[i]; }
inline double slope(int i, int j) { return (Y(i) - Y(j)) / (X(i) - X(j)); }

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