#include <cstdio>
#include <iostream>

typedef long long ll;

int main() {
    std::ios::sync_with_stdio(false);

    ll n, m;
    char op;
    std::cin >> n;
    while (std::cin >> op >> m) {
        switch (op) {
            case '+':
                n += m;
                break;
            case '-':
                n -= m;
                break;
            case '*':
                n *= m;
                break;
            case '%':
                n %= m;
                break;
            case '^':
                n *= n;
                break;
            default:
                break;
        }
    }

    std::cout << std::abs(n) << '\n';

    return 0;
}