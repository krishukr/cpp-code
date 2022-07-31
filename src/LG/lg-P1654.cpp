#include <cstdio>
#include <iomanip>
#include <iostream>

constexpr int MAX_N = 100050;

double x[MAX_N], y[MAX_N], z[MAX_N];

int main() {
    std::ios::sync_with_stdio(false);

    int n;
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        double a;
        std::cin >> a;
        x[i] = (x[i - 1] + 1) * a;
        y[i] = (y[i - 1] + 2 * x[i - 1] + 1) * a;
        z[i] = z[i - 1] + (3 * y[i - 1] + 3 * x[i - 1] + 1) * a;
    }
    std::cout << std::fixed << std::setprecision(1) << z[n] << '\n';

    return 0;
}