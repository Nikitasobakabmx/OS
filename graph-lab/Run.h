#ifndef RUN_H
#define RUN_H


#include "CalculationGraph.h"

#include <queue>
#include <iostream>

void thread(const std::string &s) {
    std::cout << s;
}


void run( CalculationGraph &graph, Node::Pointer &root) {

    std::queue<Edge> queue;

    for (auto & edge:graph.getEdges(root)) {
        queue.push(edge);
    }


    while (!queue.empty()) {
        const auto edge = queue.front();

        queue.pop();

        thread(edge.name);

        auto node = graph.getNode(edge.nodeName);
        for (auto & edge : graph.getEdges(node)) {
            queue.push(edge);
        }
    }

    std::cout << std::endl;


}












#endif // RUN_H
