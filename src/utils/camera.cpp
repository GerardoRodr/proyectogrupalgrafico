#include "utils/camera.h"
#include "utils/menu.h"
#include <GL/freeglut.h>
#include <cmath>

// Variables globales de camara orbital
float camAngleX = 20.0f;
float camAngleY = 45.0f;
float camDistance = 15.0f;
int mouseX, mouseY;
bool mouseLeftDown = false;
int iTipoCamara = 0;

// Variables para camara FPS
float fpsX = 0.0f, fpsY = 2.0f, fpsZ = 5.0f;  // Posicion inicial de la camara FPS
float fpsPitch = 0.0f, fpsYaw = 0.0f;          // Angulos de rotacion
bool bCamaraFPS = false;                       // Modo camara (false = orbital, true = FPS)
bool mouseRightDown = false;                   // Estado del boton derecho
bool keys[256];                                // Estados de las teclas

// Constantes para el movimiento FPS
const float MOVE_SPEED = 0.1f;                 // Velocidad de movimiento
const float MOUSE_SENSITIVITY = 0.2f;         // Sensibilidad del mouse

// **CONFIGURACION DE CAMARA PREESTABLECIDA**
void configurarCamara() {
    if (iTipoCamara == 1) { // Vista de cocina
        camAngleX = 10.0f;
        camAngleY = 80.0f;
        camDistance = 4.0f;
    }
    else if (iTipoCamara == 2) { // Vista de comedor
        camAngleX = 20.0f;
        camAngleY = 90.0f;
        camDistance = 14.0f;
    }
    else if (iTipoCamara == 3) { // Vista de almacen
        camAngleX = 20.0f;
        camAngleY = 150.0f;
        camDistance = 4.0f;
    }
    // iTipoCamara == 0 es camara libre, no se modifica
}

// **MOVIMIENTO CON EL MOUSE**
void cameraOnMouse(int button, int state, int x, int y) {
    if (bCamaraFPS) {
        // Modo FPS: boton izquierdo para rotar
        if (button == GLUT_LEFT_BUTTON) {
            if (state == GLUT_DOWN) {
                mouseRightDown = true;
                mouseX = x;
                mouseY = y;
                glutSetCursor(GLUT_CURSOR_NONE); // Ocultar cursor
            } else if (state == GLUT_UP) {
                mouseRightDown = false;
                glutSetCursor(GLUT_CURSOR_INHERIT); // Mostrar cursor
            }
        }
    } else {
        // Modo orbital: boton izquierdo para rotar
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
            mouseX = x;
            mouseY = y;
        }
        
        // Zoom con rueda del mouse (solo en modo orbital)
        else if (button == 3 && state == GLUT_DOWN) { // Rueda arriba
            camDistance -= 0.5f;
            if (camDistance < 5.0f) camDistance = 5.0f;
            glutPostRedisplay();
        }
        else if (button == 4 && state == GLUT_DOWN) { // Rueda abajo
            camDistance += 0.5f;
            if (camDistance > 25.0f) camDistance = 25.0f;
            glutPostRedisplay();
        }
    }
}

void cameraOnMotion(int x, int y) {
    if (bCamaraFPS && mouseRightDown) {
        // Calcular diferencias del mouse
        int deltaX = x - mouseX;
        int deltaY = y - mouseY;
        
        // Actualizar angulos de rotacion
        fpsYaw += deltaX * MOUSE_SENSITIVITY;
        fpsPitch -= deltaY * MOUSE_SENSITIVITY;
        
        // Limitar el pitch para evitar voltearse
        if (fpsPitch > 89.0f) fpsPitch = 89.0f;
        if (fpsPitch < -89.0f) fpsPitch = -89.0f;
        
        // Normalizar yaw
        if (fpsYaw >= 360.0f) fpsYaw -= 360.0f;
        if (fpsYaw < 0.0f) fpsYaw += 360.0f;
        
        mouseX = x;
        mouseY = y;
        glutPostRedisplay();
    } else if (!bCamaraFPS) {
        // Modo orbital original
        camAngleX = (camAngleX + (y - mouseY));
        camAngleY = (camAngleY + (x - mouseX));
        mouseX = x;
        mouseY = y;
        glutPostRedisplay();
    }
}

