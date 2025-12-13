# Simulador de Sistema de Archivos (Tree + Trie) 

Este proyecto implementa una consola de comandos simulada en C++ que permite gestionar una estructura de directorios y archivos. Utiliza un **Árbol General** para la jerarquía de carpetas y una estructura **Trie** para un motor de búsqueda y autocompletado eficiente.

## 👥 Integrantes
* **Eduardo** (Desarrollador)
* **Geovanny** (Desarrollador)
* **Materia:** Estructura de Datos
* **Fecha:** Diciembre 2025

##  Características Principales
1.  **Persistencia de Datos:** El estado del árbol se guarda y carga automáticamente en `ejemplo.json`.
2.  **Motor de Búsqueda:** Implementación de un Trie para buscar archivos por prefijo en tiempo real (microsegundos).
3.  **Navegación Robusta:** Soporte para rutas relativas (`cd carpeta/subcarpeta`), absolutas y navegación al padre (`cd ..`).
4.  **Gestión Completa:** Crear, listar, mover y renombrar archivos y carpetas.
5.  **Diagnóstico:** Herramientas para verificar la integridad de los punteros del árbol y pruebas de rendimiento.

##  Cómo Compilar y Ejecutar

El proyecto requiere un compilador compatible con **C++17** (debido al uso de `std::optional` y `std::shared_ptr`).

### Comando de Compilación (G++):
```bash
g++ main.cpp ArbolGeneral.cpp -o sistema_archivos.exe -std=c++17