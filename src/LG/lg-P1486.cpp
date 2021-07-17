#include <cstdio>
#include <iostream>

const int MAX_N = 400001;

int tree[MAX_N << 2];
int m, b;

void update(int x);

void mod(int x, int l, int r, int k, int v);

int sum(int k, int l, int r, int x, int y);

int query(int x, int l, int r, int k);

void clear(int x, int l, int r, int u, int v);

template <typename T>
T read();

int main() {
    // std::ios::sync_with_stdio(false);

    int n = read<int>(), m = read<int>(), min = m, ans = 0;
    m += 200000;

    for (int i = 1; i <= n; i++) {
        char op;
        int x;
        std::cin >> op;
        x = read<int>();
        if (op == 'I') {
            if (x < min) {
                continue;
            }
            mod(1, 0, MAX_N - 1, x - b + 200000, 1);
        }
        if (op == 'A') {
            m -= x;
            b += x;
        }
        if (op == 'S') {
            m += x;
            b -= x;
            if (m >= 1 and sum(1, 0, MAX_N - 1, 0, m - 1) > 0) {
                ans += sum(1, 0, MAX_N - 1, 0, m - 1);
                clear(1, 0, MAX_N - 1, 0, m - 1);
            }
        }
        if (op == 'F') {
            if (x > sum(1, 1, MAX_N - 1, m, MAX_N - 1)) {
                std::cout << -1 << '\n';
            } else {
                std::cout << query(1, 0, MAX_N - 1, x) + b - 200000 << '\n';
            }
        }
    }
    std::cout << ans << '\n';

    return 0;
}

void update(int x) { tree[x] = tree[x * 2] + tree[x * 2 + 1]; }

void mod(int x, int l, int r, int k, int v) {
    if (l == r) {
        tree[x] += v;
        return;
    }
    int mid = (l + r) / 2;
    if (k <= mid) {
        mod(x * 2, l, mid, k, v);
    } else {
        mod(x * 2 + 1, mid + 1, r, k, v);
    }
    update(x);
}

int sum(int k, int l, int r, int x, int y) {
    if (x <= l and r <= y) {
        return tree[k];
    }
    int mid = (l + r) / 2, res = 0;
    if (x <= mid) {
        res += sum(k * 2, l, mid, x, y);
    }
    if (mid < y) {
        res += sum(k * 2 + 1, mid + 1, r, x, y);
    }
    return res;
}

int query(int x, int l, int r, int k) {
    if (l == r) {
        return l;
    }
    int mid = (l + r) / 2;
    int ll = -1, rr = -1;

    if (m < l) {
        ll = tree[x * 2];
    } else if (l <= m and m <= mid) {
        ll = sum(x * 2, l, mid, m, mid);
    } else if (mid < m and m <= r) {
        rr = sum(x * 2 + 1, mid + 1, r, m, r);
    } else {
        rr = tree[x * 2 + 1];
    }

    if (rr == -1) {
        rr = tree[x] - ll;
    }
    ll = tree[x] - rr;

    if (rr >= k) {
        return query(x * 2 + 1, mid + 1, r, k);
    } else {
        return query(x * 2, l, mid, k - rr);
    }
}

void clear(int x, int l, int r, int u, int v) {
    if (l == r) {
        tree[x] = 0;
        return;
    } else {
        int mid = (l + r) / 2;
        if (u <= mid and tree[x * 2]) {
            clear(x * 2, l, mid, u, v);
        }
        if (mid < v and tree[x * 2 + 1]) {
            clear(x * 2 + 1, mid + 1, r, u, v);
        }
        update(x);
    }
}

template <typename T>
T read() {
    T x = 0, f = 1;
    char ch = getchar();
    while (!isdigit(ch)) {
        if (x == '-') f = -1;
        ch = getchar();
    }
    while (isdigit(ch)) {
        x = x * 10 + ch - 48;
        ch = getchar();
    }
    return x * f;
}