#include <cmath>
#include <cstdio>
#include <iostream>

constexpr int MAX_N = 2000050;

int pri[MAX_N], ans[MAX_N];
bool vi[MAX_N];

int tot, idx;

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    for (int i = 2; i < MAX_N; i++) {
        if (!vi[i]) {
            pri[tot++] = i;
        }
        for (int j = 0; j < tot; j++) {
            if (i * pri[j] >= MAX_N) {
                break;
            }
            vi[i * pri[j]] = true;
            if (i % pri[j] == 0) {
                break;
            }
        }
    }

    ans[1] = 1;
    for (int i = 2; i < MAX_N; i++) {
        while (i >= pri[idx + 1]) {
            idx++;
        }
        ans[i] = pri[idx];
    }

    int T;
    read(T);
    while (T--) {
        std::cout << ans[read<int>()] << '\n';
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