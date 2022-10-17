#include <cstdio>
#include <iostream>

using ll = long long;

constexpr int MAX_N = 500050;

std::pair<int, int> stk[MAX_N];
int top;

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
    ll a{};
    for (int i = 1; i <= n; i++) {
        int x;
        read(x);

        std::pair<int, int> p = {x, 1};
        while (top and stk[top].first <= x) {
            a += stk[top].second;
            if (stk[top].first == x) {
                p.second += stk[top].second;
            }
            top--;
        }
        if (top) {
            a++;
        }
        stk[++top] = p;
    }
    std::cout << a << '\n';

    return 0;
}

template <typename T>
T read() {
    T x = 0, f = 1;
    char ch = getchar_unlocked();
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