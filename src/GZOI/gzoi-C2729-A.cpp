#include <cctype>
#include <cstdio>
#include <iostream>
#include <string>

int main() {
    std::ios::sync_with_stdio(false);

    std::string s;
    std::cin >> s;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] != '-') {
            std::cout << s[i];
            continue;
        }
        if (s[i + 1] > s[i - 1] and
            ((islower(s[i + 1]) and islower(s[i - 1])) or
             (isdigit(s[i + 1]) and isdigit(s[i - 1])))) {
            for (char j = s[i - 1] + 1; j <= s[i + 1] - 1; j++) {
                std::cout << j;
            }
        } else {
            std::cout << s[i];
        }
    }
    std::cout << '\n';

    return 0;
}
