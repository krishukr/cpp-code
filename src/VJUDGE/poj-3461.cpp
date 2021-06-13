#include <iostream>

typedef unsigned long long ull;

const int MAX_N = 1000010;
const int BASE = 114514;

ull power[MAX_N], hash[MAX_N];

void init();

int main() {
    std::ios::sync_with_stdio(false);
    init();

    int T;
    std::cin >> T;
    while (T--) {
        std::string p, s;
        ull ps = 0;
        int ans = 0;

        std::cin >> p >> s;
        for (int i = 1; i <= s.length(); i++) {
            hash[i] = hash[i - 1] * BASE + (ull)(s[i - 1] - 'A' + 1);
        }
        for (int i = 1; i <= p.length(); i++) {
            ps = ps * BASE + (ull)(p[i - 1] - 'A' + 1);
        }

        for (int i = 0; i <= s.length() - p.length(); i++) {
            if (ps == hash[i + p.length()] - hash[i] * power[p.length()]) {
                ans++;
            }
        }
        std::cout << ans << '\n';
    }

    return 0;
}

void init() {
    power[0] = 1;
    for (int i = 1; i < MAX_N; i++) {
        power[i] = power[i - 1] * BASE;
    }
}