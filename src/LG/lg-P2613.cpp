#include <cstdio>
#include <iostream>

using namespace std;

const int MOD = 19260817;

long long quick_pow(long long a, long long b);

inline int getint() {
    int res = 0, ch = getchar();
    while (!isdigit(ch) and ch != EOF) ch = getchar();
    while (isdigit(ch)) {
        res = (res << 3) + (res << 1) + (ch - '0');
        res %= MOD;
        ch = getchar();
    }
    return res;
}

int main() {
    std::ios::sync_with_stdio(false);
    long long a, b;
    a = getint(), b = getint();
    if (b) {
        cout << (quick_pow(b, MOD - 2) % MOD * a % MOD + MOD) % MOD << endl;
    } else {
        cout << "Angry!" << endl;
    }

    return 0;
}

long long quick_pow(long long a, long long b) {
    long long res = 1;
    while (b) {
        if (b & 1) {
            res = res * a % MOD;
        }
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}