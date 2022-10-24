#include <cstdio>
#include <iostream>
#include <memory>

using ll = long long;

constexpr int MAX_N = 1050;
constexpr ll INF = 0x3f3f3f3f3f3f3f3f;

class Solution {
    int a[MAX_N], s[MAX_N];
    int l[MAX_N], r[MAX_N];
    ll f[MAX_N];

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
    int n, k;
    read(n, k);
    for (int i = 1; i <= n; i++) {
        read(a[i]);
    }
    for (int i = 1; i <= n; i++) {
        s[i] = s[i - 1] + a[i];
    }
    int pm{};
    for (int i = 1; i <= n; i++) {
        l[i] = s[i] - pm;
        pm = std::min(pm, s[i]);
    }
    int sm{s[n]};
    for (int i = n; i >= 1; i--) {
        r[i] = sm - s[i - 1];
        sm = std::max(sm, s[i]);
    }

    std::fill(f + 2, f + n + 1, -INF);
    ll ans{};
    for (int j = 1; j <= std::min(2000, k); j++) {
        if (j & 1) {
            ll pt{-INF};
            for (int i = 1; i <= n; i++) {
                pt = std::max(pt, f[i] - s[i - 1]);
                f[i] = pt + s[i];
                f[i] = f[i] >= 0 ? f[i] : -INF;
                ans =
                    std::max(ans, f[i] + std::max<ll>(0, 1ll * (k - j) * l[i]));
            }
        } else {
            ll st{-INF};
            for (int i = n; i >= 1; i--) {
                st = std::max(st, f[i] + s[i]);
                f[i] = st - s[i - 1];
                f[i] = f[i] >= 0 ? f[i] : -INF;
                ans =
                    std::max(ans, f[i] + std::max<ll>(0, 1ll * (k - j) * r[i]));
            }
        }
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