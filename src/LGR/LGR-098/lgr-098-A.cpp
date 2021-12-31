#include <cmath>
#include <cstdio>
#include <iostream>

template <typename T>
T read();

typedef long long ll;

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>();
    ll k = read<ll>(), sum = 0;
    auto* a = new int[n + 5];

    for (int i = 1; i <= n; i++) {
        a[i] = read<int>();
        sum += a[i];
    }

    bool flag = false;
    for (int i = 2; i <= n; i++) {
        if (a[i] != a[i - 1]) {
            flag = true;
            break;
        }
    }

    if (!flag) {
        std::cout << "No answer!\n";
        return 0;
    }

    double avg = 1.0 * sum / n, dif = 0;
    for (int i = 1; i <= n; i++) {
        dif += ((double)a[i] - avg) * ((double)a[i] - avg);
    }
    dif = std::sqrt(dif);

    if (dif >= k) {
        std::cout << 1 << '\n';
    } else {
        std::cout << (std::sqrt(1.0 * k / dif)) << '\n';
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