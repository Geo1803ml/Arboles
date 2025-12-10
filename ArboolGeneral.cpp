#include "ArbolGeneral.hpp"
#include "Trie.hpp"
#include "json.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <iomanip> // Para que el 'ls' se vea ordenado

using json = nlohmann::json;
using namespace std;

// ==========================================
// 1. FUNCIONES ESTÁTICAS AUXILIARES (JSON)
// ==========================================
// Estas funciones no pertenecen a la clase, son ayudantes internos para convertir datos.

static shared_ptr<Node> jsonToNode(const json& j) {
    // 1. Recuperar ID y Nombre (Manejo robusto de int/string)
    string idStr = j["id"].is_number() ? to_string(j["id"].get<int>()) : j["id"].get<string>();
    string nameStr = j.value("name", "SinNombre");
    
    // 2. Recuperar Tipo
    string typeStr = j.value("type", "file");
    NodeType typeEnum = (typeStr == "folder") ? NodeType::FOLDER : NodeType::FILE;

    // 3. Crear Nodo
    auto newNode = make_shared<Node>(idStr, nameStr, typeEnum);

    // 4. Recuperar Contenido (si existe)
    if (j.contains("content") && !j["content"].is_null()) {
        newNode->content = j["content"].get<string>();
    }

    // 5. Recursividad para los Hijos
    if (j.contains("children")) {
        for (const auto& childJson : j["children"]) {
            auto childNode = jsonToNode(childJson);
            
            // CRUCIAL: Conectar al padre
            childNode->parent = newNode; 
            
            newNode->children.push_back(childNode);
        }
    }
    return newNode;
}

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
// 2. MÉTODOS PRIVADOS DE LA CLASE
// ==========================================

shared_ptr<Node> ArbolGeneral::findNodeRecursive(shared_ptr<Node> current, const string& targetId) {
    if (!current) return nullptr;
    if (current->id == targetId) return current;

    for (auto& child : current->children) {
        auto result = findNodeRecursive(child, targetId);
        if (result) return result;
    }
    return nullptr;
}

bool ArbolGeneral::isDescendant(shared_ptr<Node> current, shared_ptr<Node> target) {
    if (!current || !target) return false;
    if (current == target) return true;

    for (auto& child : current->children) {
        if (isDescendant(child, target)) return true;
    }
    return false;
}

void ArbolGeneral::populateTrieRecursive(shared_ptr<Node> current, Trie& trie) {
    if (!current) return;
    
    trie.insert(current->name); // Insertar nombre en Trie
    
    for (const auto& child : current->children) {
        populateTrieRecursive(child, trie);
    }
}

// ==========================================
// 3. MÉTODOS PÚBLICOS (IMPLEMENTACIÓN)
// ==========================================

ArbolGeneral::ArbolGeneral() : root(nullptr), currentDir(nullptr) {}

// --- DÍA 4: LOAD & SAVE ---

bool ArbolGeneral::load_from_file(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) return false;

    try {
        json j;
        file >> j;
        
        // 1. Reconstruir árbol
        root = jsonToNode(j);
        root->parent.reset(); // La raíz no tiene padre
        
        // 2. IMPORTANTE: Iniciar el puntero de navegación en la raíz
        currentDir = root; 

        return true;
    } catch (...) {
        return false;
    }
}

bool ArbolGeneral::save_to_file(const string& filename) const {
    if (!root) return false;
    ofstream f(filename);
    if (!f.is_open()) return false;
    f << nodeToJson(root).dump(4);
    return true;
}

// --- DÍA 3: MOVER ---

void ArbolGeneral::moveNode(const string& idNode, const string& idDestParent) {
    if (!root) return;

    auto nodeToMove = findNodeRecursive(root, idNode);
    auto newParent = findNodeRecursive(root, idDestParent);

    if (!nodeToMove || !newParent) {
        cout << "Error: Nodo o destino no existen.\n"; return;
    }
    if (isDescendant(nodeToMove, newParent)) {
        cout << "Error: No puedes mover una carpeta dentro de si misma.\n"; return;
    }

    // Desconectar del padre anterior
    if (auto oldParent = nodeToMove->parent.lock()) {
        auto& sibs = oldParent->children;
        sibs.erase(remove(sibs.begin(), sibs.end(), nodeToMove), sibs.end());
    }

    // Conectar al nuevo padre
    newParent->children.push_back(nodeToMove);
    nodeToMove->parent = newParent;
    cout << "Nodo movido correctamente.\n";
}

// --- DÍA 5 & 6: TRIE ---

void ArbolGeneral::loadNamesIntoTrie(Trie& trieObject) {
    if (!root) return;
    populateTrieRecursive(root, trieObject);
}

void ArbolGeneral::autocompleteConsole(Trie& trieObject, const string& prefix) {
    vector<string> results = trieObject.getWordsStartingWith(prefix);
    
    cout << "\n>>> Sugerencias para: '" << prefix << "' <<<\n";
    if (results.empty()) {
        cout << "   (Sin resultados)\n";
    } else {
        for (const string& w : results) cout << "   -> " << w << endl;
    }
    cout << "-----------------------\n";
}

// --- DÍA 7: COMANDOS DE CONSOLA (LS, MKDIR, TOUCH, CD) ---

