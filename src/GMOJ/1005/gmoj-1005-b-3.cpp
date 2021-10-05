#include <cstdio>
#include <iostream>

const int MAX_N = 1000050;

int a[MAX_N], b[MAX_N], r[MAX_N];
int n;

bool check();

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n1 = read<int>();
    for (int i = 1; i <= n1; i++) {
        a[i] = read<int>();
    }

    int n2 = read<int>();
    for (int i = 1; i <= n2; i++) {
        b[i] = read<int>();
    }

    n = std::max(n1, n2);
    for (int i = 1; i <= n; i++) {
        r[i] = a[i] + b[i];
    }

    while (check()) {
        for (int i = 1; i <= n; i++) {
            if (r[i] == 2) {
                r[i - 2]++;
                r[i + 1]++;
                r[i] = 0;
            }
            if (r[i] == r[i - 1] and r[i] == 1) {
                r[i] = r[i - 1] = 0;
                r[i + 1]++;
            }

            if (r[n + 1]) {
                n++;
            }
        }
        if (r[0] == 1) {
            r[0] = 0;
            r[1] = 1;
        }
    }

    std::cout << n << ' ';
    for (int i = 1; i <= n; i++) {
        std::cout << r[i] << ' ';
    }
    std::cout << '\n';

    return 0;
}

bool check() {
    for (int i = 1; i <= n; i++) {
        if ((r[i] == r[i - 1] and r[i] == 1) or r[i] >= 2) {
            return true;
        }
    }
    return false;
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