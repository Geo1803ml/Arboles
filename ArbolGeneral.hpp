#pragma once
#include <string>
#include <vector>
#include <memory>
#include <optional>
#include "Trie.hpp"

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

class ArbolGeneral {
private:
    std::shared_ptr<Node> root;
    std::shared_ptr<Node> currentDir; //  Puntero a la carpeta actual

    // Auxiliares
    std::shared_ptr<Node> findNodeRecursive(std::shared_ptr<Node> current, const std::string& targetId);
    bool isDescendant(std::shared_ptr<Node> current, std::shared_ptr<Node> target);
    void populateTrieRecursive(std::shared_ptr<Node> current, Trie& trie);

public:
    ArbolGeneral();
    
    // Persistencia (Día 4)
    bool load_from_file(const std::string& filename);
    bool save_to_file(const std::string& filename) const;

    // Movimiento (Día 3)
    void moveNode(const std::string& idNode, const std::string& idDestParent);

    // Trie (Día 5 y 6)
    void loadNamesIntoTrie(Trie& trieObject);
    void autocompleteConsole(Trie& trieObject, const std::string& prefix);

    // --- TAREAS DÍA 7 (MENÚ BÁSICO) ---
    void ls(); // Listar directorio actual
    void mkdir(const std::string& name, Trie& trie); // Crear carpeta
    void touch(const std::string& name, Trie& trie); //  Crear archivo
    void cd(const std::string& name); // Entrar a carpeta

    //  DÍA 8
    
    // Cambiar nombre a un archivo/carpeta del directorio actual
    void rename(const std::string& oldName, const std::string& newName, Trie& trie);

    // Mover un nodo (por nombre) a otro destino (por nombre)
    void move_by_name(const std::string& nameToMove, const std::string& nameDestFolder);

    // DÍA 9 
    // Comando formal para buscar archivos usando el Trie
    void search(const std::string& prefix, Trie& trie);

    //DÍA 10PRUEBA DE RENDIMIENTO 
    // Genera 500 nodos y mide el tiempo de respuesta
    void runPerformanceTest(Trie& trie);

    // DÍA 11 VALIDACIÓN Y CONSISTENCIA 
    
    // Permite navegar rutas complejas (ej: "documentos/tarea/final")
    // Retorna el nodo si existe, o nullptr si la ruta es inválida.
    std::shared_ptr<Node> getNodeFromPath(const std::string& path);

    // Revisa la salud del árbol (verifica que los hijos apunten correctamente a sus padres)
    void checkIntegrity();
    
    // Getter del nombre actual para el prompt (ej: root/> )
    std::string getCurrentPathName();
};