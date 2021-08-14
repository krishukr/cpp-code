#include <cstdio>
#include <cstring>
#include <iostream>

const std::string s =
    "vector<vector<int>>ans={{2},{3},{2,2},{5},{2,3},{3,3},{2,2,2},{7},{2,5},{"
    "2,2,3},{3,5},{2,3,3},{2,2,2,2},{2,7},{2,2,5},{3,3,3},{2,2,2,3},{3,7},{5,5}"
    ",{2,3,5},{2,2,3,3},{2,2,2,2,2},{11},{2,2,7},{3,3,5},{2,2,2,5},{2,3,3,3},{"
    "2,2,2,2,3},{5,7},{2,3,7},{2,5,5},{2,2,3,5},{3,3,3,3},{2,2,2,3,3},{2,2,2,2,"
    "2,2},{13},{2,11},{3,3,7},{3,5,5},{2,2,2,7},{2,3,3,5},{2,2,2,2,5},{2,2,3,3,"
    "3},{2,2,2,2,2,3},{3,11},{7,7},{2,5,7},{2,2,3,7},{2,2,5,5},{3,3,3,5},{2,2,"
    "2,3,5},{2,3,3,3,3},{2,2,2,2,3,3},{2,2,2,2,2,2,2},{2,13},{2,2,11},{3,5,7},{"
    "5,5,5},{2,3,3,7},{2,3,5,5},{2,2,2,2,7},{2,2,3,3,5},{3,3,3,3,3},{2,2,2,2,2,"
    "5},{2,2,2,3,3,3},{2,2,2,2,2,2,3},{3,13},{5,11},{2,3,11},{2,7,7},{2,2,5,7},"
    "{3,3,3,7},{3,3,5,5},{2,2,2,3,7},{2,2,2,5,5},{2,3,3,3,5},{2,2,2,2,3,5},{2,"
    "2,3,3,3,3},{2,2,2,2,2,3,3},{2,2,2,2,2,2,2,2},{17},{2,2,13},{3,3,11},{3,7,"
    "7},{5,5,7},{2,2,2,11},{2,3,5,7},{2,5,5,5},{2,2,3,3,7},{2,2,3,5,5},{3,3,3,"
    "3,5},{2,2,2,2,2,7},{2,2,2,3,3,5},{2,3,3,3,3,3},{2,2,2,2,2,2,5},{2,2,2,2,3,"
    "3,3},{2,2,2,2,2,2,2,3},{5,13},{7,11},{2,3,13},{2,5,11},{2,2,3,11},{2,2,7,"
    "7},{3,3,5,7},{3,5,5,5},{2,2,2,5,7},{2,3,3,3,7},{2,3,3,5,5},{2,2,2,2,3,7},{"
    "2,2,2,2,5,5},{2,2,3,3,3,5},{3,3,3,3,3,3},{2,2,2,2,2,3,5},{2,2,2,3,3,3,3},{"
    "2,2,2,2,2,2,3,3},{2,2,2,2,2,2,2,2,2},{19},{2,17},{3,3,13},{3,5,11},{5,7,7}"
    ",{2,2,2,13},{2,3,3,11},{2,3,7,7},{2,5,5,7},{2,2,2,2,11},{2,2,3,5,7},{2,2,"
    "5,5,5},{3,3,3,3,7},{3,3,3,5,5},{2,2,2,3,3,7},{2,2,2,3,5,5},{2,3,3,3,3,5},{"
    "2,2,2,2,2,2,7},{2,2,2,2,3,3,5},{2,2,3,3,3,3,3},{2,2,2,2,2,2,2,5},{2,2,2,2,"
    "2,3,3,3},{2,2,2,2,2,2,2,2,3},{3,17},{7,13},{2,5,13},{2,7,11},{2,2,3,13},{"
    "2,2,5,11},{3,3,3,11},{3,3,7,7},{3,5,5,7},{5,5,5,5},{2,2,2,3,11},{2,2,2,7,"
    "7},{2,3,3,5,7},{2,3,5,5,5},{2,2,2,2,5,7},{2,2,3,3,3,7},{2,2,3,3,5,5},{3,3,"
    "3,3,3,5},{2,2,2,2,2,3,7},{2,2,2,2,2,5,5},{2,2,2,3,3,3,5},{2,3,3,3,3,3,3},{"
    "2,2,2,2,2,2,3,5},{2,2,2,2,3,3,3,3},{2,2,2,2,2,2,2,3,3},{2,2,2,2,2,2,2,2,2,"
    "2},{2,19},{2,2,17},{3,5,13},{3,7,11},{5,5,11},{7,7,7},{2,3,3,13},{2,3,5,"
    "11},{2,5,7,7},{2,2,2,2,13},{2,2,3,3,11},{2,2,3,7,7},{2,2,5,5,7},{3,3,3,5,"
    "7},{3,3,5,5,5},{2,2,2,2,2,11},{2,2,2,3,5,7},{2,2,2,5,5,5},{2,3,3,3,3,7},{"
    "2,3,3,3,5,5},{2,2,2,2,3,3,7},{2,2,2,2,3,5,5},{2,2,3,3,3,3,5},{3,3,3,3,3,3,"
    "3},{2,2,2,2,2,2,2,7},{2,2,2,2,2,3,3,5},{2,2,2,3,3,3,3,3},{2,2,2,2,2,2,2,2,"
    "5},{2,2,2,2,2,2,3,3,3},{2,2,2,2,2,2,2,2,2,3},{3,19},{5,17},{11,11},{2,3,"
    "17},{2,7,13},{2,2,5,13},{2,2,7,11},{3,3,3,13},{3,3,5,11},{3,5,7,7},{5,5,5,"
    "7},{2,2,2,3,13},{2,2,2,5,11},{2,3,3,3,11},{2,3,3,7,7},{2,3,5,5,7},{2,5,5,"
    "5,5},{2";

template <typename T>
T read();

int main() {
    freopen("asahi.in", "r", stdin);
    freopen("asahi.out", "w", stdout);

    int l = read<int>(), r = read<int>();

    if (r < s.length()) {
        for (int i = l; i <= r; i++) {
            std::cout << s[i - 1];
        }
    } else {
        std::cout << "FUCK";
    }

    fclose(stdin);
    fclose(stdout);
    return 0;
}

template <typename T>
T read() {
    T x = 0, f = 1;
    char ch = getchar();
    while (!isdigit(ch)) {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (isdigit(ch)) {
        x = x * 10 + ch - 48;
        ch = getchar();
    }
    return x * f;
}