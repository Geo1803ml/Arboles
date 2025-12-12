#include <iostream>
#include <string>
#include <sstream> // Necesario para partir el texto (split)
#include "ArbolGeneral.hpp"
#include "Trie.hpp"

using namespace std;

int main() {
    // 1. Inicialización del Sistema
    ArbolGeneral sistema;
    Trie autocompletado;

    cout << "Cargando sistema de archivos..." << endl;

    // 2. Cargar datos desde el JSON
    if (!sistema.load_from_file("ejemplo.json")) {
        cout << "[Aviso] No se encontro 'ejemplo.json'. Iniciando vacio.\n";
    } else {
        sistema.loadNamesIntoTrie(autocompletado);
        cout << "[Exito] Datos cargados y Trie indexado.\n";
    }

    // --- MENÚ PRINCIPAL (ACTUALIZADO DÍA 10) ---
    cout << "\n============================================\n";
    cout << "      CONSOLA DE ARBOLES (FINAL - Dia 10)   \n";
    cout << "============================================\n";
    cout << "Comandos disponibles:\n";
    cout << "  ls                  -> Listar contenido\n";
    cout << "  mkdir <nombre>      -> Crear carpeta\n";
    cout << "  touch <nombre>      -> Crear archivo\n";
    cout << "  cd <nombre>         -> Entrar a carpeta\n";
    cout << "  mv <origen> <dest>  -> Mover archivo/carpeta\n";
    cout << "  rename <old> <new>  -> Renombrar\n";
    cout << "  search <texto>      -> Buscar archivo (Trie)\n";
    cout << "  test                -> Prueba de Rendimiento (Dia 10)\n"; // NUEVO
    cout << "  exit                -> Salir\n";
    cout << "============================================\n";

    string input, command, arg;

    // 3. Bucle Principal
    while (true) {
        cout << "\n" << sistema.getCurrentPathName() << "/> ";
        
        getline(cin, input);
        if (input.empty()) continue;

        stringstream ss(input);
        ss >> command >> arg; // Lee comando y primer argumento

        // --- Procesar Comandos ---
        if (command == "exit") {
            break;
        }
        else if (command == "ls") {
            sistema.ls();
        }
        else if (command == "mkdir") {
            if (arg.empty()) cout << "Uso: mkdir <nombre>\n";
            else sistema.mkdir(arg, autocompletado);
        }
        else if (command == "touch") {
            if (arg.empty()) cout << "Uso: touch <nombre>\n";
            else sistema.touch(arg, autocompletado);
        }
        else if (command == "cd") {
            if (arg.empty()) cout << "Uso: cd <carpeta>\n";
            else sistema.cd(arg);
        }
        // --- DÍA 8: RENAME ---
        else if (command == "rename") {
            string newName;
            ss >> newName; 
            if (arg.empty() || newName.empty()) {
                cout << "Uso: rename <nombre_actual> <nombre_nuevo>\n";
            } else {
                sistema.rename(arg, newName, autocompletado);
            }
        }
        // --- DÍA 8: MOVE ---
        else if (command == "mv") {
            string dest;
            ss >> dest; 
            if (arg.empty() || dest.empty()) {
                cout << "Uso: mv <archivo_a_mover> <carpeta_destino>\n";
            } else {
                sistema.move_by_name(arg, dest);
            }
        }
        // --- DÍA 9: SEARCH ---
        else if (command == "search") {
            if (arg.empty()) {
                cout << "Uso: search <nombre_o_prefijo>\n";
            } else {
                sistema.search(arg, autocompletado);
            }
        }
        // --- DÍA 10: TEST DE RENDIMIENTO 
        else if (command == "test") {
            sistema.runPerformanceTest(autocompletado);
        }

        // DÍA 11: INTEGRIDAD
        else if (command == "status") {
            sistema.checkIntegrity();
        }
        // --------------------------
        else if (command == "help") {
            cout << "Ayuda: ls, mkdir, touch, cd, mv, rename, search, test, exit\n";
        }
        else {
            cout << "Comando no reconocido: '" << command << "'\n";
            sistema.autocompleteConsole(autocompletado, command); 
        }
        
        arg = ""; 
    }

    // 4. Guardar al Salir
    cout << "Guardando cambios en 'ejemplo.json'...\n";
    if (sistema.save_to_file("ejemplo.json")) {
        cout << "Guardado exitoso.\n";
    } else {
        cout << "Error al guardar.\n";
    }

    cout << "Saliendo. Hasta luego!\n";
    return 0;
}