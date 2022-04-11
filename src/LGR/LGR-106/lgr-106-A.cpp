#include <cstdio>
#include <iostream>
#include <memory>

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int T;
    read(T);
    while (T--) {
        int n;
        read(n);
        auto ans = std::make_unique<int[]>(n + 50);
        int lst = n + 1, cs = 0;
        for (int i = 1; i <= n; i++) {
            int x;
            read(x);
            if (x != -1) {
                int len = i - lst + 1;
                if (len > 0) {
                    int v = (x - cs) / len;
                    for (int j = lst; j < i; j++) {
                        ans[j] = v;
                        cs += v;
                    }
                }
                ans[i] = x - cs;
                cs = x;
                lst = n + 1;
            } else {
                if (lst > n) {
                    lst = i;
                }
            }
        }

        for (int i = 1; i <= n; i++) {
            std::cout << (ans[i] ? ans[i] : 1) << ' ';
        }
        std::cout << '\n';
    }

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