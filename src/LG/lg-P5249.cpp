#include <cstdio>
#include <iomanip>
#include <iostream>

const int MAX_N = 100050;
const int M = 100000;

double s1[MAX_N], s2[MAX_N], s3[MAX_N];

double quick_pow(double a, int b);

int main() {
    std::ios::sync_with_stdio(false);

    double p, ans = 0;
    int n, k;
    std::cin >> p >> n >> k;

    if (n == 1) {
        std::cout << 1 << '\n';
        return 0;
    }

    for (int i = 1; i <= M; i++) {
        s1[i] = 1 - quick_pow(1 - p, i);
        s2[i] = quick_pow(s1[i], k - 1);
        s3[i] = quick_pow(s1[i], n - k);
    }

    for (int i = 1; i <= M; i++) {
        if (k == n) {
            ans += s2[i] * (s1[i] - s1[i - 1]);
        } else if (k == 1) {
            ans += s3[i - 1] * (s1[i] - s1[i - 1]);
        } else {
            ans += s2[i] * s3[i - 1] * (s1[i] - s1[i - 1]);
        }
    }

    std::cout << std::fixed << std::setprecision(8) << ans << '\n';

    return 0;
}

double quick_pow(double a, int b) {
    double res = 1;
    while (b) {
        if (b & 1) {
            res = res * a;
        }
        a = a * a;
        b >>= 1;
    }
    return res;
}