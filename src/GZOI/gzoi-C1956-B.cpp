#include <algorithm>
#include <climits>
#include <cstdio>
#include <iostream>
#include <memory>

using ll = long long;

constexpr int MAX_N = 2050;

class Solution {
    int a[MAX_N];
    ll s[MAX_N];

   public:
    Solution() = default;
    ~Solution() = default;

    void solve();
};

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
        auto solution = std::make_unique<Solution>();
        solution->solve();
    }

    return 0;
}

void Solution::solve() {
    int n, m;
    read(n, m);
    for (int i = 1; i <= n; i++) {
        read(a[i]);
    }
    std::sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; i++) {
        s[i] = s[i - 1] + a[i];
    }

    ll ans{LLONG_MAX};
    for (int i = 1; i < m; i++) {
        ans = std::min(ans, 1ll * (n - m) * a[i] + s[i] + s[n] - s[n - m + i]);
    }
    for (int i = m; i <= n; i++) {
        ans = std::min(ans, 1ll * (n - i) * a[i] + s[i] - s[i - m]);
    }
    std::cout << ans << '\n';
}

template <typename T>
T read() {
    T x = 0, f = 1;
    char ch = getchar_unlocked();
    while (!isdigit(ch)) {
        if (ch == '-') f = -1;
        ch = getchar_unlocked();
    }
    while (isdigit(ch)) {
        x = x * 10 + ch - 48;
        ch = getchar_unlocked();
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