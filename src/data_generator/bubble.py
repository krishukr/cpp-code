from cyaron import *

if __name__ == '__main__':
    for i in range(1, 11):
        io = IO()
        io.input_writeln(i)

        Compare.program("../../bin/bubble",
                        std_program="../../bin/yuan", input=io)
