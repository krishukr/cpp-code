#include <cstdio>
#include <iostream>

using ll = long long;

int main() {
    std::ios::sync_with_stdio(false);

    ll n, a, b, r{};
    std::cin >> n >> a >> b;
    for (int i = 1; i <= n; i++) {
        std::string u, s;
        std::cin >> u >> s;
        if (s == "/oh") {
            r += a;
        } else if (s == "/hsh") {
            r += b;
        }
    }
    std::cout << r << '\n';

    return 0;
}