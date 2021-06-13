#include <cstring>
#include <iostream>

int nxt[10000005];

void init(std::string s);

void kmp(std::string t, std::string p);

int main() {
    std::ios::sync_with_stdio(false);

    int n;
    std::string t;
    std::cin >> n >> t;
    init(t);
    std::cout << n - nxt[n];

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