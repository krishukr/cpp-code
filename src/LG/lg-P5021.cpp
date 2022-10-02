#include <cstdio>
#include <iostream>
#include <memory>
#include <set>

constexpr int MAX_N = 50050;
constexpr int MAX_R = MAX_N * 10000;

struct {
    int v;
    int nxt;
    int w;
} node[MAX_N << 1];

int head[MAX_N];
int cnt;

void create(int u, int v, int w);

class Check {
   private:
    int f[MAX_N];
    int ans;

    void dfs(int x, int f);

    int mid;

   public:
    Check() = default;
    ~Check() = default;

    bool check(int mid);
};

int n, m;

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    read(n, m);
    for (int i = 1; i < n; i++) {
        int x, y, z;
        read(x, y, z);
        create(x, y, z);
        create(y, x, z);
    }

    int l{}, r{MAX_R}, a{};
    while (l <= r) {
        auto check = std::make_unique<Check>();
        const auto mid = (l + r) >> 1;
        if (check->check(mid)) {
            a = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    std::cout << a << '\n';

    return 0;
}

void create(int u, int v, int w) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    node[cnt].w = w;
    head[u] = cnt;
}

void Check::dfs(int x, int fa) {
    std::multiset<int> s;
    for (int i = head[x]; i; i = node[i].nxt) {
        const auto v = node[i].v, w = node[i].w;
        if (v == fa) {
            continue;
        }
        dfs(v, x);
        if (f[v] + w >= mid) {
            ans++;
        } else {
            s.insert(f[v] + w);
        }
    }
    while (!s.empty()) {
        auto it = s.begin();
        s.erase(it);
        auto itt = s.lower_bound(mid - *it);
        if (itt == s.end()) {
            f[x] = std::max(f[x], *it);
        } else {
            ans++;
            s.erase(itt);
        }
    }
}

bool Check::check(int mid) {
    this->mid = mid;
    dfs(1, 0);
    return m <= ans;
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