#include <climits>
#include <cstdio>
#include <iostream>

constexpr int MAX_N = 5050;

int d[MAX_N];

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
    for (int i = 1; i <= n; i++) {
        char ch = getchar();
        while (ch != 'F' and ch != 'B') {
            ch = getchar();
        }
        d[i] = (ch == 'F');
    }

    int ak{}, am{INT_MAX};
    for (int x = 1; x <= n; x++) {
        int f[MAX_N << 1]{};
        int s{}, t{}, p{};
        for (int i = 1; i <= n; i++) {
            if (!((d[i] + t) & 1)) {
                if (n < i + x - 1) {
                    p = true;
                    break;
                }
                s++;
                t++;
                f[i + x - 1] = -114514;
            }
            if (f[i] == -114514) {
                t--;
                f[i] = 0;
            }
        }
        if (p) {
            continue;
        }
        if (am > s) {
            am = s;
            ak = x;
        }
    }
    std::cout << ak << ' ' << am << '\n';

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