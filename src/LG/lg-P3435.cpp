#include <cstring>
#include <iostream>

int nxt[10000005];

void init(std::string s);

int main() {
    std::ios::sync_with_stdio(false);

    int n;
    long long ans = 0;
    std::string t;
    std::cin >> n >> t;
    init(t);
    for (int i = 2, j = 2; i <= n; i++, j = i) {
        while (nxt[j]) {
            j = nxt[j];
        }
        if (nxt[i]) {
            nxt[i] = j;
        }
        ans += i - j;
    }
    std::cout << ans << '\n';

    return 0;
}

void init(std::string s) {
    int i = 0, j;
    nxt[0] = j = -1;
    while (i < s.length()) {
        if (j == -1 or s[i] == s[j]) {
            nxt[++i] = ++j;
        } else {
            j = nxt[j];
        }
    }
}