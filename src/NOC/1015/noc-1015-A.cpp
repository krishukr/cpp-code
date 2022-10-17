#include <cstdio>
#include <iostream>

int a, b, c, d;

bool check(int x);

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    read(a, b, c, d);
    int l{}, r{a + b + c + d}, ans{};
    while (l <= r) {
        const auto mid = (l + r) >> 1;
        if (check(mid)) {
            r = mid - 1;
            ans = mid;
        } else {
            l = mid + 1;
        }
    }
    std::cout << ans << '\n';

    return 0;
}

bool check(int x) {
    for (int i = 0; i <= b; i++) {
        for (int j = 0; j <= c; j++) {
            const auto req = std::max(b - i - j / 4, c - i / 4 - j),
                       dif = x - i - j;
            if ((x - i - j) / 2 < req) {
                continue;
            }
            const auto rea = std::max(0, a - i / 2 - j / 2),
                       red = std::max(0, d - i / 2 - j / 2),
                       rng = std::max(0, (rea - dif / 4) * 4 / 3);
            for (int k = std::max(0, rng - 5); k <= std::min(dif, rng + 5);
                 k++) {
                if (k + (dif - k) / 4 >= rea and k / 4 + dif - k >= red) {
                    return true;
                }
            }
        }
    }
    return false;
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