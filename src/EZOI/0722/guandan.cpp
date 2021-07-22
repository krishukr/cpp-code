#include <algorithm>
#include <cstdio>
#include <iostream>

const int MAX_N = 100050;

int val[MAX_N];

template <typename T>
T read();

int main() {
    freopen("guandan.in", "r", stdin);
    freopen("guandan.out", "w", stdout);

    int B = read<int>(), N = read<int>(), D = read<int>(), M = read<int>();

    if (B == 1) {
        long long res = 0;

        for (int i = 1; i <= N; i++) {
            val[i] = read<int>();
        }
        std::sort(val + 1, val + N + 1);

        int j = 1;
        for (int i = 1; i <= N; i++) {
            while (val[i] - val[j] > D and j < i) {
                j++;
            }
            res += i - j;
        }

        std::cout << res << '\n';
    } else {
        std::cout << "FUCK\n";
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