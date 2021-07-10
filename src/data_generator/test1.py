from cyaron import *

for i in range(0, 10):
    io = IO(file_prefix="a", data_id=i + 1)

    n = randint(2, 1001)
    m = randint(1, 2001)

    io.input_writeln(n, m)

    graph = Graph.graph(n, m)

    io.input_writeln(graph.to_str(output=Edge.unweighted_edge, shuffle=True))

    io.output_gen("../../bin/a")
