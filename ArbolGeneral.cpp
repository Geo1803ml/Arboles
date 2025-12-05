#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // Para std::find_if si quisieras optimizar, pero tu loop está bien.
#include "Nodo.h"

using namespace std;

class ArbolGeneral {
private:
    Nodo* raiz;

    // --- FUNCIONES AUXILIARES (PRIVADAS) ---

    // Buscar nodo por ID recursivamente
    Nodo* buscarRecursivo(Nodo* actual, string idBuscado) {
        if (actual == nullptr) return nullptr;
        if (actual->id == idBuscado) return actual;

        for (Nodo* hijo : actual->children) {
            Nodo* encontrado = buscarRecursivo(hijo, idBuscado);
            if (encontrado != nullptr) return encontrado;
        }
        return nullptr;
    }

    // Buscar al padre de un nodo
    Nodo* buscarPadreDe(Nodo* actual, string idHijoBuscado) {
        if (actual == nullptr) return nullptr;

        for (Nodo* hijo : actual->children) {
            if (hijo->id == idHijoBuscado) {
                return actual; // ¡Lo encontré! Soy su padre.
            }
            Nodo* resultado = buscarPadreDe(hijo, idHijoBuscado);
            if (resultado != nullptr) return resultado;
        }
        return nullptr;
    }

    // Validar que no estemos moviendo un nodo dentro de sus propios hijos (Ciclo)
    bool esSubnodo(Nodo* posibleHijo, string idPadreObjetivo) {
        if (posibleHijo->id == idPadreObjetivo) return true;
        for (Nodo* hijo : posibleHijo->children) {
            if (esSubnodo(hijo, idPadreObjetivo)) return true;
        }
        return false;
    }

public:
    ArbolGeneral() {
        raiz = nullptr;
    }

    // --- FUNCIONES PÚBLICAS ---

    void insertar(string idPadre, string id, string nombre, string tipo, string contenido) {
        Nodo* nuevo = new Nodo(id, nombre, tipo, contenido);

        if (raiz == nullptr) {
            raiz = nuevo;
            return;
        }

        Nodo* padre = buscarRecursivo(raiz, idPadre);
        if (padre != nullptr) {
            padre->children.push_back(nuevo);
        } else {
            cout << "Error: Padre no encontrado." << endl;
            delete nuevo;
        }
    }

    void listarHijos(string idPadre) {
        Nodo* padre = buscarRecursivo(raiz, idPadre);
        if (padre != nullptr) {
            cout << "Hijos de " << padre->nombre << ": ";
            for (Nodo* hijo : padre->children) {
                cout << hijo->nombre << " ";
            }
            cout << endl;
        }
    }

    // TU FUNCIÓN PRINCIPAL DEL DÍA 3
    void moverNodo(string idNodo, string idNuevoPadre) {
        if (raiz == nullptr) return;
        
        if (idNodo == raiz->id) {
            cout << "-> Error: No se puede mover la raiz." << endl;
            return;
        }

        // 1. Buscamos punteros
        Nodo* nodoAMover = buscarRecursivo(raiz, idNodo);
        Nodo* nuevoPadre = buscarRecursivo(raiz, idNuevoPadre);
        Nodo* antiguoPadre = buscarPadreDe(raiz, idNodo);

        // 2. Validaciones básicas
        if (nodoAMover == nullptr || nuevoPadre == nullptr || antiguoPadre == nullptr) {
            cout << "-> Error: Nodo, nuevo padre o antiguo padre no validos." << endl;
            return;
        }

        // 3. Validación de ciclo (IMPORTANTE)
        // Si intentas mover la carpeta "Fotos" adentro de "Fotos/Vacaciones", rompes el árbol.
        if (esSubnodo(nodoAMover, idNuevoPadre)) {
            cout << "-> Error: No puedes mover un nodo dentro de uno de sus descendientes." << endl;
            return;
        }

        // 4. Cortar (Borrar del vector del padre antiguo)
        for (auto it = antiguoPadre->children.begin(); it != antiguoPadre->children.end(); ++it) {
            if ((*it)->id == idNodo) {
                antiguoPadre->children.erase(it);
                break; 
            }
        }

        // 5. Pegar (Agregar al vector del nuevo padre)
        nuevoPadre->children.push_back(nodoAMover);
        cout << "-> Exito: Movido '" << nodoAMover->nombre << "' a '" << nuevoPadre->nombre << "'" << endl;
    }
    
    // Getter para tests
    Nodo* getRaiz() { return raiz; }
};