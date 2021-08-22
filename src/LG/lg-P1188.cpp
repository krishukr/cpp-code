#include <cstdio>
#include <iostream>
#include <vector>

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), k = read<int>();

    std::vector<int> v;
    typedef std::vector<int>::const_iterator it;

    for (int i = 1; i <= n; i++) {
        v.push_back(i);
    }

    for (int i = 1; i <= k; i++) {
        int x = read<int>(), y = read<int>(), z = read<int>();

        it l = v.begin() + x - 1, r = v.begin() + y;
        std::vector<int> c(l, r);

        v.erase(l, r);
        v.insert(v.begin() + z, c.begin(), c.end());
    }

    for (int i = 0; i < 10; i++) {
        std::cout << v[i] << '\n';
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