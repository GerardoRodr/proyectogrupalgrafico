# Proyecto Grupal - Cocina 3D Interactiva

Proyecto de graficos por computadora que simula una cocina 3D y con suerte algo más xddddddddddddddddddd

## 📁 Estructura del Proyecto

```
ProyectoGrupal/
├── src/                     # Código fuente
│   ├── main.cpp            # Archivo principal
│   ├── objects/            # Objetos de la escena
│   │   ├── common.cpp      # Funciones compartidas
│   │   ├── kitchen.cpp     # Cocina (Jheferson, Brenda, Bryan, Jose, Angello)
│   │   ├── dining.cpp      # Comedor
│   │   └── storage.cpp     # Almacén
│   └── utils/              # Utilidades
│       ├── camera.cpp      # Control de cámara
│       ├── lighting.cpp    # Iluminación
│       ├── menu.cpp        # Sistema de menús
│       └── environment.cpp # Entorno (pisos, paredes)
├── include/                 # Archivos de cabecera
│   ├── objects/
│   │   ├── common.h
│   │   ├── kitchen.h
│   │   ├── dining.h
│   │   └── storage.h
│   └── utils/
│       ├── camera.h
│       ├── lighting.h
│       ├── menu.h
│       └── environment.h
├── assets/                  # Recursos del proyecto
│   └── Revolution-909.wav   # Archivo de audio
├── build/                   # Archivos compilados
├── Makefile                 # Script de compilación
└── README.md               # Este archivo
```

## 🔨 Compilación

- Usar la tarea "C/C++: g++.exe build active file" 
- O usar Ctrl+Shift+P > "Tasks: Run Task"

## 🎮 Controles

### Teclado:
- `ESC`: Salir del programa
- `R`: Resetear vista de cámara
- `A`: Activar/desactivar animación
- `1`: Vista de cocina
- `2`: Vista de comedor  
- `3`: Vista de almacén

### Mouse:
- **Clic derecho**: Abrir menú contextual
- **Clic izquierdo + arrastrar**: Rotar cámara
- **Rueda del mouse**: Zoom in/out

## 🍳 Secciones del Proyecto

### Cocina (kitchen.cpp)
- **Jheferson**: Fregadero con grifo
- **Brenda**: Gabinetes superiores con puertas
- **Bryan**: Encimera, base y cajones  
- **Jose**: Refrigerador y estufa con quemadores
- **Angello**: Mesa y sillas de la cocina

### Comedor (dining.cpp)
- Mesas para 2 personas (rectangulares)
- Mesas para 4 personas (cuadradas)
- Sillas con diferentes colores

### Almacén (storage.cpp)
- Estanterías metálicas
- Cajas de comida con etiquetas
- Sacos de harina y azúcar
- Botellas transparentes con líquidos
- Latas de conservas
- Congelador horizontal

## 🎨 Características

- **Iluminación**: 3 tipos (día, noche, ambiente)
- **Visualización**: Sólido y alambre
- **Sonido**: Música de fondo activable
- **Animación**: Rotación automática
- **Cámara**: Libre y vistas preestablecidas
- **Transparencias**: Botellas con líquidos visibles

## 👥 Equipo - Grupo 10

- **Jheferson**: Fregadero
- **Brenda**: Gabinetes superiores  
- **Bryan**: Encimera y cajones
- **Jose**: Electrodomésticos
- **Angello**: Mesa y sillas
- **Gerardo**: Integración y entorno

## 📋 Dependencias

- OpenGL
- FreeGLUT
- GLU
- Windows Multimedia API (para sonido)

¡Disfruta explorando la cocina 3D! 🍳✨
