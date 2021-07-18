#include <cstdio>
#include <iostream>
#include <vector>

std::vector<std::vector<int> > v;
std::vector<long long> ans;

template <typename T>
T read();

int main() {
    freopen("control.in", "r", stdin);
    freopen("control.out", "w", stdout);

    std::vector<int> t;
    int n = read<int>(), m = read<int>();
    for (int i = 1; i <= n; i++) {
        int a = read<int>();
        for (int j = 1; j <= a; j++) {
            int x = read<int>();
            t.push_back(x);
        }
        v.push_back(t);
        t.clear();
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