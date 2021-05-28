#include <bits/stdc++.h>

using namespace std;

long long quick_pow(long long a, long long b, long long m);

int main() {
    long b, q, k;
    cin >> b >> q >> k;
    printf("%d^%d mod %d=%d", b, q, k, quick_pow(b, q, k) % k);
}

long long quick_pow(long long a, long long b, long long m) {
    a %= m;
    long long res = 1;
    while (b > 0) {
        if (b & 1) res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}