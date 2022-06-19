#include <algorithm>
#include <cstdio>
#include <iostream>

constexpr int MAX_N = 8050;

std::pair<int, int> a[MAX_N];
int ans[MAX_N];
int n, q;

void calc();

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    freopen("sort.in", "r", stdin);
    freopen("sort.out", "w", stdout);
    std::ios::sync_with_stdio(false);

    read(n, q);
    for (int i = 1; i <= n; i++) {
        read(a[i].first);
        a[i].second = i;
    }
    std::sort(a + 1, a + n + 1);
    calc();

    while (q--) {
        int op;
        read(op);
        if (op == 1) {
            int x, v;
            read(x, v);
            a[ans[x]].first = v;
            for (int i = ans[x]; i > 1; i--) {
                if (a[i] < a[i - 1]) {
                    std::swap(a[i], a[i - 1]);
                }
            }
            for (int i = ans[x]; i < n; i++) {
                if (a[i] > a[i + 1]) {
                    std::swap(a[i], a[i + 1]);
                }
            }
            calc();
        } else {
            int a;
            read(a);
            std::cout << ans[a] << '\n';
        }
    }

    std::cout << std::flush;
    fclose(stdin);
    fclose(stdout);
    return 0;
}

void calc() {
    for (int i = 1; i <= n; i++) {
        ans[a[i].second] = i;
    }
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