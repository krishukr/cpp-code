#include <cstdio>
#include <iostream>
#include <queue>
#include <vector>

constexpr int MAX_N = 100050;

struct P {
    int l;
    int r;
    int v;
} p[MAX_N];

int a[MAX_N];
bool vis[MAX_N];

std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                    std::greater<std::pair<int, int>>>
    q;

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n, k;
    read(n, k);
    for (int i = 1; i <= n; i++) {
        read(a[i]);
    }
    for (int i = 1; i < n; i++) {
        p[i] = {i - 1, i + 1, a[i + 1] - a[i]};
        q.push({p[i].v, i});
    }
    p[0].v = p[n].v = 0x3f3f3f3f;

    int ans{0};
    for (int i = 1; i <= k; i++) {
        while (vis[q.top().second]) {
            q.pop();
        }
        const auto o = q.top();
        q.pop();
        const auto idx = o.second;

        ans += o.first;
        vis[p[idx].l] = vis[p[idx].r] = true;
        p[idx].v = p[p[idx].l].v + p[p[idx].r].v - p[idx].v;
        q.push({p[idx].v, idx});

        p[idx].l = p[p[idx].l].l;
        p[idx].r = p[p[idx].r].r;
        p[p[idx].l].r = idx;
        p[p[idx].r].l = idx;
    }
    std::cout << ans << '\n';

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

template <typename T>
void read(T& t) {
    t = read<T>();
}

template <typename T, typename... Args>
void read(T& t, Args&... rest) {
    t = read<T>();
    read(rest...);
}