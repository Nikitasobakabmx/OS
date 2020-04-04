#ifndef CALCULATIONGRAPH_H
#define CALCULATIONGRAPH_H

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

class Node {
public:
    using Pointer = std::shared_ptr<Node>;

    Node(const std::string &name)
        : m_name(name) {

    }

    std::string name() const {
        return m_name;
    }

    // some
private:
    std::string m_name;
};

namespace NodeFactory {
    static Node::Pointer create(const std::string &name) {
        return std::make_shared<Node>(name);
    }
}


class CalculationGraph {
public:
    CalculationGraph& conncet(Node::Pointer from, Node::Pointer to) {
        if (from != nullptr && to != nullptr ) {
            const auto fromName = from->name();
            const auto toName = to->name();

            m_adjacencyList[fromName].push_back(toName);
        }
        return *this;
    }

    Node::Pointer getNode(const std::string &name) {
        if (m_nodes.find(name) != m_nodes.end()) {
            return m_nodes[name];
        }

        return nullptr;
    }
private:


    std::unordered_map<std::string, std::vector<std::string>> m_adjacencyList;
    std::unordered_map<std::string, Node::Pointer> m_nodes;
};
















#endif // CALCULATIONGRAPH_H
