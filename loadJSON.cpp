#include "Tree.hpp"         
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <memory>           

using json = nlohmann::json;

// --- Función auxiliar interna 
static std::shared_ptr<Node> json_to_node(const json& j) {
    // 1. Crear el nodo vacío usando punteros inteligentes
    auto n = std::make_shared<Node>();
    
    // 2. Recuperar ID y Nombre
    n->id = j.at("id").get<int>();
    n->name = j.at("name").get<std::string>();
    
    // 3. Convertir string a Enum (Type)
    // Esto debe coincidir con como Geovanny guardó "folder" o "file"
    std::string typeStr = j.at("type").get<std::string>();
    if (typeStr == "folder") {
        n->type = NodeType::FOLDER;
    } else {
        n->type = NodeType::FILE;
    }

    // 4. Recuperar el contenido (Manejo de opcionales)
    if (!j.at("content").is_null()) {
        n->content = j.at("content").get<std::string>();
    } else {
        n->content = std::nullopt; 
    }

    // 5. Recursividad: Recuperar los hijos
    if (j.contains("children")) {
        for (const auto& child_json : j["children"]) {
            // Llamamos a esta misma función para cada hijo y lo guardamos
            n->children.push_back(json_to_node(child_json));
        }
    }

    return n;
}

// --- Tu función principal del Día 4 ---
bool Tree::load_from_file(const std::string& filename) {
    std::ifstream f(filename);
    if (!f.is_open()) return false;

    try {
        json j;
        f >> j; // Leer todo el JSON

        // Aquí reconstruimos todo el árbol y actualizamos la raíz de la clase
        _root = json_to_node(j);

        return true;
    } catch (const json::parse_error& e) {
        std::cerr << "Error al parsear JSON: " << e.what() << std::endl;
        return false;
    }
}