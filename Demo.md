## Objetivo
Demostrar el correcto funcionamiento del árbol de directorios y sus operaciones principales.

## Escenario de prueba

1. Crear carpeta raíz:
   - mkdir /documentos

2. Crear subcarpetas:
   - mkdir /documentos/tareas
   - mkdir /documentos/examenes

3. Crear archivos:
   - touch /documentos/tareas tarea1.txt
   - touch /documentos/examenes parcial.txt

4. Mostrar estructura:
   - export_preorder()

5. Eliminar archivo:
   - rm /documentos/tareas/tarea1.txt

6. Restaurar desde papelera:
   - restore_from_trash()

7. Búsqueda por prefijo:
   - trie.search("ta")

8. Guardar estructura:
   - save_to_file("estructura.json")
