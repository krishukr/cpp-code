#include <cstdio>
#include <iostream>

constexpr int MAX_N = 1000050;

struct {
    int v;
    int nxt;
} node[MAX_N];

int head[MAX_N];

char s[MAX_N];
int a[MAX_N];

template <typename T>
T read();

template <>
char read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n, mn{};
    read(n);
    for (int i = 1; i <= n; i++) {
        read(s[i]);
    }
    for (int i = 1; i <= n; i++) {
        a[i] = a[i - 1] + (s[i] == 'p' ? 1 : -1);
        mn = std::min(mn, a[i]);
    }
    for (int i = n; i >= 0; i--) {
        const auto x = a[i] - mn;
        node[i] = {i, head[x]};
        head[x] = i;
    }

    int ans{};
    for (int i = n, p = n; i >= 1; i--) {
        if (s[i] == 'j') {
            p = i - 1;
        } else {
            if (node[i - 1].nxt >= 0 and a[p] <= a[node[node[i - 1].nxt].v]) {
                p = node[node[i - 1].nxt].v;
            }
            node[i - 1].v = p;
            ans = std::max(ans, p - i + 1);
        }
    }
    std::cout << ans << '\n';

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

template <>
char read() {
    char ch = getchar_unlocked();
    while (ch != 'j' and ch != 'p') {
        ch = getchar_unlocked();
    }
    return ch;
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