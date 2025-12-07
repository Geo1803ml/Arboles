#include "Tree.hpp"
#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;

static json node_to_json(const std::shared_ptr<Node>& n) {
    json j;
    j["id"] = n->id;
    j["name"] = n->name;
    j["type"] = (n->type == NodeType::FOLDER ? "folder" : "file");
    j["content"] = n->content.has_value() ? n->content.value() : nullptr;

    for (auto& c : n->children)
        j["children"].push_back(node_to_json(c));

    return j;
}

bool Tree::save_to_file(const std::string& filename) const {
    json j = node_to_json(_root);
    std::ofstream f(filename);
    if (!f.is_open()) return false;
    f << j.dump(4);
    return true;
}
