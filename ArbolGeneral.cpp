#include <iostream>
#include <vector>
#include <string>
#include "Nodo.h" // Asegúrate de que Nodo.h define la clase Nodo adecuadamente


using namespace std;

class ArbolGeneral {
private:
    Nodo* raiz;

    // Función auxiliar recursiva para buscar un nodo por ID
    // (Necesaria para saber dónde insertar el nuevo hijo)
    Nodo* buscarRecursivo(Nodo* actual, string idBuscado) {
        if (actual == nullptr) return nullptr;
        if (actual->id == idBuscado) return actual;

        // Recorrer hijos
        for (Nodo* hijo : actual->children) {
            Nodo* encontrado = buscarRecursivo(hijo, idBuscado);
            if (encontrado != nullptr) return encontrado;
        }
        return nullptr;
    }

    // --- AGREGAR EN LA SECCIÓN PRIVATE ---

    // Función auxiliar para encontrar al papá de un nodo específico
    Nodo* buscarPadreDe(Nodo* actual, string idHijoBuscado) {
        if (actual == nullptr) return nullptr;

        for (Nodo* hijo : actual->children) {
            // Si uno de mis hijos es el que busco, ¡YO soy el padre!
            if (hijo->id == idHijoBuscado) {
                return actual;
            }
            // Si no, busco en los nietos...
            Nodo* resultado = buscarPadreDe(hijo, idHijoBuscado);
            if (resultado != nullptr) return resultado;
        }
        return nullptr;
    }

    // --- AGREGAR EN LA SECCIÓN PUBLIC ---

    // Función Mover (Cut & Paste)
    void moverNodo(string idNodo, string idNuevoPadre) {
        if (idNodo == raiz->id) {
            cout << "-> Error: No se puede mover la raiz." << endl;
            return;
        }

        // 1. Buscamos los protagonistas
        Nodo* nodoAMover = buscarRecursivo(raiz, idNodo);
        Nodo* nuevoPadre = buscarRecursivo(raiz, idNuevoPadre);
        Nodo* antiguoPadre = buscarPadreDe(raiz, idNodo);

        // 2. Validaciones
        if (nodoAMover == nullptr) {
            cout << "-> Error: El nodo a mover no existe." << endl; 
            return;
        }
        if (nuevoPadre == nullptr) {
            cout << "-> Error: El nuevo padre no existe." << endl; 
            return;
        }
        if (antiguoPadre == nullptr) {
            cout << "-> Error: Estructura corrupta (el nodo no tiene padre)." << endl; 
            return;
        }
        // Validación extra: No mover un nodo dentro de sí mismo (evitar ciclos)
        // (Opcional por ahora, pero recomendado implementarlo luego)

        // 3. "Cortar" (Borrar del padre antiguo)
        // Usamos un iterador para buscar y borrar del vector
        for (auto it = antiguoPadre->children.begin(); it != antiguoPadre->children.end(); ++it) {
            if ((*it)->id == idNodo) {
                antiguoPadre->children.erase(it);
                break; // Ya lo borramos, salimos del ciclo
            }
        }

        // 4. "Pegar" (Agregar al nuevo padre)
        nuevoPadre->children.push_back(nodoAMover);
        
        cout << "-> Exito: Nodo '" << nodoAMover->nombre 
             << "' movido de '" << antiguoPadre->nombre 
             << "' a '" << nuevoPadre->nombre << "'." << endl;
    }

public:
    ArbolGeneral() {
        raiz = nullptr;
    }

    // 1. FUNCION INSERTAR
    // Si el árbol está vacío, crea la raíz.
    // Si no, busca al padre y le agrega el hijo.
    void insertar(string idPadre, string id, string nombre, string tipo, string contenido) {
        Nodo* nuevo = new Nodo(id, nombre, tipo, contenido);

        if (raiz == nullptr) {
            raiz = nuevo;
            cout << "-> Raiz creada exitosamente: " << nombre << endl;
            return;
        }

        Nodo* padre = buscarRecursivo(raiz, idPadre);

        if (padre != nullptr) {
            padre->children.push_back(nuevo); // Asumiendo que children es un vector<Nodo*>
            cout << "-> Nodo '" << nombre << "' agregado bajo '" << padre->nombre << "'" << endl;
        } else {
            cout << "-> Error: No se encontro el padre con ID: " << idPadre << endl;
            // Aquí podrías borrar 'nuevo' para no dejar basura en memoria
            delete nuevo; 
        }
    }

    // 2. FUNCION LISTAR HIJOS
    void listarHijos(string idPadre) {
        Nodo* padre = buscarRecursivo(raiz, idPadre);

        if (padre != nullptr) {
            cout << "Hijos de " << padre->nombre << ":" << endl;
            if (padre->children.empty()) {
                cout << "  (No tiene hijos)" << endl;
            } else {
                for (Nodo* hijo : padre->children) {
                    cout << "  - [" << hijo->id << "] " << hijo->nombre 
                         << " (" << hijo->tipo << ")" << endl;
                }
            }
        } else {
            cout << "-> Error: Nodo no encontrado." << endl;
        }
    }
    
    // Getter para la raíz (útil para pruebas)
    Nodo* getRaiz() { return raiz; }
};
