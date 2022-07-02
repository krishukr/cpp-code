#include <cstdio>
#include <iostream>

using ll = long long;

constexpr int MAX_N = 300050;

int a[MAX_N], s[MAX_N];
int c[]{1, 0};

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
    ll ans{};
    for (int i = 1; i <= n; i++) {
        ll x;
        read(x);
        while (x) {
            a[i] += x % 2;
            x >>= 1;
        }
        s[i] = s[i - 1] + a[i];

        ans += c[s[i] & 1];
        for (int j = i, k = i + 1, m = 0; j >= 1 and i - j <= 61; j--) {
            while (k > j) {
                m = std::max(m, a[--k]);
            }
            if (m + m > s[i] - s[j - 1] and (s[i] & 1) == (s[j - 1] & 1)) {
                ans--;
            }
        }
        c[s[i] & 1]++;
    }
    std::cout << ans << '\n';

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