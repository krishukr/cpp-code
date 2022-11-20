#include <algorithm>
#include <cstdio>
#include <iostream>
#include <queue>

using ll = long long;

constexpr int MAX_N = 150050;

struct A {
    int x;
    int y;
} a[MAX_N];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n;
    read(n);
    for (int i = 1; i <= n; i++) {
        read(a[i].x, a[i].y);
    }
    std::sort(a + 1, a + n + 1,
              [](const A& x, const A& y) { return x.y < y.y; });

    std::priority_queue<int> q;
    ll crt{}, ans{};
    for (int i = 1; i <= n; i++) {
        if (crt + a[i].x <= a[i].y) {
            ans++;
            crt += a[i].x;
            q.push(a[i].x);
        } else if (q.top() > a[i].x) {
            crt -= q.top() - a[i].x;
            q.pop();
            q.push(a[i].x);
        }
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