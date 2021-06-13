#include <cstring>
#include <iostream>
#include <queue>

const int MAX_N = 100010;

int tree[MAX_N][27], exi[MAX_N], nxt[MAX_N], ans[MAX_N];
int tot;
std::string s[MAX_N];

void build();

void insert(std::string s, int c);

void query(std::string s);

int main() {
    std::ios::sync_with_stdio(false);

    int n;
    while (std::cin >> n) {
        if (n == 0) {
            break;
        }

        memset(tree, 0, sizeof(tree));
        memset(exi, 0, sizeof(exi));
        memset(nxt, 0, sizeof(nxt));
        memset(ans, 0, sizeof(ans));
        tot = 0;

        for (int i = 0; i < n; i++) {
            std::cin >> s[i];
            insert(s[i], i + 1);
        }
        build();

        std::string k;
        std::cin >> k;
        query(k);

        int tmp = 0;
        for (int i = 1; i <= n; i++) {
            tmp = std::max(tmp, ans[i]);
        }
        std::cout << tmp << '\n';
        for (int i = 1; i <= n; i++) {
            if (ans[i] == tmp) {
                std::cout << s[i - 1] << '\n';
            }
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
        int ch = s[i] - 'a';
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
        int ch = s[i] - 'a';
        x = tree[x][ch];
        for (int j = x; j; j = nxt[j]) {
            ans[exi[j]]++;
        }
    }
}
