#include <algorithm>
#include <iostream>

typedef unsigned long long ull;

const int MAX_N = 10010;
const int BASE = 114514;

ull power[MAX_N], hash[MAX_N];

int main() {
    std::ios::sync_with_stdio(false);

    int n, ans = 0;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::string s;
        std::cin >> s;
        for (int j = 0; j < s.length(); j++) {
            hash[i] = hash[i] * BASE + (ull)(s[j] - '0' + 1);
        }
    }

    std::sort(hash, hash + n);
    for (int i = 0; i < n; i++) {
        if (hash[i] != hash[i + 1]) {
            ans++;
        }
    }
    std::cout << ans << '\n';

    return 0;
}