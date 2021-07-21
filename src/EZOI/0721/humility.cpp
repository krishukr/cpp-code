#include <cstdio>
#include <iostream>

typedef long long ll;

int num[9] = {9, 1, 2, 3, 4, 5, 6, 7, 8};

template <typename T>
T read();

int main() {
    freopen("humility.in", "r", stdin);
    freopen("humility.out", "w", stdout);

    int T = read<int>();
    while (T--) {
        ll x = read<ll>(), k = read<ll>();

        ll xx = x % 9, kk = k % 9, ans = num[xx], pos = 0;

        for (int i = 1; i <= 9; i++) {
            if (num[(i * kk + xx) % 9] < ans) {
                ans = num[(i * kk + xx) % 9];
                pos = i;
            }
        }
        x += pos * k;

        while (x != ans) {
            ll idx = 0;
            while (x) {
                idx += x % 10;
                x /= 10;
            }
            x = idx;
            pos++;
        }

        std::cout << ans << ' ' << pos << '\n';
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