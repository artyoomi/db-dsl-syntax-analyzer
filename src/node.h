#pragma once

#include <format>
#include <fstream>
#include <iostream>
#include <magic_enum/magic_enum.hpp>
#include <memory>
#include <optional>
#include <queue>
#include <stdexcept>
#include <string>
#include <vector>

namespace ast {

struct Node;

using NodePtr = std::shared_ptr<Node>;

enum class NodeType : uint8_t {
    // Request types
    GET_REQUEST,
    ADD_REQUEST,
    CHANGE_TO_REQUEST,
    DELETE_REQUEST,

    // Conditions
    CONDITION,
    AND,
    OR,
    EQUAL,
    NEQUAL,

    // Assignments
    ASSIGNMENT,
    ASSIGN_OP,

    // Leaves with identifiers and values
    TOKEN
};

// Factory function that forwards arguments to the appropriate constructor
template <typename... Args>
auto makeNodePtr(Args&&... args) -> NodePtr
{
    return std::make_shared<Node>(std::forward<Args>(args)...);
}

struct Node {
    unsigned                   id;
    NodeType                   type;
    std::optional<std::string> token;
    std::vector<NodePtr>       children;

    Node() = delete;
    Node(const Node& other) = delete;
    Node(Node&& other) = delete;

    explicit Node(NodeType type) : id{Node::generateId()}, type{type}, token{std::nullopt} {}

    explicit Node(NodeType type, const std::string& token)
        : id{Node::generateId()}, type{type}, token{token}
    {
    }

    // Generates and assigns unique id for each new node
    static auto generateId() -> unsigned
    {
        static unsigned id = 0;
        return ++id;
    }
};

/** Format of resulting .dot file is as follows
    ```
    digraph AST {
        node0 [label="EQUAL"];
        node1 [label="TOKEN: typing"];
        node2 [label="TOKEN: abc"];

        node0 -> node1;
        node0 -> node2;
    }
    ```
 */
void dumpToGraphviz(const std::string& filename, const NodePtr& node);

}  // namespace ast
