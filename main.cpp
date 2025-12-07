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

    // 2. Cargar datos desde el JSON (Persistencia)
    // Asegúrate de tener 'ejemplo.json' o el programa iniciará vacío.
    if (!sistema.load_from_file("ejemplo.json")) {
        cout << "[Aviso] No se encontro 'ejemplo.json' o hubo error al leer. Iniciando vacio.\n";
    } else {
        // Si cargó bien, llenamos el Trie para el autocompletado
        sistema.loadNamesIntoTrie(autocompletado);
        cout << "[Exito] Datos cargados y Trie indexado.\n";
    }

    cout << "\n============================================\n";
    cout << "      CONSOLA DE ARBOLES (Dia 7)           \n";
    cout << "============================================\n";
    cout << "Comandos disponibles:\n";
    cout << "  ls                  -> Listar contenido\n";
    cout << "  mkdir <nombre>      -> Crear carpeta\n";
    cout << "  touch <nombre>      -> Crear archivo\n";
    cout << "  cd <nombre>         -> Entrar a carpeta (.. para regresar)\n";
    cout << "  exit                -> Salir\n";
    cout << "============================================\n";

    string input, command, arg;

    // 3. Bucle Principal (La Consola Interactiva)
    while (true) {
        // Mostrar ruta actual como prompt (ej: root/> )
        cout << "\n" << sistema.getCurrentPathName() << "/> ";
        
        // Leer toda la línea que escribe el usuario
        getline(cin, input);
        if (input.empty()) continue;

        // Separar comando y argumento (ej: "mkdir tarea" -> cmd="mkdir", arg="tarea")
        stringstream ss(input);
        ss >> command >> arg; 

        // --- Procesar Comandos ---
        if (command == "exit") {
            break; // Rompe el bucle y termina
        }
        else if (command == "ls") {
            sistema.ls();
        }
        else if (command == "mkdir") {
            if (arg.empty()) cout << "Error: Falta el nombre. Uso: mkdir <nombre>\n";
            else sistema.mkdir(arg, autocompletado);
        }
        else if (command == "touch") {
            if (arg.empty()) cout << "Error: Falta el nombre. Uso: touch <nombre>\n";
            else sistema.touch(arg, autocompletado);
        }
        else if (command == "cd") {
            if (arg.empty()) cout << "Error: Falta el destino. Uso: cd <carpeta>\n";
            else sistema.cd(arg);
        }
        else if (command == "help") {
            cout << "Ayuda: ls, mkdir, touch, cd, exit\n";
        }
        else {
            cout << "Comando no reconocido: '" << command << "'\n";
            // Aquí conectarás el autocompletado visual en el futuro
            sistema.autocompleteConsole(autocompletado, command);
        }
        
        // Limpiar argumento para la siguiente vuelta
        arg = ""; 
    }

    // 4. Guardado Automático al Salir (Opcional pero recomendado)
    cout << "Guardando cambios en 'ejemplo.json'...\n";
    if (sistema.save_to_file("ejemplo.json")) {
        cout << "Guardado exitoso.\n";
    } else {
        cout << "Error al guardar.\n";
    }

    cout << "Saliendo. Hasta luego!\n";
    return 0;
}