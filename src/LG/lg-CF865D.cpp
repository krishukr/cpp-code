#include <cstdio>
#include <iostream>
#include <queue>

using ll = long long;

template <typename T>
using pq = std::priority_queue<T, std::vector<T>, std::greater<T>>;

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

    ll ans{};
    pq<int> q;
    for (int i = 1; i <= n; i++) {
        int x;
        read(x);
        if (!q.empty() and x > q.top()) {
            ans += x - q.top();
            q.pop();
            q.push(x);
        }
        q.push(x);
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