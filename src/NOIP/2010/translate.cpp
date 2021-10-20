#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>

template <typename T>
T read();

int main() {
    freopen("translate.in", "r", stdin);
    freopen("translate.out", "w", stdout);

    std::vector<int> mem;

    int n = read<int>(), m = read<int>(), ans = 0;
    for (int i = 1; i <= m; i++) {
        int x = read<int>();
        if (std::find(mem.begin(), mem.end(), x) == mem.end()) {
            ans++;
            mem.push_back(x);
        }

        if (mem.size() > n) {
            mem.erase(mem.begin());
        }
    }

    std::cout << ans << '\n';

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