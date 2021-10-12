#include <cstdio>
#include <cstring>
#include <iostream>

typedef long long ll;

ll ans;

class Star {
   private:
    const static int MAX_N = 4000050;

   public:
    struct Node {
        int v;
        int nxt;
    } node[MAX_N];

    int cnt;
    int head[MAX_N], siz[MAX_N];

    void create(int u, int v) {
        node[++cnt].v = v;
        node[cnt].nxt = head[u];
        head[u] = cnt;
    }
} star;

class SAM {
   private:
    const static int CHA_SIZE = 26;
    const static int MAX_N = 4000050;

    int siz;
    int lst;

    struct Node {
        int len;
        int lnk;
        int nxt[CHA_SIZE];
    } node[MAX_N];

   public:
    SAM() {
        node[siz++] = (Node){0, -1};
        lst = 0;
    }

    void insert(const char& c) {
        int crt = siz++;
        node[crt].len = node[lst].len + 1;
        star.siz[crt] = 1;

        int p = lst;
        while (p != -1 and !node[p].nxt[c]) {
            node[p].nxt[c] = crt;
            p = node[p].lnk;
        }

        if (p == -1) {
            node[crt].lnk = 0;
        } else {
            int q = node[p].nxt[c];
            if (node[p].len + 1 == node[q].len) {
                node[crt].lnk = q;
            } else {
                int cpy = siz++;
                node[cpy] = (Node){node[p].len + 1, node[q].lnk};
                for (int i = 0; i < CHA_SIZE; i++) {
                    node[cpy].nxt[i] = node[q].nxt[i];
                }

                while (p != -1 and node[p].nxt[c] == q) {
                    node[p].nxt[c] = cpy;
                    p = node[p].lnk;
                }
                node[q].lnk = node[crt].lnk = cpy;
            }
        }

        lst = crt;
    }

    void trans() {
        for (int i = 1; i < siz; i++) {
            star.create(node[i].lnk, i);
        }
    }

    void dfs(int x) {
        for (int i = star.head[x]; i; i = star.node[i].nxt) {
            int v = star.node[i].v;
            dfs(v);
            star.siz[x] += star.siz[v];
        }

        if (star.siz[x] != 1) {
            ans = std::max(ans, (ll)(star.siz[x] * node[x].len));
        }
    }
};

int main() {
    std::ios::sync_with_stdio(false);

    SAM* sam = new SAM();

    std::string s;
    std::cin >> s;
    for (auto i : s) {
        sam->insert(i - 'a');
    }

    sam->trans();
    sam->dfs(0);

    std::cout << ans << '\n';

    delete sam;
    return 0;
}