// **MANEJO DE TECLAS PARA MOVIMIENTO FPS**
void cameraOnKeyboard(unsigned char key, int x, int y) {
    keys[key] = true;
    
    // Cambiar modo de camara con la tecla 'C'
    if (key == 'c' || key == 'C') {
        bCamaraFPS = !bCamaraFPS;
        if (bCamaraFPS) {
            // Cambiar a FPS: posicionar camara en una buena ubicacion inicial
            fpsX = 0.0f;
            fpsY = 2.0f;
            fpsZ = 5.0f;
            fpsPitch = 0.0f;
            fpsYaw = 0.0f;
        }
        glutPostRedisplay();
    }
}

void cameraOnKeyboardUp(unsigned char key, int x, int y) {
    keys[key] = false;
}

// **ACTUALIZAR POSICION DE CAMARA FPS**
void updateFPSCamera() {
    if (!bCamaraFPS) return;
    
    bool haMovido = false; // Variable para detectar si hubo movimiento
    
    // Convertir angulos a radianes
    float yawRad = fpsYaw * M_PI / 180.0f;
    float pitchRad = fpsPitch * M_PI / 180.0f;
    
    // Calcular vectores de direccion
    float frontX = cos(pitchRad) * cos(yawRad);
    float frontY = sin(pitchRad);
    float frontZ = cos(pitchRad) * sin(yawRad);
    
    float rightX = cos(yawRad - M_PI/2.0f);
    float rightZ = sin(yawRad - M_PI/2.0f);
    
    // Movimiento con WASD
    if (keys['w'] || keys['W']) {
        fpsX += frontX * MOVE_SPEED;
        fpsY += frontY * MOVE_SPEED;
        fpsZ += frontZ * MOVE_SPEED;
        haMovido = true;
    }
    if (keys['s'] || keys['S']) {
        fpsX -= frontX * MOVE_SPEED;
        fpsY -= frontY * MOVE_SPEED;
        fpsZ -= frontZ * MOVE_SPEED;
        haMovido = true;
    }
    if (keys['a'] || keys['A']) {
        fpsX += rightX * MOVE_SPEED;
        fpsZ += rightZ * MOVE_SPEED;
        haMovido = true;
    }
    if (keys['d'] || keys['D']) {
        fpsX -= rightX * MOVE_SPEED;
        fpsZ -= rightZ * MOVE_SPEED;
        haMovido = true;
    }
    
    // Movimiento vertical con Space y Z
    if (keys[' ']) { // Espacio para subir
        fpsY += MOVE_SPEED;
        haMovido = true;
    }
    if (keys['z'] || keys['Z']) { // Z para bajar
        fpsY -= MOVE_SPEED;
        haMovido = true;
    }
    
    // **FORZAR REDIBUJADO SI HUBO MOVIMIENTO**
    if (haMovido) {
        glutPostRedisplay();
    }
}

// **APLICAR CONFIGURACION DE CAMARA**
void applyCamera() {
    if (bCamaraFPS) {
        // Convertir angulos a radianes
        float yawRad = fpsYaw * M_PI / 180.0f;
        float pitchRad = fpsPitch * M_PI / 180.0f;
        
        // Calcular punto de mira
        float targetX = fpsX + cos(pitchRad) * cos(yawRad);
        float targetY = fpsY + sin(pitchRad);
        float targetZ = fpsZ + cos(pitchRad) * sin(yawRad);
        
        // Aplicar vista FPS
        gluLookAt(
            fpsX, fpsY, fpsZ,           // Posicion de la camara
            targetX, targetY, targetZ,   // Punto al que mira
            0.0f, 1.0f, 0.0f            // Vector "arriba"
        );
    } else {
        // Camara orbital original
        float camX = camDistance * cos(camAngleY * M_PI/180) * cos(camAngleX * M_PI/180);
        float camY = camDistance * sin(camAngleX * M_PI/180);
        float camZ = camDistance * sin(camAngleY * M_PI/180) * cos(camAngleX * M_PI/180);
        
        gluLookAt(
            camX, camY, camZ,
            2.25f, 0.0f, 0.5f,
            0.0f, 1.0f, 0.0f
        );
    }
}
