#include <cstring>
#include <iostream>
#include <queue>

const int MAX_N = 700050;
const int MAX_M = 2050;

int tree[MAX_N][35], exi[MAX_N], nxt[MAX_N], ans[MAX_M];
int tot;
std::string s[MAX_M];

int tt[255] = {0,  0,  0,  0, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0,  0,
               0,  0,  0,  0, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0,  0,
               0,  0,  0,  0, 0, 0, 0, 0, 0, 0,  0,  0,  0,  16, 17, 18, 19, 20,
               21, 22, 23, 0, 0, 0, 0, 0, 0, 0,  0,  0,  3,  0,  0,  0,  0,  0,
               0,  0,  0,  1, 0, 0, 4, 0, 6, 2,  5,  0,  0,  0,  0,  0,  0,  0,
               0,  0,  0,  0, 0, 0, 0, 8, 9, 10, 11, 12, 13, 14, 15};

void build();

void insert(std::string s, int c);

void query(std::string s);

int main() {
    std::ios::sync_with_stdio(false);

    int n, m;
    std::cin >> n >> m;

    auto* nam = new std::string[n + 5];
    for (int i = 1; i <= n; i++) {
        int k;
        std::cin >> k;
        std::getline(std::cin, nam[i]);
        std::getline(std::cin, nam[i]);

        for (int j = 1; j <= k; j++) {
            std::string x;
            std::cin >> x;
            s[i] += x;
        }
        insert(s[i], i);
    }
    build();

    std::string k;
    for (int i = 1; i <= m; i++) {
        std::string s;
        std::cin >> s;
        k += s;
    }
    query(k);

    for (int i = 1; i <= n; i++) {
        if (ans[i]) {
            std::cout << nam[i] << '\n';
        }
    }

    return 0;
}

void build() {
    std::queue<int> q;
    for (int i = 0; i < 26; i++) {
        if (tree[0][i]) {
            q.push(tree[0][i]);
        }
    }
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        for (int i = 0; i < 26; i++) {
            if (!tree[x][i]) {
                tree[x][i] = tree[nxt[x]][i];
            } else {
                q.push(tree[x][i]);
                nxt[tree[x][i]] = tree[nxt[x]][i];
            }
        }
    }
}

void insert(std::string s, int c) {
    int x = 0;
    for (int i = 0; s[i]; i++) {
        int ch = tt[s[i]];
        if (!tree[x][ch]) {
            tree[x][ch] = ++tot;
        }
        x = tree[x][ch];
    }
    exi[x] = c;
}

void query(std::string s) {
    int x = 0;
    for (int i = 0; s[i]; i++) {
        int ch = tt[s[i]];
        x = tree[x][ch];
        for (int j = x; j; j = nxt[j]) {
            ans[exi[j]]++;
        }
    }
}