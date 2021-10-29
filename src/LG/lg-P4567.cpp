#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>

int main() {
    // std::ios::sync_with_stdio(false);

    std::string buffer;
    int ptr = 0;

    int n;
    std::cin >> n;
    while (n--) {
        std::string ops;
        std::cin >> ops;
        char op = ops[0];

        if (op == 'M') {
            std::cin >> ptr;
        } else if (op == 'I') {
            int x;
            std::cin >> x;
            std::string s;
            char ch = getchar();

            for (int i = 1; i <= x; i++) {
                s += getchar();
            }

            buffer.insert(buffer.begin() + ptr, s.begin(), s.end());
        } else if (op == 'D') {
            int x;
            std::cin >> x;
            buffer.erase(buffer.begin() + ptr, buffer.begin() + ptr + x);
        } else if (op == 'R') {
            int x;
            std::cin >> x;
            std::reverse(buffer.begin() + ptr, buffer.begin() + ptr + x);
        } else if (op == 'G') {
            putchar(buffer[ptr]);
            if (buffer[ptr] != '\n') {
                putchar('\n');
            }
        } else if (op == 'P') {
            ptr--;
        } else if (op == 'N') {
            ptr++;
        }
    }

    return 0;
}