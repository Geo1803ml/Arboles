#include "Tree.hpp"

std::optional<std::string> Tree::get_full_path(std::shared_ptr<Node> node) const {
    if (!node) return std::nullopt;

    std::string path = node->name;
    auto p = node->parent.lock();

    while (p) {
        if (p->name != "/")
            path = p->name + "/" + path;
        p = p->parent.lock();
    }
    return "/" + path;
}
