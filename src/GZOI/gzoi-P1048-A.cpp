#include <cstdio>
#include <iostream>
#include <string>
#include <unordered_set>

std::unordered_set<std::string> st;

int main() {
    std::ios::sync_with_stdio(false);

    int n;
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        std::string op, s;
        std::cin >> op >> s;
        if (op[0] == 'i') {
            st.insert(s);
        } else if (op[0] == 'f') {
            std::cout << (st.find(s) == st.end() ? "no" : "yes") << '\n';
        }
    }

    return 0;
}