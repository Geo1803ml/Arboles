#pragma once

#include <string>
#include <vector>
#include <memory>   // Para std::shared_ptr, std::weak_ptr
#include <optional> // Para std::optional


#include "Trie.hpp"


// 1. ESTRUCTURA DEL NODO (Día 1 y 2)


enum class NodeType { FOLDER, FILE };

struct Node {
    std::string id;
    std::string name;
    NodeType type;
    std::optional<std::string> content;
    
    // Punteros inteligentes (Modern C++)
    std::vector<std::shared_ptr<Node>> children;
    std::weak_ptr<Node> parent; // "weak" para evitar ciclos de memoria

    // Constructor
    Node(const std::string& _id, const std::string& _name, NodeType _type)
        : id(_id), name(_name), type(_type), content(std::nullopt) {}
};


// 2. CLASE ÁRBOL 


class Tree {
private:
    std::shared_ptr<Node> root;

    // --- MÉTODOS PRIVADOS (Auxiliares internos) ---
    
    // Busca un nodo por su ID en todo el árbol
    std::shared_ptr<Node> findNodeRecursive(std::shared_ptr<Node> current, const std::string& targetId);
    
    // Verifica si un nodo es hijo/nieto de otro (para evitar ciclos al mover)
    bool isDescendant(std::shared_ptr<Node> current, std::shared_ptr<Node> target);
    
    // Recorre el árbol para llenar el Trie (Día 5)
    void populateTrieRecursive(std::shared_ptr<Node> current, Trie& trie);

public:
    // Constructor
    Tree();

    // ---  DÍA 4: Cargar y Guardar ---
    bool load_from_file(const std::string& filename);      
    bool save_to_file(const std::string& filename) const;  

    // ---  DÍA 3: Mover nodos ---
    void moveNode(const std::string& idNode, const std::string& idDestParent);

    // ---DÍA 5: Conectar con Trie ---
    void loadNamesIntoTrie(Trie& trieObject);
    
    // Getter para pruebas (opcional)
    std::shared_ptr<Node> getRoot() { return root; }
    // ... dentro de class Tree ... public:

    // DÍA 6 
    void autocompleteConsole(Trie& trieObject, const std::string& prefix);


};