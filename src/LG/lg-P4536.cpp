#include <algorithm>
#include <cstdio>
#include <iostream>

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    std::string s;
    std::string a[4];
    std::cin >> s;
    if (s.back() == '4') {
        s.pop_back();
        for (int i = 1; i <= 3; i++) {
            std::cout << s << i << '\n';
        }
    } else {
        for (size_t i = 1; i < s.length(); i++) {
            a[s[i] - '0'] = s.substr(0, i) + '4';
        }
        std::sort(a + 1, a + 4);

        for (int i = 1; i <= 3; i++) {
            if (!a[i].empty()) {
                std::cout << a[i] << '\n';
            }
        }
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