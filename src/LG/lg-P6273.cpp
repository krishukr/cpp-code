#include <algorithm>
#include <cstdio>
#include <functional>
#include <iostream>
#include <map>

constexpr int MAX_N = 100050;
constexpr int MAX_S = 64;
constexpr int MOD = 1e9 + 7;

char s[MAX_N], b[MAX_N];
int cnt;

struct Node {
    char t[MAX_S];

    friend bool operator<(const Node& a, const Node& b) {
        for (int i = 1; i <= cnt; i++) {
            if (a.t[i] != b.t[i]) {
                return a.t[i] < b.t[i];
            }
        }
        return false;
    }
} node[MAX_N];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n >> (s + 1);
    for (int i = 1; i <= n; i++) {
        b[i] = s[i];
    }
    std::sort(b + 1, b + n + 1);
    cnt = std::unique(b + 1, b + n + 1) - b - 1;
    for (int i = 1; i <= n; i++) {
        s[i] = std::lower_bound(b + 1, b + cnt + 1, s[i]) - b;
    }

    std::map<int, int, std::function<bool(int, int)>> mp(
        [](const int& a, const int& b) { return node[a] < node[b]; });
    mp[0] = 1;

    long long a{};
    for (int i = 1; i <= n; i++) {
        node[i] = node[i - 1];
        if (s[i] > 1) {
            node[i].t[s[i]]++;
        } else {
            for (int j = 2; j <= cnt; j++) {
                node[i].t[j]--;
            }
        }
        a += mp[i]++;
    }
    std::cout << a % MOD << '\n';

    return 0;
}