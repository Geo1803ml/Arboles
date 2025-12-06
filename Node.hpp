#pragma once
#include <string>
#include <vector>
#include <memory>
#include <optional>

enum class NodeType { FOLDER, FILE };

struct Node {
    std::string id;
    std::string name;
    NodeType type;
    std::optional<std::string> content;
    std::vector<std::shared_ptr<Node>> children;
    std::weak_ptr<Node> parent;

    Node(const std::string& _id, const std::string& _name, NodeType _type)
        : id(_id), name(_name), type(_type), content(std::nullopt) {}
};
