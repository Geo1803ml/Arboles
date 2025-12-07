#include "Tree.hpp"
#include <algorithm>

bool Tree::remove_at_path(const std::string& path) {
    auto node = traverse_to(path);
    if (!node || node == _root) return false;

    auto parent = node->parent.lock();
    if (!parent) return false;

    // eliminar del padre
    auto& vec = parent->children;
    vec.erase(std::remove_if(vec.begin(), vec.end(),
        [&](const std::shared_ptr<Node>& n) { return n->id == node->id; }),
        vec.end());

    // mover a papelera
    trash.push_back(node);

    node->parent.reset();
    build_index();
    return true;
}
