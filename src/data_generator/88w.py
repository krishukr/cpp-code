b = ["个", "十", "百", "千", "万"]

if __name__ == '__main__':
    file = open("./88w.cpp", "w+")

    file.writelines([
        "#include <iostream>\n\n",
        "using namespace std;\n\n",
        "int main() {\n",
        "   int x;\n",
        "   cin >> x;\n\n",
        "   switch (x) {\n"
    ])

    for i in range(1, 100000):
        file.write("    case {0}:\n".format(i))

        d = str(i)
        n = len(d)
        file.write("        cout << \"是{0}位数\" << endl;\n".format(n))

        for j in range(0, n):
            file.write(
                "        cout << \"{0}位数是：{1}\" << endl;\n".format(b[j], d[::-1][j]))

        file.write(
            "        cout << \"倒过来是：{0}\" << endl;\n".format(d[::-1]))
        file.write("        break;\n\n")

    file.writelines([
        "  }",
        "\n",
        "}",
        "\n"
    ])
