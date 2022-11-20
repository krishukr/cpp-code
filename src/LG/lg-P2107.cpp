#include <algorithm>
#include <cstdio>
#include <iostream>
#include <queue>

using ll = long long;

constexpr int MAX_N = 100050;

struct A {
    ll x;
    ll t;
} a[MAX_N];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    ll n, m;
    read(n, m);
    for (int i = 1; i <= n; i++) {
        read(a[i].x, a[i].t);
    }
    std::sort(a + 1, a + n + 1,
              [](const A& x, const A& y) { return x.x < y.x; });

    std::priority_queue<ll> q;
    ll crt{}, cra{}, ans{};
    for (int i = 1; i <= n; i++) {
        crt += a[i].x - a[i - 1].x + a[i].t;
        cra++;
        q.push(a[i].t);

        while (!q.empty() and crt > m) {
            cra--;
            crt -= q.top();
            q.pop();
        }
        if (crt > m) {
            break;
        }
        ans = std::max(ans, cra);
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