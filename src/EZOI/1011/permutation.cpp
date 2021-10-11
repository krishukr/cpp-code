#include <cstdio>
#include <iostream>
#include <vector>

const int MAX_N = 100;

int a[MAX_N];

template <typename T>
T read();

int main() {
    freopen("permutation.in", "r", stdin);
    freopen("permutation.out", "w", stdout);

    int n = read<int>(), ans = 0;
    for (int i = 1; i <= n; i++) {
        a[i] = i;
    }

    do {
        bool flag = true;
        for (int i = 1; flag and i <= n; i++) {
            for (int j = i + 1; flag and j <= n; j++) {
                if (std::__algo_gcd(i, j) == 1 and
                    std::__algo_gcd(a[i], a[j]) != 1) {
                    flag = false;
                    break;
                }
                if (std::__algo_gcd(a[i], a[j]) == 1 and
                    std::__algo_gcd(i, j) != 1) {
                    flag = false;
                    break;
                }
            }
        }
        if (flag) {
            ans++;
        }
    } while (std::next_permutation(a + 1, a + n + 1));

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