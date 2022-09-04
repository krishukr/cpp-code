#include <cstdio>
#include <iostream>
#include <unordered_map>

using ll = long long;

std::unordered_map<int, ll> v;

ll dfs(int x);

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
    std::cout << dfs(n) << '\n';

    return 0;
}

ll dfs(int x) {
    if (x == 1) {
        return 1;
    }
    if (v.find(x) != v.end()) {
        return v[x];
    }
    int l, r;
    ll ans{};
    for (l = 2; l <= x; l = r + 1) {
        r = x / (x / l);
        ans += dfs(x / l) * (r - l + 1);
    }
    v[x] = ans;
    return ans;
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