#include <cstdio>
#include <iostream>
#include <queue>

using pi = std::pair<int, int>;

constexpr int MAX_N = 100050;

int a[MAX_N], b[MAX_N];
int v[MAX_N];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    std::priority_queue<pi, std::vector<pi>, std::greater<pi>> q;
    int n;
    read(n);
    std::fill(v + 1, v + n + 1, 1);
    for (int i = 1; i <= n; i++) {
        read(a[i]);
    }
    for (int i = 1; i <= n; i++) {
        read(b[i]);
        q.push({a[1] + b[i], i});
    }
    for (int i = 1; i <= n; i++) {
        std::cout << q.top().first << ' ';
        const auto p = q.top().second;
        q.pop();
        q.push({a[++v[p]] + b[p], p});
    }
    std::cout << '\n';

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