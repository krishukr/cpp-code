#include <algorithm>
#include <cstdio>
#include <iostream>
#include <map>
#include <random>

using ull = unsigned long long;

constexpr int MAX_N = 200050;

std::mt19937_64 mrand(1145142007);

int a[MAX_N], b[MAX_N];
ull sa[MAX_N], sb[MAX_N];
std::map<int, bool> va, vb;
std::map<int, ull> mp;

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
        read(a[i]);
    }
    for (int i = 1; i <= n; i++) {
        read(b[i]);
    }
    for (int i = 1; i <= n; i++) {
        if (va[a[i]]) {
            a[i] = 0;
        } else {
            va[a[i]] = true;
        }
    }
    for (int i = 1; i <= n; i++) {
        if (vb[b[i]]) {
            b[i] = 0;
        } else {
            vb[b[i]] = true;
        }
    }

    for (int i = 1; i <= n; i++) {
        if (a[i] and (mp.find(a[i]) == mp.end())) {
            mp[a[i]] = mrand();
        }
    }
    for (int i = 1; i <= n; i++) {
        if (b[i] and (mp.find(b[i]) == mp.end())) {
            mp[b[i]] = mrand();
        }
    }
    for (int i = 1; i <= n; i++) {
        sa[i] = sa[i - 1];
        if (a[i]) {
            sa[i] ^= mp[a[i]];
        }
    }
    for (int i = 1; i <= n; i++) {
        sb[i] = sb[i - 1];
        if (b[i]) {
            sb[i] ^= mp[b[i]];
        }
    }

    int q;
    read(q);
    while (q--) {
        int x, y;
        read(x, y);
        std::cout << (sa[x] == sb[y] ? "Yes" : "No") << '\n';
    }

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