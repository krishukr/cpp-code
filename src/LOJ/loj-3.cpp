#include <cstdio>
#include <cstring>
#include <iostream>

template <typename T>
T read();

int main() {
    freopen("copycat.in", "r", stdin);
    freopen("copycat.out", "w", stdout);

    int t = read<int>();
    while (t--) {
        std::string s;
        std::cin >> s;
        std::cout << s << '\n';
    }

    fclose(stdin);
    fclose(stdout);
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