#include "ArbolGeneral.cpp"

void correrPruebas() {
    //esto aun no esta terminado
    ArbolGeneral arbol;
    
    cout << "--- INICIO DE PRUEBAS ---" << endl;

    // 1. Prueba de Inserción
    cout << "1. Creando arbol..." << endl;
    arbol.insertar("0", "1", "Raiz", "dir", "");
    arbol.insertar("1", "2", "Documentos", "dir", "");
    arbol.insertar("1", "3", "Fotos", "dir", "");
    arbol.insertar("2", "4", "Tesis.pdf", "file", "");
    
    // Verificamos visualmente listando
    arbol.listarHijos("1"); // Debería salir Documentos y Fotos
    arbol.listarHijos("2"); // Debería salir Tesis.pdf

    // 2. Prueba de Movimiento
    cout << "\n2. Moviendo 'Tesis.pdf' de 'Documentos' a 'Fotos'..." << endl;
    arbol.moverNodo("4", "3"); // Mueve ID 4 (Tesis) al ID 3 (Fotos)

    // 3. Verificación
    cout << "\n--- Verificacion ---" << endl;
    cout << "Carpeta Documentos (debe estar vacia):" << endl;
    arbol.listarHijos("2"); 
    
    cout << "Carpeta Fotos (debe tener Tesis.pdf):" << endl;
    arbol.listarHijos("3");
}
int main() {
    correrPruebas();
    return 0;
}