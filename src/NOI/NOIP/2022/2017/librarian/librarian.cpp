#include <bits/stdc++.h>

constexpr int MAX_N = 1050;

int b[MAX_N];

bool check(int a, int b, int l);

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    freopen("librarian.in", "r", stdin);
    freopen("librarian.out", "w", stdout);
    std::ios::sync_with_stdio(false);

    int n, q;
    read(n, q);
    for (int i = 1; i <= n; i++) {
        read(b[i]);
    }
    std::sort(b + 1, b + n + 1);

    while (q--) {
        int l, a;
        read(l, a);
        bool flag{};
        for (int i = 1; i <= n; i++) {
            if (check(b[i], a, l)) {
                std::cout << b[i] << '\n';
                flag = true;
                break;
            }
        }
        if (!flag) {
            std::cout << -1 << '\n';
        }
    }

    std::cout << std::flush;
    fclose(stdin);
    fclose(stdout);
    return 0;
}

bool check(int a, int b, int l) { return a % (int)std::pow(10, l) == b; }

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