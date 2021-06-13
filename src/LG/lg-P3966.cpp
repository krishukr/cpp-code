#include <iostream>

const int MAX_N = 205;

std::string s[MAX_N];
int cnt[MAX_N];

int main() {
    std::ios::sync_with_stdio(false);

    int n, p;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> s[i];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0;
                 k < s[j].length() and (p = s[j].find(s[i], k)) != s[j].npos;
                 k++) {
                k = p;
                cnt[i]++;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        std::cout << cnt[i] << '\n';
    }

    return 0;
}