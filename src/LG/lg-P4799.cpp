#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>

using ll = long long;

constexpr int MAX_N = 45;

ll v[MAX_N];
std::vector<ll> a, b;

void dfs1(ll x, int d);

void dfs2(ll x, int d);

int n, mid;
ll m;

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    read(n, m);
    mid = n >> 1;
    for (int i = 1; i <= n; i++) {
        read(v[i]);
    }
    dfs1(0, 1);
    dfs2(0, mid + 1);

    ll ans{};
    std::sort(a.begin(), a.end());
    for (const auto& i : b) {
        ans += std::upper_bound(a.begin(), a.end(), m - i) - a.begin();
    }
    std::cout << ans << '\n';

    return 0;
}

void dfs1(ll x, int d) {
    if (x > m) {
        return;
    }
    if (d > mid) {
        a.push_back(x);
        return;
    }
    dfs1(x + v[d], d + 1);
    dfs1(x, d + 1);
}

void dfs2(ll x, int d) {
    if (x > m) {
        return;
    }
    if (d > n) {
        b.push_back(x);
        return;
    }
    dfs2(x + v[d], d + 1);
    dfs2(x, d + 1);
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