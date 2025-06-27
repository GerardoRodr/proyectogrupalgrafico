#include "utils/camera.h"
#include "utils/menu.h"
#include <GL/freeglut.h>
#include <cmath>

// Variables globales de camara
float camAngleX = 20.0f;
float camAngleY = 45.0f;
float camDistance = 15.0f;
int mouseX, mouseY;
bool mouseLeftDown = false;
int iTipoCamara = 0;

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
void onMouse(int button, int state, int x, int y) {
    if ( (button == GLUT_LEFT_BUTTON) & (state == GLUT_DOWN) ) {
        mouseX = x;
        mouseY = y;
    }
    
    // Zoom con rueda del mouse
    else if (button == 3 && state == GLUT_DOWN) { // Rueda arriba
        camDistance -= 0.5f;
        if (camDistance < 5.0f) camDistance = 5.0f; // Minimo ajustado
        glutPostRedisplay();
    }
    else if (button == 4 && state == GLUT_DOWN) { // Rueda abajo
        camDistance += 0.5f;
        if (camDistance > 25.0f) camDistance = 25.0f; // Maximo aumentado
        glutPostRedisplay();
    }
}

void onMotion(int x, int y) {
    camAngleX = (camAngleX + (y - mouseY));
    camAngleY = (camAngleY + (x - mouseX));
    mouseX = x;
    mouseY = y;
    glutPostRedisplay();
}
