// ArbolGeneral.hpp
#pragma once
#include <string>
#include <vector>
#include <memory>   // Para shared_ptr
#include <optional> // Para optional

// 1. EL NODO MODERNO (El que me pasaste último)
enum class NodeType { FOLDER, FILE };

struct Node {
    std::string id;
    std::string name;
    NodeType type;
    std::optional<std::string> content;
    std::vector<std::shared_ptr<Node>> children;
    std::weak_ptr<Node> parent; // Importante para mover nodos

    Node(const std::string& _id, const std::string& _name, NodeType _type)
        : id(_id), name(_name), type(_type), content(std::nullopt) {}
};

// 2 CLASE PRINCIPA
class Tree {
private:
    std::shared_ptr<Node> root;

    // Métodos privados auxiliares
    std::shared_ptr<Node> findNodeRecursive(std::shared_ptr<Node> current, const std::string& targetId);
    bool isDescendant(std::shared_ptr<Node> current, std::shared_ptr<Node> target);
    
    // Auxiliar para JSON (se implementa en el cpp)
    // No necesitas declararla aquí si la haces estática en el cpp, 
    // pero si la haces método de clase, ponla aquí.

public:
    Tree(); 

    // Tarea Día 4: Cargar y Guardar
    bool load_from_file(const std::string& filename);
    bool save_to_file(const std::string& filename) const;

    // Tarea Día 3: Mover
    void moveNode(const std::string& idNode, const std::string& idDestParent);

   
};