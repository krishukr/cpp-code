#include <cstdio>
#include <iostream>

const int MAX_N = 10000050;

bool ile[MAX_N];
int nxt[MAX_N];

bool check(int x);

void init(int n);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    init(10000010);

    int T = read<int>();
    while (T--) {
        int x = read<int>();
        if (ile[x]) {
            std::cout << -1 << '\n';
        } else {
            std::cout << nxt[x] << '\n';
        }
    }

    return 0;
}

bool check(int x) {
    while (x) {
        if (x % 10 == 7) {
            return true;
        }
        x /= 10;
    }
    return false;
}

void init(int n) {
    for (int i = 1; i <= n; i++) {
        if (check(i)) {
            for (int j = 1; j * i <= n; j++) {
                ile[j * i] = true;
            }
        }
    }

    int pre = 0;
    for (int i = 1; i <= n; i++) {
        if (!ile[i]) {
            nxt[pre] = i;
            pre = i;
        }
    }
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