void ArbolGeneral::ls() {
    if (!currentDir) {
        cout << "Error: No hay directorio actual seleccionado.\n";
        return;
    }

    if (currentDir->children.empty()) {
        cout << "   (Carpeta vacia)\n";
        return;
    }

    // Encabezados de tabla
    cout << left << setw(20) << "NOMBRE" << setw(10) << "TIPO" << "ID" << endl;
    cout << string(40, '-') << endl;

    for (const auto& child : currentDir->children) {
        string tipo = (child->type == NodeType::FOLDER) ? "<DIR>" : "<FILE>";
        cout << left << setw(20) << child->name 
             << setw(10) << tipo 
             << child->id << endl;
    }
}

void ArbolGeneral::mkdir(const string& name, Trie& trie) {
    if (!currentDir) return;

    // Verificar duplicados
    for (const auto& child : currentDir->children) {
        if (child->name == name) {
            cout << "Error: Ya existe '" << name << "' aqui.\n";
            return;
        }
    }

    string newId = currentDir->id + "_" + name; // Generar ID único simple
    auto newNode = make_shared<Node>(newId, name, NodeType::FOLDER);
    newNode->parent = currentDir;
    
    currentDir->children.push_back(newNode);
    trie.insert(name); // Actualizar Trie
    cout << "Directorio creado: " << name << endl;
}

void ArbolGeneral::touch(const string& name, Trie& trie) {
    if (!currentDir) return;

    for (const auto& child : currentDir->children) {
        if (child->name == name) {
            cout << "Error: Ya existe '" << name << "' aqui.\n";
            return;
        }
    }

    string newId = currentDir->id + "_" + name;
    auto newNode = make_shared<Node>(newId, name, NodeType::FILE);
    newNode->content = ""; // Archivo vacío
    newNode->parent = currentDir;
    
    currentDir->children.push_back(newNode);
    trie.insert(name); // Actualizar Trie
    cout << "Archivo creado: " << name << endl;
}

void ArbolGeneral::cd(const string& name) {
    if (!currentDir) return;

    // Caso especial: Ir hacia atrás
    if (name == "..") {
        if (auto p = currentDir->parent.lock()) {
            currentDir = p;
        } else {
            cout << "Ya estas en la raiz.\n";
        }
        return;
    }

    // Buscar carpeta en los hijos
    for (const auto& child : currentDir->children) {
        if (child->name == name) {
            if (child->type == NodeType::FOLDER) {
                currentDir = child;
            } else {
                cout << "Error: '" << name << "' es un archivo, no una carpeta.\n";
            }
            return;
        }
    }
    cout << "Error: No se encontro el directorio '" << name << "'.\n";
}

string ArbolGeneral::getCurrentPathName() {
    return currentDir ? currentDir->name : "???";
}

// --- DÍA 8: RENOMBRAR Y MOVER POR NOMBRE ---

void ArbolGeneral::rename(const string& oldName, const string& newName, Trie& trie) {
    if (!currentDir) return;

    // 1. Verificar que el nombre nuevo no exista ya (para no duplicar)
    for (const auto& child : currentDir->children) {
        if (child->name == newName) {
            cout << "Error: Ya existe un archivo con el nombre '" << newName << "'.\n";
            return;
        }
    }

    // 2. Buscar el nodo a renombrar
    for (auto& child : currentDir->children) {
        if (child->name == oldName) {
            // Cambiar nombre
            child->name = newName;
            
            // Actualizar Trie (Insertamos el nuevo. Borrar el viejo es complejo, 
            // por ahora solo agregamos el nuevo para que el autocompletado funcione).
            trie.insert(newName);

            cout << "Renombrado con exito: " << oldName << " -> " << newName << endl;
            return;
        }
    }

    cout << "Error: No se encontro '" << oldName << "'.\n";
}

void ArbolGeneral::move_by_name(const string& nameToMove, const string& nameDestFolder) {
    if (!currentDir) return;

    // A. Buscar el nodo que queremos mover (dentro de la carpeta actual)
    shared_ptr<Node> nodeToMove = nullptr;
    for (const auto& child : currentDir->children) {
        if (child->name == nameToMove) {
            nodeToMove = child;
            break;
        }
    }

    if (!nodeToMove) {
        cout << "Error: No se encontro '" << nameToMove << "' para mover.\n";
        return;
    }

    // B. Buscar el destino
    // Caso especial: ".." significa ir al padre del actual
    shared_ptr<Node> destFolder = nullptr;

    if (nameDestFolder == "..") {
        destFolder = currentDir->parent.lock(); // Obtener padre
        if (!destFolder) {
            cout << "Error: Ya estas en la raiz, no puedes mover a ..\n"; 
            return;
        }
    } else {
        // Buscar carpeta destino dentro de los hijos actuales
        for (const auto& child : currentDir->children) {
            if (child->name == nameDestFolder) {
                destFolder = child;
                break;
            }
        }
    }

    if (!destFolder) {
        cout << "Error: No se encontro el destino '" << nameDestFolder << "'.\n";
        return;
    }

    // C. Llamar a la lógica "pesada" del Día 3 usando los IDs encontrados
    // (Reutilizamos tu función moveNode que ya valida ciclos y todo eso)
    moveNode(nodeToMove->id, destFolder->id);
}

// --- DÍA 9 COMANDO SEARCH ---
void ArbolGeneral::search(const string& prefix, Trie& trie) {
    cout << "Ejecutando busqueda global..." << endl;
    // Reutilizamos tu función visual del Día 6
    autocompleteConsole(trie, prefix);
}