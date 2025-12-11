#include "Tree.hpp"
#include <iostream>

void menu_rm(Tree& tree) {
    std::string ruta;
    std::cout << "Ruta a eliminar: ";
    std::cin >> ruta;

    if (tree.remove_at_path(ruta))
        std::cout << "Movido a papelera.\n";
    else
        std::cout << "Error al eliminar.\n";
}
