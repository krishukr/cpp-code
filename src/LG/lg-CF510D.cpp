#include <algorithm>
#include <cstdio>
#include <iostream>
#include <unordered_map>

constexpr int MAX_N = 305;

int a[MAX_N], b[MAX_N];
std::unordered_map<int, int> mp;

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
        for (const auto& j : mp) {
            const auto x = std::__gcd(a[i], j.first), w = j.second + b[i];
            if (mp.find(x) == mp.end()) {
                mp[x] = w;
            } else {
                mp[x] = std::min(mp[x], w);
            }
        }
        if (mp.find(a[i]) == mp.end()) {
            mp[a[i]] = b[i];
        } else {
            mp[a[i]] = std::min(mp[a[i]], b[i]);
        }
    }

    std::cout << (mp.find(1) == mp.end() ? -1 : mp[1]) << '\n';

    return 0;
}

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

template <typename T>
void read(T& t) {
    t = read<T>();
}

template <typename T, typename... Args>
void read(T& t, Args&... rest) {
    t = read<T>();
    read(rest...);
}