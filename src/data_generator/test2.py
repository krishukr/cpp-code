from cyaron import *

for i in range(0, 10):
    io = IO(file_prefix="dilute", data_id=i + 1)

    s = String.random((3, 25))

    io.input_writeln(s)

    # Compare.program("../../bin/yuan", input=io, std_program="../../bin/dilute")
    io.output_gen("../../bin/dilute")
