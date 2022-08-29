#include <cstdio>
#include <iostream>

constexpr int MAX_N = 1000050;

int s[MAX_N];
bool v[MAX_N];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    s[1] = 0;
    v[1] = true;
    for (int i = 2; i <= MAX_N - 40; i++) {
        if (!v[i]) {
            s[i] = s[i - 1] + 1;
            for (int j = i; j <= MAX_N - 40; j += i) {
                v[j] = true;
            }
        } else {
            s[i] = s[i - 1];
        }
    }

    int n, m;
    read(n, m);
    while (n--) {
        int l, r;
        read(l, r);
        if (l < 1 or r > m) {
            std::cout << "Crossing the line\n";
        } else {
            std::cout << s[r] - s[l - 1] << '\n';
        }
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