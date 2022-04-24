#include <algorithm>
#include <cstdio>
#include <iostream>

using ll = long long;

constexpr int MAX_N = 200050;

int n, k;
int a[MAX_N];

bool check(int x);

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    read(n, k);
    for (int i = 1; i <= n; i++) {
        read(a[i]);
    }
    std::sort(a + 1, a + n + 1);

    ll l = 0, r = 0x7f7f7f7f;
    while (l < r) {
        int mid = (l + r + 1) >> 1;
        if (check(mid)) {
            l = mid;
        } else {
            r = mid - 1;
        }
    }
    std::cout << r << '\n';

    return 0;
}

bool check(int x) {
    ll s = 0;
    for (int i = (n + 1) >> 1; i <= n; i++) {
        if (x > a[i]) {
            s += x - a[i];
        } else {
            break;
        }
    }
    return s <= k;
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