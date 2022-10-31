#include <algorithm>
#include <cstdio>
#include <iostream>
#include <queue>

constexpr int MAX_N = 1000050;

int a[MAX_N];
int n, k;

template <class Cmp>
void calc();

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
    calc<std::less<int>>();
    calc<std::greater<int>>();

    return 0;
}

template <class Cmp>
void calc() {
    std::deque<int> q;
    for (int i = 1; i <= n; i++) {
        while (!q.empty() and q.front() + k <= i) {
            q.pop_front();
        }
        while (!q.empty() and Cmp{}(a[i], a[q.back()])) {
            q.pop_back();
        }
        q.push_back(i);
        if (k <= i) {
            std::cout << a[q.front()] << ' ';
        }
    }
    std::cout << '\n';
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