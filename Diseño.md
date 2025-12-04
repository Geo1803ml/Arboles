## 1. Nodo (Node)
Cada nodo representa un archivo o carpeta dentro del árbol.

### Campos
- id: string (único)
- name: string
- type: { FILE, FOLDER }
- content: optional<string> (solo en archivos)
- parent: weak_ptr<Node>
- children: vector<shared_ptr<Node>>

## 2. Árbol (Tree)
- root: Nodo principal con nombre "/"
- Cada operación usa rutas tipo UNIX (/carpeta/subcarpeta)

## 3. Operaciones Principales
- insert_at_path()
- remove_at_path()
- move_path()
- rename_at_path()
- list_children()
- save_to_file()
- export_preorder()
- find_by_name()
- restore_from_trash()

## 4. JSON
Cada nodo se guarda como:

```json
{
  "id": "n1",
  "name": "docs",
  "type": "folder",
  "content": null,
  "children": [ ... ]
}
