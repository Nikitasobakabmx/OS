#ifndef CALCULATIONGRAPH_H
#define CALCULATIONGRAPH_H

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

struct Edge {
    Edge(const std::string &inNodeName,const std::string &inEndgeName)
        : nodeName(inNodeName),
          name(inEndgeName)
    {}

    std::string nodeName;
    std::string name;
};


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

}


class CalculationGraph {
public:
    CalculationGraph& connect(Node::Pointer from, Node::Pointer to,const std::string &edgeName) {
        if (from != nullptr && to != nullptr ) {
            const auto fromName = from->name();
            const auto toName = to->name();

            const auto edge = Edge(toName, edgeName);
            m_adjacencyList[fromName].push_back(edge);
        }
        return *this;
    }

    Node::Pointer getNode(const std::string &name) {
        if (m_nodes.find(name) != m_nodes.end()) {
            return m_nodes[name];
        }

        return nullptr;
    }

    std::vector<Edge> getEdges(const Node::Pointer &node) {
        if (node == nullptr) {
            return {};
        }

        const auto ndoeName = node->name();

        if (m_adjacencyList.find(ndoeName) != m_adjacencyList.end()) {
            return  m_adjacencyList[ndoeName];
        }

        return {};
    }

     Node::Pointer create(const std::string &name) {
        const auto node = std::make_shared<Node>(name);

        m_nodes[name] = node;

        return node;
    }

private:


    std::unordered_map<std::string, std::vector<Edge>> m_adjacencyList;
    std::unordered_map<std::string, Node::Pointer> m_nodes;
};
















#endif // CALCULATIONGRAPH_H
