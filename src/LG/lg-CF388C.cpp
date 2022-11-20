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

    std::priority_queue<int> q;
    int n, a1{}, a2{};
    read(n);
    for (int i = 1; i <= n; i++) {
        int s;
        read(s);
        for (int j = 1; j <= s; j++) {
            int x;
            read(x);
            if (s & 1 and j == ((s + 1) >> 1)) {
                q.push(x);
            } else {
                if (j <= (s >> 1)) {
                    a1 += x;
                } else {
                    a2 += x;
                }
            }
        }
    }

    int t{};
    while (!q.empty()) {
        if (t) {
            a2 += q.top();
        } else {
            a1 += q.top();
        }
        q.pop();
        t ^= 1;
    }
    std::cout << a1 << ' ' << a2 << '\n';

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