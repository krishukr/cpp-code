#include <iostream>

const int MAX_N = 1000050;

int fa[MAX_N];
int ans;

void init(int n);

int find(int x);

void merge(int i, int j);

template <typename T>
T read();

int main() {
    freopen("chang.in", "r", stdin);
    freopen("chang.out", "w", stdout);

    int n = read<int>(), m = read<int>();
    init(n);
    for (int i = 1; i <= n; i++) {
        int x = read<int>(), y = read<int>();
    }
    for (int i = 1; i <= m; i++) {
        int x = read<int>(), y = read<int>();
        merge(x, y);
    }
    std::cout << ans << '\n';

    fclose(stdin);
    fclose(stdout);
    return 0;
}

void init(int n) {
    for (int i = 1; i <= n; i++) {
        fa[i] = i;
    }
}

int find(int x) { return x == fa[x] ? x : (fa[x] = find(fa[x])); }

void merge(int i, int j) {
    if (find(i) == find(j)) {
        ans++;
    } else {
        fa[find(i)] = find(j);
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