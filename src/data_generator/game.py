from cyaron import *

import os

if __name__ == '__main__':
    # for i in range(7, 20):
    #     io = IO(file_prefix="game", data_id=i)

    #     n = randint(1000, 100001)
    #     m = randint(1, 20)
    #     l = n

    #     io.input_writeln(n, m)

    #     for j in range(1, m + 1):
    #         e = randint(2, 201)
    #         l -= e
    #         io.input_writeln(e)

    # io = IO(file_prefix="game", data_id=20)

    # n = 100000
    # m = 50000

    # io.input_writeln(n, m)

    # for i in range(1, m+1):
    #     io.input_writeln(2)

    # for i in range(1, 21):
    #     io = IO(file_prefix="game", data_id=i)

    #     io.output_gen("../../bin/game")

    # io = IO("./game1.in")

    # io.output_gen("../../bin/game")

    for i in range(1, 21):
        os.system("cp ./game{0}.in ../../bin/game.in".format(i))
        os.system("../../bin/game")
        os.system("cp ../../bin/game.out ./game{0}.out".format(i))
