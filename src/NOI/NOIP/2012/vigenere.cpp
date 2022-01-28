#include <cstdio>
#include <cstring>
#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);

    std::string k, s;
    std::cin >> k >> s;

    for (int i = 0; i < s.length(); i++) {
        int code = (k[i % k.length()] & 31) - 1;
        s[i] = ((s[i] & 31) - code > 0 ? s[i] - code : s[i] - code + 26);
    }

    std::cout << s << '\n';

    return 0;
}