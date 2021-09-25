#include <climits>
#include <cstdio>
#include <iostream>

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int mu = INT_MAX, md = INT_MAX, su = 0, sd = 0;

    int n = read<int>();
    for (int i = 1; i <= n; i++) {
        int u = read<int>(), d = read<int>();
        su += u, sd += d;

        mu = std::min(mu, u);
        md = std::min(md, d);
    }

    std::cout << std::max(mu + sd, md + su) << '\n';

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