#include <algorithm>
#include <iostream>
#include <vector>

const int MAX_N = 100050;

int fa[MAX_N];
std::pair<int, int> edge[MAX_N];
int n, m;
std::vector<std::pair<int, int> > ans;

void init();

int find(int x);

void merge(int i, int j);

bool query(int x);

int main() {
    std::ios::sync_with_stdio(false);

    std::cin >> n >> m;
    for (int i = 0; i < m; i++) {
        std::cin >> edge[i].first >> edge[i].second;
        if (edge[i].first > edge[i].second) {
            std::swap(edge[i].first, edge[i].second);
        }
    }
    for (int i = 0; i < m; i++) {
        if (query(i)) {
            ans.push_back(edge[i]);
        }
    }
    std::sort(ans.begin(), ans.end());

    for (std::vector<std::pair<int, int> >::iterator it = ans.begin();
         it != ans.end(); it++) {
        std::cout << (*it).first << ' ' << (*it).second << '\n';
    }

    return 0;
}

void init() {
    for (int i = 1; i <= n; i++) {
        fa[i] = i;
    }
}

int find(int x) { return x == fa[x] ? x : (fa[x] = find(fa[x])); }

void merge(int i, int j) { fa[find(i)] = find(j); }

bool query(int x) {
    init();
    for (int i = 0; i < m; i++) {
        if (i == x) {
            continue;
        }
        merge(edge[i].first, edge[i].second);
    }
    for (int i = 2; i <= n; i++) {
        if (find(1) != find(i)) {
            return true;
        }
    }
    return false;
}