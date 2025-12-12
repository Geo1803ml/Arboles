#include "Tree.hpp"
#include <iostream>

int main(){
    Tree t;

    for (int i = 0; i < 200; i++)
        t.insert_at_path("/", "n" + std::to_string(i), NodeType::FOLDER);

    std::cout << "Nodos creados: 200\n";
    std::cout << "Altura: " << t.height() << "\n";
    std::cout << "Tamaño total: " << t.size() << "\n";
}
