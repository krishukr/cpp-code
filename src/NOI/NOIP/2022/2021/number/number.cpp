#include <cstdio>
#include <iostream>

constexpr int MAX_N = 10000050;

bool vis[MAX_N];
int ans[MAX_N];

bool check(int x);

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    freopen("number.in", "r", stdin);
    freopen("number.out", "w", stdout);
    std::ios::sync_with_stdio(false);

    {
        for (int i = 1; i <= MAX_N - 40; i++) {
            if (check(i)) {
                for (int j = 1; i * j <= MAX_N - 40; j++) {
                    vis[i * j] = true;
                }
            }
        }
        int p{};
        for (int i = 1; i <= MAX_N - 40; i++) {
            if (!vis[i]) {
                ans[p] = i;
                p = i;
            }
        }
    }

    int T;
    read(T);
    while (T--) {
        int x;
        read(x);
        std::cout << (vis[x] ? -1 : ans[x]) << '\n';
    }

    std::cout << std::flush;
    fclose(stdin);
    fclose(stdout);
    return 0;
}

bool check(int x) {
    while (x) {
        if (x % 10 == 7) {
            return true;
        }
        x /= 10;
    }
    return false;
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