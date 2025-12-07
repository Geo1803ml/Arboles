#include "Tree.hpp"
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <memory> 

using json = nlohmann::json;

// --- Función auxiliar recursiva ---
static std::shared_ptr<Node> json_to_node(const json& j) {
    // 1. Crear el nodo
    auto n = std::make_shared<Node>();

    // 2. Cargar datos básicos
    n->id = j.at("id").get<int>();
    n->name = j.at("name").get<std::string>();

    // 3. Convertir string a Enum
    std::string typeStr = j.at("type").get<std::string>();
    n->type = (typeStr == "folder") ? NodeType::FOLDER : NodeType::FILE;

    // 4. Cargar contenido opcional
    if (!j.at("content").is_null()) {
        n->content = j.at("content").get<std::string>();
    } else {
        n->content = std::nullopt;
    }

    // 5. Recursividad + ENLACE DE PADRES (¡Muy importante!)
    if (j.contains("children")) {
        for (const auto& child_json : j["children"]) {
            // Convertir el hijo
            std::shared_ptr<Node> child = json_to_node(child_json);
            
            // CRUCIAL: Asignar el padre (weak_ptr se asigna desde shared_ptr)
            child->parent = n; 
            
            // Agregarlo a la lista de hijos
            n->children.push_back(child);
        }
    }

    return n;
}

// --- Tu función principal ---
bool Tree::load_from_file(const std::string& filename) {
    std::ifstream f(filename);
    if (!f.is_open()) return false;

    try {
        json j;
        f >> j; // Parsear JSON

        // 1. Reconstruir la estructura de nodos
        _root = json_to_node(j);
        
        // La raíz no tiene padre
        _root->parent.reset(); 

        // 2. CRUCIAL: Reconstruir el índice del árbol
        // Sin esto, funciones como 'traverse_to' o busquedas rápidas fallarán
        // Asumo que esta función existe porque la vi en tu snippet anterior.
        this->build_index(); 

        return true;
    } catch (const json::parse_error& e) {
        std::cerr << "Error JSON: " << e.what() << std::endl;
        return false;
    }
}