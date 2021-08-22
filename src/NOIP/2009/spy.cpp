#include <cstdio>
#include <cstring>
#include <iostream>

template <typename T>
T read();

std::string a, b, c;
int cnt[100];

int main() {
    // std::ios::sync_with_stdio(false);

    std::cin >> a >> b >> c;
    int s1 = 0, s2 = 0;

    for (int i = 0; i < a.length(); i++) {
        if (cnt[a[i]] and cnt[a[i]] != b[i]) {
            std::cout << "Failed\n";
            return 0;
        }
        cnt[a[i]] = b[i];
    }

    for (int i = 'A'; i <= 'Z'; i++) {
        s1 += i;
        s2 += cnt[i];
    }

    if (s1 != s2) {
        std::cout << "Failed\n";
        return 0;
    }

    for (int i = 0; i < c.length(); i++) {
        std::cout << (char)cnt[c[i]];
    }
    std::cout << '\n';

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