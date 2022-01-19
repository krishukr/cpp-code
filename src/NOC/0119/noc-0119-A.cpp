#include <cstdio>
#include <iostream>

typedef long long ll;

const int MAX_N = 100050;

ll a[MAX_N], s[MAX_N], q[MAX_N];

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>();
    for (int i = 1; i <= n; i++) {
        a[i] = read<int>();
        s[i] = s[i - 1] + a[i];
        q[i] = q[i - 1] + a[i] * a[i];
    }

    for (int i = 1; i <= n; i++) {
        ll a1 = (q[n] - q[i] + q[i - 1]) * (n - 1);
        ll a2 = s[n] - s[i] + s[i - 1];
        std::cout << a1 - a2 * a2 << ' ';
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