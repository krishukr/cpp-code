#include <cstdio>
#include <iostream>

typedef long long ll;

const int MAX_N = 100010;

ll sum[MAX_N * 4];

void mod(int k, int l, int r, int v, int x);

ll query(int k, int l, int r, int x, int y);

inline int read() {
    int x = 0, f = 1, ch = getchar();
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

int main() {
    std::ios::sync_with_stdio(false);

    int n = read(), m = read();
    while (m--) {
        int op = read(), x = read(), y = read();
        if (op) {
            std::cout << query(1, 1, n, x, y) << "\n";
        } else {
            mod(1, 1, n, y, x);
        }
    }

    return 0;
}

void mod(int k, int l, int r, int v, int x) {
    if (x < l or x > r) {
        return;
    }
    if (l == r and l == x) {
        sum[k] += v;
        return;
    }
    int mid = (l + r) / 2;
    mod(k * 2, l, mid, v, x);
    mod(k * 2 + 1, mid + 1, r, v, x);
    sum[k] = sum[k * 2] + sum[k * 2 + 1];
}

ll query(int k, int l, int r, int x, int y) {
    if (r < x or y < l) {
        return 0;
    }
    if (l >= x and y >= r) {
        return sum[k];
    }
    int mid = (l + r) / 2;
    return query(k * 2, l, mid, x, y) + query(k * 2 + 1, mid + 1, r, x, y);
}