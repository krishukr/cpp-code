#include <cstdio>
#include <deque>
#include <iostream>

constexpr int MAX_N = 100050;

int s[MAX_N], f[MAX_N], g[MAX_N];

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
    for (int i = n; i >= 1; i--) {
        read(s[i]);
    }
    for (int i = 1; i <= n; i++) {
        s[i] = s[i - 1] + s[i];
    }

    std::deque<int> q;
    for (int i = 1, p = 0; i <= n; i++) {
        while (!q.empty() and s[i] >= s[q.front()] + g[q.front()]) {
            p = q.front();
            q.pop_front();
        }
        g[i] = s[i] - s[p];
        f[i] = f[p] + 1;
        while (!q.empty() and s[i] + g[i] <= s[q.back()] + g[q.back()]) {
            q.pop_back();
        }
        q.push_back(i);
    }
    std::cout << f[n] << '\n';

    std::cout << std::flush;
    return 0;
}

template <typename T>
T read() {
    T x{}, f{1};
    int ch = getchar_unlocked();
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