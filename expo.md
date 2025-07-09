# Exposición: Funciones Principales del main.cpp - Proyecto Cocina 3D Interactiva
**Grupo 10 - COMPUTACIÓN GRÁFICA Y VISUAL**

---

## **Integrantes del Equipo**
- **Bryan Jean Piere Mercado Ajalcriña**
- **Brenda Gabriela Ormeño Bocanegra** 
- **Jheferson Rafael Suarez**
- **Gerardo Manuel Rodriguez Monzon**
- **José Colona Silva**
- **Axel Angello Zeballos Nuñez**

---

## **Parte 1: Introducción y Estructura del Proyecto** 

### **¿Qué es nuestro proyecto?**
- Una aplicación 3D desarrollada en **OpenGL** que simula un restaurante completo
- **Primer piso**: Cocina, comedor y almacén
- **Segundo piso**: Bar con área VIP  
- **Entorno exterior**: Carreteras, aceras y edificios circundantes

### **Arquitectura del main.cpp**
```cpp
#include "objects/kitchen.h"    // Cocina principal
#include "objects/dining.h"     // Área de comedor
#include "objects/storage.h"    // Almacén
#include "utils/camera.h"       // Sistema de cámara
#include "utils/lighting.h"     // Sistema de iluminación
#include "utils/menu.h"         // Menús contextuales
#include "utils/environment.h"  // Entorno y estructuras
```

El **main.cpp** actúa como el **controlador central** que:
- ✅ Coordina todos los módulos
- ✅ Maneja la renderización principal
- ✅ Gestiona la interacción del usuario
- ✅ Controla las animaciones y cámara

---

## **Parte 2: Función main() - Inicialización del Sistema**

### **Configuración Inicial de la Ventana**
```cpp
glutInit(&argc, argv);  
glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);  
glutInitWindowSize(1024, 768);  
glutCreateWindow("Cocina 3D Interactiva con Menu Expandido - Grupo 10");
```

### **Configuración OpenGL Esencial**
```cpp
glEnable(GL_DEPTH_TEST);     // Habilita el buffer de profundidad para 3D
glEnable(GL_LIGHTING);       // Sistema de iluminación realista
glEnable(GL_LIGHT0);         // Luz principal
glEnable(GL_COLOR_MATERIAL); // Materiales con colores
glEnable(GL_NORMALIZE);      // Normalización automática de vectores
```

### **Sistema de Transparencia**
```cpp
glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
glDisable(GL_BLEND);  // Deshabilitado por defecto para optimización
```

### **Registro de Callbacks Críticos**
- **glutDisplayFunc(display)** → Función de renderizado principal
- **glutReshapeFunc(reshape)** → Redimensionamiento de ventana
- **glutMouseFunc/MotionFunc** → Interacción con mouse
- **glutKeyboardFunc** → Control por teclado
- **glutIdleFunc(idle)** → Animación continua

---

## **Parte 3: Función display() - Corazón del Renderizado**

### **Sistema de Colores de Fondo Dinámicos**
```cpp
float coloresFondo[4][3] = {
    {0.8f, 0.8f, 0.8f}, // Gris claro - ambiente neutro
    {1.0f, 1.0f, 1.0f}, // Blanco - laboratorio
    {0.96f, 0.96f, 0.86f}, // Beige - ambiente cálido
    {0.53f, 0.81f, 0.98f}  // Celeste cielo - exterior
};
```

### **Modos de Visualización**
```cpp
if(iEstiloVisualizacion == 1) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Modo WIREFRAME
} else {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Modo SÓLIDO
}
```

### **Sistema de Renderizado por Secciones**
```cpp
// PRIMER PISO (iSeccionVisible == 0 || == 2)
drawParedes(); drawPiso(); 
drawKitchen(); drawDining(); drawStorage();

// SEGUNDO PISO (iSeccionVisible == 1 || == 2)  
drawSecondFloorKitchen();

// ENTORNO EXTERIOR (iSeccionVisible == 2)
drawGrassExterior(); drawAcera(); drawCarretera();
edificio(-6.56f, 0.0f, 5.5f, 1.0f, 0.0f, COLOR_VERDE);
edificio(11.06f, 0.0f, 5.5f, 1.0f, 0.0f, COLOR_AZUL);
```

### **Configuración de Cámara y Animación**
- **applyCamera()** → Aplica configuración FPS u orbital
- **Rotación automática** cuando animación está activa
- **glutSwapBuffers()** → Double buffering para fluidez

---

## **Parte 4: Sistema de Cámara y Controles**

