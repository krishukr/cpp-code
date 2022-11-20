#include <asm-generic/errno-base.h>

#include <cstdio>
#include <iostream>
#include <queue>
#include <utility>

using ll = long long;

constexpr int MAX_N = 500050;

struct N {
    ll x;
    int p;
    int n;
} t[MAX_N];

std::priority_queue<std::pair<ll, int>> q;

bool vis[MAX_N];

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
        int x;
        read(x);
        t[i] = {x, i - 1, i + 1};
        q.push({x, i});
    }

    ll ans{};
    for (int i = 1; i <= k; i++) {
        while (vis[q.top().second]) {
            q.pop();
        }
        const auto p = q.top();
        q.pop();
        if (p.first <= 0) {
            break;
        }
        ans += p.first;
        vis[t[p.second].p] = vis[t[p.second].n] = true;
        t[p.second].x = t[t[p.second].p].x + t[t[p.second].n].x - t[p.second].x;
        q.push({t[p.second].x, p.second});
        t[p.second].p = t[t[p.second].p].p;
        t[p.second].n = t[t[p.second].n].n;
        t[t[p.second].p].n = p.second;
        t[t[p.second].n].p = p.second;
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