#include <cstdio>
#include <iostream>

typedef long long ll;

const int MAX_N = 1000050;

ll f[MAX_N], ans[MAX_N];

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>();
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j += i) {
            f[j] += i;
        }
    }

    ans[1] = 1;
    for (int i = 2; i <= n; i++) {
        ans[i] = ans[i - 1] + f[i];
    }

    for (int i = 1; i <= n; i++) {
        std::cout << 1ll * n * i - ans[i] << ' ';
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