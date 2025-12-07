#include "ArbolGeneral.hpp"
#include "Trie.hpp"      // Necesario para el Día 5
#include "json.hpp"      // Necesario para el Día 4
#include <iostream>
#include <fstream>
#include <algorithm>

using json = nlohmann::json;
using namespace std;

// ==========================================
// SECCIÓN: MÉTODOS PRIVADOS (AYUDANTES)
// ==========================================

// Ayudante 1: Buscar nodo por ID recursivamente
shared_ptr<Node> Tree::findNodeRecursive(shared_ptr<Node> current, const string& targetId) {
    if (!current) return nullptr;
    if (current->id == targetId) return current;

    for (auto& child : current->children) {
        auto result = findNodeRecursive(child, targetId);
        if (result) return result;
    }
    return nullptr;
}

// Ayudante 2: Detectar ciclos (Para mover nodos de forma segura)
bool Tree::isDescendant(shared_ptr<Node> current, shared_ptr<Node> target) {
    if (!current || !target) return false;
    if (current == target) return true;

    for (auto& child : current->children) {
        if (isDescendant(child, target)) return true;
    }
    return false;
}

// Ayudante 3: Recursividad para llenar el Trie (Día 5)
void Tree::populateTrieRecursive(shared_ptr<Node> current, Trie& trie) {
    if (!current) return;
    
    // Insertamos el nombre en el Trie
    trie.insert(current->name);

    // Seguimos con los hijos
    for (const auto& child : current->children) {
        populateTrieRecursive(child, trie);
    }
}

// Ayudante 4: Función estática para convertir JSON a Nodo (Día 4)
// (Esta función no pertenece a la clase, es una utilidad local del archivo)
static shared_ptr<Node> jsonToNode(const json& j) {
    // 1. ID y Nombre
    string idStr = j["id"].is_number() ? to_string(j["id"].get<int>()) : j["id"].get<string>();
    string nameStr = j.value("name", "SinNombre");

    // 2. Tipo
    string typeStr = j.value("type", "file");
    NodeType typeEnum = (typeStr == "folder") ? NodeType::FOLDER : NodeType::FILE;

    // 3. Crear Nodo
    auto newNode = make_shared<Node>(idStr, nameStr, typeEnum);

    // 4. Contenido
    if (j.contains("content") && !j["content"].is_null()) {
        newNode->content = j["content"].get<string>();
    }

    // 5. Hijos
    if (j.contains("children")) {
        for (const auto& childJson : j["children"]) {
            auto childNode = jsonToNode(childJson);
            childNode->parent = newNode; // ¡Importante! Conectar padre
            newNode->children.push_back(childNode);
        }
    }
    return newNode;
}

// Ayudante 5: Inverso (Nodo -> JSON) para el Save de Geovanny
static json nodeToJson(const shared_ptr<Node>& n) {
    json j;
    j["id"] = n->id;
    j["name"] = n->name;
    j["type"] = (n->type == NodeType::FOLDER ? "folder" : "file");
    j["content"] = n->content.has_value() ? n->content.value() : nullptr;

    for (auto& c : n->children)
        j["children"].push_back(nodeToJson(c));

    return j;
}

// ==========================================
// SECCIÓN: MÉTODOS PÚBLICOS
// ==========================================

Tree::Tree() : root(nullptr) {}

// --- TAREA DÍA 4 (EDUARDO): CARGAR ---
bool Tree::load_from_file(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: No se pudo abrir " << filename << endl;
        return false;
    }
    try {
        json j;
        file >> j;
        root = jsonToNode(j);
        root->parent.reset(); // La raíz no tiene padre
        return true;
    } catch (const exception& e) {
        cerr << "Error JSON: " << e.what() << endl;
        return false;
    }
}

// --- TAREA DÍA 4 (GEOVANNY): GUARDAR ---
bool Tree::save_to_file(const string& filename) const {
    if (!root) return false;
    json j = nodeToJson(root);
    ofstream f(filename);
    if (!f.is_open()) return false;
    f << j.dump(4);
    return true;
}

// --- TAREA DÍA 3 (EDUARDO): MOVER ---
void Tree::moveNode(const string& idNode, const string& idDestParent) {
    if (!root) return;

    auto nodeToMove = findNodeRecursive(root, idNode);
    auto newParent = findNodeRecursive(root, idDestParent);

    // Validaciones
    if (!nodeToMove || !newParent) {
        cout << "Error: Nodo o destino no encontrado.\n"; return;
    }
    if (nodeToMove == root) {
        cout << "Error: No se puede mover la raiz.\n"; return;
    }
    if (newParent->type != NodeType::FOLDER) {
        cout << "Error: El destino debe ser carpeta.\n"; return;
    }
    if (isDescendant(nodeToMove, newParent)) {
        cout << "Error: Ciclo detectado (Mover carpeta dentro de si misma).\n"; return;
    }

    // 1. Cortar
    if (auto oldParent = nodeToMove->parent.lock()) {
        auto& sibs = oldParent->children;
        sibs.erase(remove(sibs.begin(), sibs.end(), nodeToMove), sibs.end());
    }

    // 2. Pegar
    newParent->children.push_back(nodeToMove);
    nodeToMove->parent = newParent;
    cout << "Movido exitosamente.\n";
}

// --- TAREA DÍA 5 (EDUARDO): CARGAR AL TRIE ---
void Tree::loadNamesIntoTrie(Trie& trieObject) {
    if (!root) return;
    populateTrieRecursive(root, trieObject);
    cout << "Nombres cargados al Trie.\n";
}