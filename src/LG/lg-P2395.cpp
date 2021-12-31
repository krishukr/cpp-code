#include <cstdio>
#include <cstring>
#include <iostream>
#include <stack>

enum BBC { BB_h1, BB_h2, BB_i, BB_b, BB_url, BB_img, BB_quote };

std::string out;
std::stack<BBC> cmd;
std::stack<std::string> txt;

void check(BBC val);

int main() {
    std::ios::sync_with_stdio(false);

    char ch = getchar();
    while (ch != EOF) {
        if (ch == '[') {
            std::string c = "";
            ch = getchar();
            while (ch != ']') {
                c.push_back(ch);
                ch = getchar();
            }

            bool is_ed = (c[0] == '/');
            if (is_ed) {
                c = c.substr(1);
            }

            if (c == "h1") {
                if (is_ed) {
                    check(BB_h1);
                    out.append(" #");
                } else {
                    out.append("# ");
                    cmd.push(BB_h1);
                }
            } else if (c == "h2") {
                if (is_ed) {
                    check(BB_h2);
                    out.append(" ##");
                } else {
                    out.append("## ");
                    cmd.push(BB_h2);
                }
            } else if (c == "i") {
                if (is_ed) {
                    check(BB_i);
                    out.append("*");
                } else {
                    out.append("*");
                    cmd.push(BB_i);
                }
            } else if (c == "b") {
                if (is_ed) {
                    check(BB_b);
                    out.append("__");
                } else {
                    out.append("__");
                    cmd.push(BB_b);
                }
            } else if (c.substr(0, 3) == "url") {
                if (is_ed) {
                    check(BB_url);
                    out.append("](" + txt.top() + ")");
                    txt.pop();
                } else {
                    txt.push(c.substr(4));
                    out.append("[");
                    cmd.push(BB_url);
                }
            } else if (c.substr(0, 3) == "img") {
                if (is_ed) {
                    check(BB_img);
                    out.append("](" + txt.top() + ")");
                    txt.pop();
                } else {
                    txt.push(c.substr(4));
                    out.append("![");
                    cmd.push(BB_img);
                }
            } else if (c == "quote") {
                char t = getchar();
                while (t == '\n') {
                    t = getchar();
                }
                std::string buf = "";

                while (t != EOF) {
                    buf.push_back(t);
                    if (buf.size() >= 8 and
                        buf.substr(buf.size() - 8) == "[/quote]") {
                        break;
                    }
                    t = getchar();
                }

                if (t == EOF) {
                    std::cout << "Match Error\n";
                    std::exit(0);
                }

                buf = buf.substr(0, buf.size() - 8);
                while (buf.back() == '\n') {
                    buf.pop_back();
                }

                if (out.back() != '\n') {
                    out.push_back('\n');
                }

                out.append("> ");
                for (auto i : buf) {
                    out.push_back(i);
                    if (i == '\n') {
                        out.append("> ");
                    }
                }
                out.push_back('\n');
            }
        } else {
            out.push_back(ch);
        }
        ch = getchar();
    };

    if (!cmd.empty()) {
        std::cout << "Unclosed Mark\n";
        return 0;
    }

    std::cout << out;

    return 0;
}

void check(BBC val) {
    if (cmd.empty() or cmd.top() != val) {
        std::cout << "Match Error\n";
        std::exit(0);
    }
    cmd.pop();
}