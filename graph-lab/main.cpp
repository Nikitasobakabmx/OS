#include <iostream>

#include "Run.h"
#include "CalculationGraph.h"

int main()
{
    CalculationGraph graph;

    auto root  = graph.create("root");
    auto node1 = graph.create("1");
    auto node2 = graph.create("2");
    auto node3 = graph.create("3");
    auto node4 = graph.create("4");
    auto node5 = graph.create("5");
    auto node6 = graph.create("6");
    auto node7 = graph.create("7");
    auto node8 = graph.create("8");
    auto node9 = graph.create("9");

    graph.connect(root, node1, "a")
         .connect(root, node2, "c")
         .connect(root, node3, "d")
         .connect(root, node4, "e")
            
         .connect(node1, node2, "b")
         .connect(node2, node4, "g")
         .connect(node2, node5, "h")

         .connect(node3, node4, "f")
         .connect(node4, node5, "i")
         .connect(node4, node5, "k")

         .connect(node5, node6, "m");

     run(graph, root);

    return 0;
}
