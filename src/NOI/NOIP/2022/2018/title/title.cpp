#include <bits/stdc++.h>

int main() {
    freopen("title.in", "r", stdin);
    freopen("title.out", "w", stdout);
    std::ios::sync_with_stdio(false);

    std::string s;
    std::getline(std::cin, s);
    int r{};
    for (const auto& i : s) {
        r += (int)((bool)(isalnum(i)));
    }
    std::cout << r << '\n';

    std::cout << std::flush;
    fclose(stdin);
    fclose(stdout);
    return 0;
}