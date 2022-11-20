#include <algorithm>
#include <cstdio>
#include <iostream>
#include <queue>

using ll = long long;

constexpr int MAX_N = 100050;

struct A {
    int a;
    int b;
    int c;
} a[MAX_N];

ll f[MAX_N], g[MAX_N];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int x, y, z;
    read(x, y, z);
    const auto n = x + y + z;
    ll tot{};
    for (int i = 1; i <= n; i++) {
        int x, y, z;
        read(x, y, z);
        a[i] = {x, y, z};
        tot += z;
    }
    std::sort(a + 1, a + n + 1,
              [](const A& x, const A& y) { return x.a - x.b > y.a - y.b; });

    {
        std::priority_queue<ll> q;
        for (int i = 1; i <= n; i++) {
            q.push(a[i].c - a[i].a);
            f[i] = f[i - 1] + a[i].a - a[i].c;
            if (q.size() > x) {
                f[i] += q.top();
                q.pop();
            }
        }
    }
    {
        std::priority_queue<ll> q;
        for (int i = n; i >= 1; i--) {
            q.push(a[i].c - a[i].b);
            g[i] = g[i + 1] + a[i].b - a[i].c;
            if (q.size() > y) {
                g[i] += q.top();
                q.pop();
            }
        }
    }

    ll ans{};
    for (int i = x; i <= x + z; i++) {
        ans = std::max(ans, f[i] + g[i + 1] + tot);
    }
    std::cout << ans << '\n';

    return 0;
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