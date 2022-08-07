#include <cstdio>
#include <iostream>

using ull = unsigned long long;

constexpr int MAX_N = 65536;
constexpr ull MOD = 1e9 + 7;

constexpr ull x1 = 94153035;
constexpr ull x2 = 905847205;
constexpr ull x3 = 64353223;
constexpr ull x4 = 847809841;
constexpr ull k = 233230706;

namespace Mker {
unsigned long long SA, SB, SC;
void init() { scanf("%llu%llu%llu", &SA, &SB, &SC); }
unsigned long long rand() {
    SA ^= SA << 32, SA ^= SA >> 13, SA ^= SA << 1;
    unsigned long long t = SA;
    SA = SB, SB = SC, SC ^= t ^ SA;
    return SC;
}
}  // namespace Mker

struct ANS {
    ull s1[MAX_N], s2[MAX_N], s3[MAX_N], s4[MAX_N];

    constexpr ANS() : s1(), s2(), s3(), s4() {
        s1[0] = 1;
        for (int i = 1; i < 65536; i++) {
            s1[i] = s1[i - 1] * x1 % MOD;
        }
        s2[0] = 1;
        for (int i = 1; i < 65536; i++) {
            s2[i] = s2[i - 1] * x2 % MOD;
        }
        s3[0] = 1;
        for (int i = 1; i < 65536; i++) {
            s3[i] = s3[i - 1] * x3 % MOD;
        }
        s4[0] = 1;
        for (int i = 1; i < 65536; i++) {
            s4[i] = s4[i - 1] * x4 % MOD;
        }
    }
};

template <typename T>
T read();

template <typename T>
void read(T& t);

int main() {
    std::ios::sync_with_stdio(false);

    constexpr auto ans = ANS();

    int T;
    read(T);
    Mker::init();
    ull r{};
    while (T--) {
        auto n = Mker::rand();
        n %= (MOD - 1);
        r ^= k *
             ((ans.s3[n >> 16] * ans.s1[n & 65535] % MOD) -
              (ans.s4[n >> 16] * ans.s2[n & 65535] % MOD) + MOD) %
             MOD;
    }
    std::cout << r << '\n';

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

template <typename T>
void read(T& t) {
    t = read<T>();
}