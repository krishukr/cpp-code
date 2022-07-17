#include <cstdio>
#include <iostream>

constexpr int MAX_N = 505;

int s[MAX_N][MAX_N];
int r, c, a, b;

bool check(int x);

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    read(r, c, a, b);
    for (int i = 1; i <= r; i++) {
        for (int j = 1; j <= c; j++) {
            read(s[i][j]);
        }
    }
    for (int i = 1; i <= r; i++) {
        for (int j = 1; j <= c; j++) {
            s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1] + s[i][j];
        }
    }

    int bl{}, br{s[r][c]}, ans{};
    while (bl <= br) {
        const auto mid = (bl + br) >> 1;
        if (check(mid)) {
            ans = mid;
            bl = mid + 1;
        } else {
            br = mid - 1;
        }
    }
    std::cout << ans << '\n';

    return 0;
}

bool check(int x) {
    int t{}, n{};
    for (int i = 1; i <= ::r; i++) {
        int d{}, m{};
        for (int j = 1; j <= ::c; j++) {
            const auto p = s[i][j] - s[i][j - 1] - s[t][j] + s[t][j - 1];
            if (d + p < x) {
                d += p;
            } else {
                m++;
                d = 0;
            }
        }
        if (b <= m) {
            t = i;
            n++;
        }
    }
    return a <= n;
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