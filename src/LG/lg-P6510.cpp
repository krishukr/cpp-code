#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>

constexpr int MAX_N = 100050;

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
    }

    std::vector<int> mx, mn;
    int ans{};
    for (int i = 1; i <= n; i++) {
        while (!mx.empty() and a[mx.back()] < a[i]) {
            mx.pop_back();
        }
        while (!mn.empty() and a[mn.back()] > a[i]) {
            mn.pop_back();
        }
        const auto p = std::upper_bound(mn.begin(), mn.end(), mx.back());
        if (p != mn.end()) {
            ans = std::max(ans, i - *p + 1);
        }
        mx.push_back(i);
        mn.push_back(i);
    }
    std::cout << ans << '\n';

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