#include <cstdio>
#include <iostream>
#include <stack>

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n, c{};
    read(n);

    std::stack<int> s;
    for (int i = 1; i <= n; i++) {
        int d, w;
        read(d, w);
        while (!s.empty() and w <= s.top()) {
            if (w == s.top()) {
                c++;
            }
            s.pop();
        }
        s.push(w);
    }
    std::cout << n - c << '\n';

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