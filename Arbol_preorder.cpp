#include "Tree.hpp"

void Tree::preorder_collect(const std::shared_ptr<Node>& node, std::string& out, int depth) const {
    out.append(std::string(depth * 2, ' '));
    out.append(node->name + "\n");

    for (auto& c : node->children)
        preorder_collect(c, out, depth + 1);
}

std::string Tree::export_preorder() const {
    std::string out;
    preorder_collect(_root, out);
    return out;
}
