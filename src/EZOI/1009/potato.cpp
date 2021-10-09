#include <cmath>
#include <cstdio>
#include <iostream>

typedef long long ll;

const int MAX_N = 200050;

int ic[MAX_N], fr[MAX_N];

inline ll calc(double x);

template <typename T>
T read();

int main() {
    freopen("potato.in", "r", stdin);
    freopen("potato.out", "w", stdout);

    int n = read<int>();
    ll s1 = 0, s2 = 0;
    for (int i = 1; i <= n; i++) {
        ic[i] = read<int>();
        s1 += ic[i];
    }
    for (int i = 1; i <= n; i++) {
        fr[i] = read<int>();
        s2 += fr[i];
    }

    int m = read<int>();
    for (int i = 1; i <= m; i++) {
        int op = read<int>(), x = read<int>(), t = read<int>();
        int l = read<int>(), r = read<int>();

        if (op) {
            fr[x] += t;
            s2 += t;
        } else {
            ic[x] += t;
            s1 += t;
        }

        if (l > fr[1] or r <= ic[1]) {
            std::cout << "NO\n";
            continue;
        }

        ll tmp = calc((s1 + s2) / (2.0 * n));
        if (tmp < l) {
            std::cout << l << '\n';
        } else if (tmp > r) {
            std::cout << r << '\n';
        } else {
            std::cout << tmp << '\n';
        }
    }

    fclose(stdin);
    fclose(stdout);
    return 0;
}

inline ll calc(double x) { return (x > 0 ? x + 0.5 : x - 0.5); }

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