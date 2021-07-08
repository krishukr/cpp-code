#include <cmath>
#include <iostream>

inline int read();

int main() {
    std::ios::sync_with_stdio(false);
    freopen("stand.in", "r", stdin);
    freopen("stand.out", "w", stdout);

    int n = read(), m = read(), ans = 0;
    for (int i = 0; i < 5; i++) {
        ans += read() * std::pow(n, i + 1);
    }

    std::cout << ans << '\n';

    fclose(stdin);
    fclose(stdout);
    return 0;
}

inline int read() {
    int x = 0, f = 1;
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