### **Función onKeyboard() - Control Total del Usuario**
```cpp
void onKeyboard(unsigned char key, int x, int y) {
    cameraOnKeyboard(key, x, y);  // Delega controles WASD a módulo camera
    
    switch(key) {
        case 27: exit(0);          // ESC - Salida rápida
        case 'r': case 'R':        // RESET - Restaurar vista
        case 'f': case 'F':        // FPS MODE - Cambiar modo cámara
        case '1': iTipoCamara = 1; // Vista COCINA
        case '2': iTipoCamara = 2; // Vista COMEDOR  
        case '3': iTipoCamara = 3; // Vista ALMACÉN
    }
}
```

### **Dos Sistemas de Cámara Completos**

#### **🎮 Modo FPS (Primera Persona)**
- **WASD** → Movimiento libre en todas direcciones
- **Mouse** → Control de vista (pitch/yaw)
- **Coordenadas**: fpsX, fpsY, fpsZ, fpsPitch, fpsYaw
- **Ideal para**: Exploración inmersiva del restaurante

#### **🔄 Modo Orbital (Tercera Persona)**
- **Mouse** → Rotación orbital alrededor del centro
- **Vistas predefinidas** → Cocina, Comedor, Almacén
- **Variables**: camAngleX, camAngleY, camDistance
- **Ideal para**: Presentaciones y vistas panorámicas

### **Reset Inteligente**
```cpp
if (bCamaraFPS) {
    // Reset FPS a posición inicial
    fpsX = 0.0f; fpsY = 2.0f; fpsZ = 5.0f;
} else {
    // Reset orbital a vista general
    camAngleX = 20.0f; camAngleY = 45.0f; camDistance = 15.0f;
}
```

---

## **Parte 5: Funciones de Soporte y Optimización**

### **Función reshape() - Adaptación Inteligente**
```cpp
void reshape(int width, int height) {
    glViewport(0, 0, width, height);  // Ajusta viewport al nuevo tamaño
    glMatrixMode(GL_PROJECTION);      // Matriz de proyección
    glLoadIdentity();                 // Reset matriz
    gluPerspective(45.0f, (float)width/(float)height, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);       // Vuelve a modelview
}
```

**¿Por qué es importante?**
- ✅ **Mantiene proporciones** sin distorsión al redimensionar
- ✅ **Campo de visión 45°** optimal para experiencia 3D
- ✅ **Clipping planes** 0.1f a 100.0f para rendimiento

### **Función idle() - Motor de Animación**
```cpp
void idle() {
    updateFPSCamera();    // Actualiza cámara FPS constantemente
    
    if (bAnimacionActiva) {
        glutPostRedisplay(); // Solo redibuja cuando es necesario
    }
}
```

### **Optimizaciones Implementadas**
- **Renderizado condicional**: Solo redibuja cuando hay cambios
- **Actualización selectiva**: FPS camera se actualiza constantemente, otras solo cuando necesario
- **Control de estados**: Variables booleanas para controlar recursos

### **Gestión de Eventos Completa**
```cpp
glutKeyboardUpFunc(onKeyboardUp); // Necesario para movimiento WASD fluido
cameraOnKeyboardUp(key, x, y);    // Libera teclas correctamente
```

---

## **Parte 6: Integración y Conclusiones**

### **Flujo de Ejecución Completo**
```
1. main() → Inicialización OpenGL y callbacks
2. glutMainLoop() → Loop principal infinito
3. display() → Renderizado cada frame
4. idle() → Actualización continua
5. onKeyboard() → Respuesta a interacción
6. reshape() → Adaptación dinámica
```

### **Arquitectura Modular Exitosa**
El **main.cpp** demuestra **separación de responsabilidades**:

```cpp
// OBJETOS 3D (kitchen.h, dining.h, storage.h)
drawKitchen(); drawDining(); drawStorage();

// UTILIDADES (camera.h, lighting.h, environment.h)  
applyCamera(); configurarIluminacion(); drawParedes();

// INTERACCIÓN (menu.h)
creacionMenu(); cameraOnKeyboard();
```

### **Características Técnicas Destacadas**
- ✅ **Double Buffering** → Animación fluida sin parpadeo
- ✅ **Depth Testing** → Renderizado 3D correcto
- ✅ **Iluminación Dinámica** → Realismo visual
- ✅ **Múltiples Viewports** → 3 secciones + vista completa
- ✅ **Control Dual** → FPS + Orbital cameras
- ✅ **Entorno Completo** → Interior + Exterior integrados

### **Logros del Equipo**
- 🏆 **Simulación completa** de restaurante 3D
- 🏆 **Interactividad avanzada** con múltiples controles
- 🏆 **Código modular** y mantenible
- 🏆 **Rendimiento optimizado** con renderizado selectivo

### **El main.cpp como Director de Orquesta**
Nuestro archivo principal coordina perfectamente:
- **6 módulos** de objetos y utilidades
- **2 sistemas** de cámara
- **4 modos** de visualización  
- **3 secciones** + entorno exterior

---