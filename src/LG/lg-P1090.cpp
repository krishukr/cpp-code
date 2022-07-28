#include <cstdio>
#include <iostream>
#include <queue>

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    std::priority_queue<int, std::vector<int>, std::greater<int>> q;
    int n;
    read(n);
    for (int i = 1; i <= n; i++) {
        q.push(read<int>());
    }

    int r{};
    while (q.size() >= 2) {
        const auto x = q.top();
        q.pop();
        const auto y = q.top();
        q.pop();
        r += x + y;
        q.push(x + y);
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