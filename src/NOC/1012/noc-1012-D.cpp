#include <cstdio>
#include <iostream>

using ll = long long;

constexpr int MOD = 1e9 + 7;

ll ans[4];

void gp(int n);

void ga(int n);

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n, q, type;
    read(n, q, type);
    if (n == 1 and q == 1) {
        int a;
        read(a);
        gp(a);
        ga(a);
        std::cout << ans[type] << '\n';
    }

    return 0;
}

void gp(int n) {
    int ta{};
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            ta++;
            int tb{};
            while (n % i == 0) {
                n /= i;
                tb++;
                if (tb >= 2) {
                    ans[1] = 0;
                    return;
                }
            }
        }
    }
    if (n != 1) {
        ta++;
    }
    if (ta & 1) {
        ans[1] = -1;
    } else {
        ans[1] = 1;
    }
}

void ga(int n) {
    for (int i = 1; i <= n; i++) {
        if (n % i == 0) {
            ans[2]++;
            ans[3] += i;
            ans[3] %= MOD;
        }
    }
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