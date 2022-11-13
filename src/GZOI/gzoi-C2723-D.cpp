#include <cstdio>
#include <iostream>
#include <map>
#include <memory>
#include <random>
#include <vector>

using ull = unsigned long long;

constexpr int MAX_N = 300050;

std::mt19937_64 mrand(1145141999);

std::map<ull, int> mp;
std::vector<int> c[MAX_N];
ull v[MAX_N];

void solve();

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
        solve();
    }

    return 0;
}

void solve() {
    int n;
    read(n);
    for (int i = 1; i <= n; i++) {
        int x;
        read(x);
        c[x].push_back(i);
    }
    for (int i = 1; i <= n; i++) {
        if (c[i].empty()) {
            continue;
        }
        ull s{};
        for (int j = 1; j < c[i].size(); j++) {
            s ^= (v[c[i][j]] = mrand());
        }
        v[c[i][0]] = s;
    }

    mp[0] = 1;
    ull s{}, a{};
    for (int i = 1; i <= n; i++) {
        s ^= v[i];
        a += mp[s];
        mp[s]++;
    }
    std::cout << a << '\n';

    for (int i = 1; i <= n; i++) {
        c[i].clear();
        v[i] = 0;
    }
    mp.clear();
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