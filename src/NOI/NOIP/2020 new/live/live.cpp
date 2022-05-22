#include <cstdio>
#include <iostream>

constexpr int MAX_N = 600;

int b[MAX_N + 5];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    freopen("live.in", "r", stdin);
    freopen("live.out", "w", stdout);
    std::ios::sync_with_stdio(false);

    int n, w;
    read(n, w);
    for (int i = 1; i <= n; i++) {
        b[read<int>()]++;

        int r{};
        // for (int j = MAX_N; j > 0; j--) {
        for (int j = MAX_N; j >= 0; j--) {
            r += b[j];
            if (r >= std::max(1, (i * w / 100))) {
                std::cout << j << ' ';
                break;
            }
        }
    }

    std::cout << std::flush;
    fclose(stdin);
    fclose(stdout);
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