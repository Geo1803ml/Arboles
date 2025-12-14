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

## 📖 Lista de Comandos Disponibles

Una vez iniciado el programa, puedes utilizar los siguientes comandos en la consola interactiva:

### 📂 Navegación y Visualización
| Comando | Argumentos | Descripción | Ejemplo |
| :--- | :--- | :--- | :--- |
| **`ls`** | *(Ninguno)* | Lista el contenido del directorio actual. | `ls` |
| **`cd`** | `<ruta>` | Cambia el directorio actual. Soporta `..` para subir un nivel. | `cd documentos/tareas` |
| **`pwd`** | *(Ninguno)* | Muestra la ruta absoluta donde te encuentras. | `pwd` |

### 📝 Gestión de Archivos y Carpetas
| Comando | Argumentos | Descripción | Ejemplo |
| :--- | :--- | :--- | :--- |
| **`mkdir`** | `<nombre>` | Crea una nueva carpeta en el directorio actual. | `mkdir fotos` |
| **`touch`** | `<nombre>` | Crea un nuevo archivo vacío en el directorio actual. | `touch notas.txt` |
| **`mv`** | `<origen> <destino>` | Mueve un archivo o carpeta a otra ubicación. | `mv notas.txt documentos` |
| **`rename`** | `<viejo> <nuevo>` | Cambia el nombre de un archivo o carpeta. | `rename tesis.txt final.txt` |

### 🔍 Herramientas Avanzadas
| Comando | Argumentos | Descripción | Ejemplo |
| :--- | :--- | :--- | :--- |
| **`search`** | `<prefijo>` | **(Trie)** Busca archivos en todo el sistema que empiecen con el prefijo dado. | `search ta` |
| **`export`** | `<nombre.txt>` | Exporta la estructura completa del árbol en formato Preorden a un archivo de texto. | `export reporte.txt` |
| **`status`** | *(Ninguno)* | Verifica la integridad de los punteros del árbol (diagnóstico de salud). | `status` |
| **`test`** | *(Ninguno)* | **(Benchmark)** Genera 500 nodos automáticamente para medir el rendimiento de inserción y búsqueda. | `test` |

### ⚙️ Sistema
| Comando | Argumentos | Descripción |
| :--- | :--- | :--- |
| **`help`** | *(Ninguno)* | Muestra una lista rápida de los comandos disponibles. |
| **`exit`** | *(Ninguno)* | Guarda automáticamente los cambios en `ejemplo.json` y cierra el programa. |