# Definición del Formato y Comandos del Sistema

## 1. Estructura del JSON (Base de Datos)
# El árbol se guardará en un archivo `.json` siguiendo esta estructura recursiva. Cada nodo contiene una lista de hijos.

### Ejemplo de estructura:
```json
{
  "root": {
    "id": "1",
    "nombre": "Raiz_Sistema",
    "tipo": "directorio", 
    "contenido": "Descripción general",
    "children": [
      {
        "id": "2",
        "nombre": "Documentos",
        "tipo": "directorio",
        "contenido": "Carpeta de documentos",
        "children": [
            {
                "id": "4",
                "nombre": "tesis.pdf",
                "tipo": "archivo",
                "contenido": "base64_o_texto_plano",
                "children": []
            }
        ]
      },
      {
        "id": "3",
        "nombre": "Config",
        "tipo": "archivo",
        "contenido": "configuraciones=true",
        "children": []
      }
    ]
  }
}