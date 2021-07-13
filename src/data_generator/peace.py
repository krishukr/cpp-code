from cyaron import *

for i in range(0, 20):
    io = IO(file_prefix="peace", data_id=i + 1)

    n = randint(1000, 100000)

    io.input_writeln(n)

    # Compare.program("../../bin/peace", input=io, std_program="../../bin/xu")
    io.output_gen("../../bin/peace")
