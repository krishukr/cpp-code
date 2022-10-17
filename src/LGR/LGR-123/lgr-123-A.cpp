#include <bits/stdc++.h>

int a[1000050];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    std::string s;
    {
        s = " ";
        int i{};
        while (s.length() <= 1000000) {
            for (int j = 1; j <= i; j++) {
                s += std::move(std::to_string(i));
            }
            i++;
        }
    }

    for (int i = 1; i <= 1000000; i++) {
        a[i] = a[i - 1] + s[i] - '0';
    }

    int T;
    read(T);
    while (T--) {
        int l, r, ans{};
        read(l, r);
        std::cout << a[r] - a[l - 1] << '\n';
    }

    return 0;
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