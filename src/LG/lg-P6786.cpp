#include <algorithm>
#include <cstdio>
#include <iostream>
#include <unordered_map>

using ll = long long;

constexpr int MAX_N = 300050;

std::unordered_map<ll, int> mp;
int a[MAX_N];

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
        mp[a[i]]++;
    }
    std::sort(a + 1, a + n + 1);

    ll r{};
    for (int i = 1; i <= n; i++) {
        ll c{}, j = a[i];
        while (mp[j]) {
            c += j * mp[j];
            mp[j] = 0;
            if (j & 1) {
                break;
            } else {
                j = j / 2 * 3;
            }
        }
        r = std::max(r, c);
    }
    std::cout << r << '\n';

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