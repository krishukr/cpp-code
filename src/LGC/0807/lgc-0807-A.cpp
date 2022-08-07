#include <algorithm>
#include <cstdio>
#include <iostream>
#include <map>

std::map<char, char> mp{
    {'0', '0'}, {'1', '1'}, {'2', '5'}, {'5', '2'}, {'8', '8'}, {'A', 'A'},
    {'H', 'H'}, {'I', 'I'}, {'J', 'L'}, {'L', 'J'}, {'M', 'M'}, {'O', 'O'},
    {'T', 'T'}, {'U', 'U'}, {'V', 'V'}, {'W', 'W'}, {'X', 'X'}, {'Y', 'Y'}};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string s;
    std::cin >> s;
    std::reverse(s.begin(), s.end());
    for (auto& i : s) {
        i = mp[i];
    }
    std::cout << s << '\n';

    return 0;
}
