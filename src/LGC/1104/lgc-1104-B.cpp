#include <algorithm>
#include <cstdio>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>

using ll = long long;

template <typename T>
using pq = std::priority_queue<T, std::vector<T>, std::greater<T>>;

constexpr int MAX_N = 100050;
constexpr int MOD = 1e9 + 7;

struct R {
    int l;
    int r;
} r[MAX_N];

template <typename T>
T quick_pow(T a, T b);

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n, k;
    read(n, k);
    for (int i = 1; i <= n; i++) {
        read(r[i].l, r[i].r);
    }
    std::sort(r + 1, r + n + 1,
              [](const R& x, const R& y) { return x.l < y.l; });
    pq<int> q;
    ll ans{};
    for (int i = 1; i <= n; i++) {
        if (r[i].r - r[i].l < k) {
            continue;
        }
        while (!q.empty() and q.top() - r[i].l < k) {
            q.pop();
        }
        ans += quick_pow<ll>(2, q.size());
        ans %= MOD;
        q.push(r[i].r);
    }
    std::cout << ans << '\n';

    return 0;
}

template <typename T>
T quick_pow(T a, T b) {
    T r{1};
    while (b) {
        if (b & 1) {
            r = r * a % MOD;
        }
        a = a * a % MOD;
        b >>= 1;
    }
    return r;
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