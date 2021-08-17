#include <cstdio>
#include <iostream>

template <typename T>
T read();

const int MAX_N = 250;

class rps {
   public:
    int cyc[MAX_N];
    int len;
    int score;

    void in() {
        for (int i = 0; i < len; i++) {
            cyc[i] = read<int>();
        }
    }

    void out() { std::cout << score << ' '; }
} a, b;

int pts[5][5] = {{0, 0, 1, 1, 0},
                 {1, 0, 0, 1, 0},
                 {0, 1, 0, 0, 1},
                 {0, 0, 1, 0, 1},
                 {1, 1, 0, 0, 0}};

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>();
    a.len = read<int>(), b.len = read<int>();

    a.in(), b.in();

    for (int i = 0; i < n; i++) {
        a.score += pts[a.cyc[i % a.len]][b.cyc[i % b.len]];
        b.score += pts[b.cyc[i % b.len]][a.cyc[i % a.len]];
    }

    a.out(), b.out();

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