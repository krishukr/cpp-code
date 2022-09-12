#include <cstdio>
#include <iostream>

using ll = long long;

constexpr ll B = 2147483647;

int main() {
    std::ios::sync_with_stdio(false);

    char op;
    ll n1, n2;
    scanf("a+%lld%[><]%lld", &n1, &op, &n2);
    std::cout << B - (op == '>' ? n2 : -n2 - 1) << '\n';

    return 0;
}
