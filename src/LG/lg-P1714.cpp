#include <climits>
#include <cstdio>
#include <iostream>
#include <queue>

constexpr int MAX_N = 500050;

int s[MAX_N];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n, m;
    read(n, m);
    for (int i = 1; i <= n; i++) {
        s[i] = s[i - 1] + read<int>();
    }

    std::deque<int> q{0};
    int ans{INT_MIN};
    for (int i = 1; i <= n; i++) {
        while (!q.empty() and q.front() < i - m) {
            q.pop_front();
        }
        ans = std::max(ans, s[i] - s[q.front()]);
        while (!q.empty() and s[q.back()] > s[i]) {
            q.pop_back();
        }
        q.push_back(i);
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