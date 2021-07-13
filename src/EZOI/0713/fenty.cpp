#include <cstdio>
#include <iostream>

const int mod1 = 1e9 + 7;
const int mod2 = 1e9 + 9;

typedef long long ll;

ll a[15], b;

template <typename T>
T read();

int main() {
    freopen("fenty.in", "r", stdin);
    freopen("fenty.out", "w", stdout);

    int n = read<int>();
    for (int i = n; ~i; i--) {
        a[i] = read<ll>();
    }
    b = a[n];
    for (int i = n; ~i; i--) {
        a[i] /= b;
    }

    if (b != 1) {
        if (b == -1) {
            putchar('-');
        } else {
            printf("%lld", b);
        }
    }
    if (!a[0]) {
        for (int i = 0; i < n; i++) {
            a[i] = a[i + 1];
        }
        n--;
        putchar('x');
    }

    for (int i = 1e6; i >= -1e6; i--) {
        if (i != 0) {
            int ans1 = 0, ans2 = 0, p1 = 1, p2 = 1;
            for (int j = 0; j <= n; j++) {
                ans1 = (ans1 + a[j] % mod1 * p1) % mod1;
                ans2 = (ans2 + a[j] % mod2 * p2) % mod2;
                p1 = 1ll * p1 * i % mod1;
                p2 = 1ll * p2 * i % mod2;
            }
            if (!ans1 && !ans2) {
                printf("(x");
                if (i < 0) {
                    putchar('+');
                }
                printf("%d)", -i);
            }
        }
    }
    std::cout << '\n';

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