#include "objects/kitchen.h"
#include "objects/dining.h"
#include "objects/storage.h"
#include "utils/camera.h"
#include "utils/lighting.h"
#include "utils/menu.h"
#include "utils/environment.h"
#include <GL/freeglut.h>
#include <cmath>
#include <windows.h>
#include "mmsystem.h"

// **FUNCIONES PRINCIPALES (RENDER Y CONFIG)**  
void display() {  
    // Colores de fondo posibles
    float coloresFondo[4][3] = {
        {0.8f, 0.8f, 0.8f}, // Gris claro
        {1.0f, 1.0f, 1.0f}, // Blanco
        {0.96f, 0.96f, 0.86f}, // Beige
        {0.53f, 0.81f, 0.98f} // Celeste cielo
    };
    
    glClearColor(coloresFondo[iFondo][0], 
                coloresFondo[iFondo][1], 
                coloresFondo[iFondo][2], 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Configura el estilo de visualizacion
    if(iEstiloVisualizacion == 1) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Alambre
    } else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Solido
    }
    
    // Configurar iluminacion segun el tipo seleccionado
    configurarIluminacion();
    
    // Actualizar animacion si esta activa
    actualizarAnimacion();
    
    glMatrixMode(GL_MODELVIEW);  
    glLoadIdentity();  

    // Aplicar configuracion de camara (FPS o orbital)
    applyCamera();

    // Aplicar rotacion de animacion si esta activa (solo en modo orbital)
    if (bAnimacionActiva && !bCamaraFPS) {
        glRotatef(fTiempoAnimacion, 0.0f, 1.0f, 0.0f);
    }

    // Dibujar elementos segun la seccion visible
    if (iSeccionVisible == 0 || iSeccionVisible == 2) { // Primer piso o todo
        drawParedes();  
        drawPiso();  
        drawKitchen();
        drawDining();
        drawStorage();
    }
    
    if (iSeccionVisible == 1 || iSeccionVisible == 2) { // Segundo piso o todo
        // Dibujar segundo piso de la cocina
        drawSecondFloorKitchen();
    }
    
    if (iSeccionVisible == 2) { // Solo cuando se muestra todo
        drawGrassExterior(2.25f, -0.7f, 1.5f, 32.5f, 11.0f); // Mismo nivel que acera, mismo ancho
        drawAcera();
        drawCarretera(); 
        drawLineasAmarillasCarretera();
        
        // Edificio izquierdo (al lado de la pared izquierda del restaurante) - Color verde claro
        edificio(-6.56f, 0.0f, 5.5f, 1.0f, 0.0f, COLOR_VERDE); // Separado 1cm de la pared izquierda
        
        // Edificio derecho (al lado de la pared derecha del restaurante) - Color azul claro
        edificio(11.06f, 0.0f, 5.5f, 1.0f, 0.0f, COLOR_AZUL); // Separado 1cm de la pared derecha
    }
    
    glutSwapBuffers();  
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);  // Ajusta el viewport al nuevo tamano
    glMatrixMode(GL_PROJECTION);  // Selecciona la matriz de proyeccion
    glLoadIdentity();  // Reinicia la matriz
    gluPerspective(45.0f, (float)width / (float)height, 0.1f, 100.0f);  // Proyeccion en perspectiva
    glMatrixMode(GL_MODELVIEW);  // Vuelve a la matriz de modelo-vista
}

// **FUNCION IDLE PARA ANIMACION**
void idle() {
    // **ACTUALIZAR CAMARA FPS CONSTANTEMENTE**
    updateFPSCamera();
    
    if (bAnimacionActiva) {
        glutPostRedisplay(); // Solo redibuja si la animacion esta activa
    }
}

// **FUNCION PARA MANEJAR TECLAS**
void onKeyboard(unsigned char key, int x, int y) {
    // Primero llamar la funcion de camara para manejar WASD y cambio de modo
    cameraOnKeyboard(key, x, y);
    
    switch(key) {
        case 27: // ESC para salir
            exit(0);
            break;
        case 'r': case 'R': // Reset vista
            if (bCamaraFPS) {
                // Reset FPS
                fpsX = 0.0f;
                fpsY = 2.0f;
                fpsZ = 5.0f;
                fpsPitch = 0.0f;
                fpsYaw = 0.0f;
            } else {
                // Reset orbital
                camAngleX = 20.0f;
                camAngleY = 45.0f;
                camDistance = 15.0f;
                iTipoCamara = 0;
            }
            glutPostRedisplay();
            break;
        case 'f': case 'F': // Toggle FPS mode (alternativa a 'C')
            bCamaraFPS = !bCamaraFPS;
            if (bCamaraFPS) {
                fpsX = 0.0f;
                fpsY = 2.0f;
                fpsZ = 5.0f;
                fpsPitch = 0.0f;
                fpsYaw = 0.0f;
            }
            glutPostRedisplay();
            break;
        case '1': // Vista cocina (solo en modo orbital)
            if (!bCamaraFPS) {
                iTipoCamara = 1;
                configurarCamara();
                glutPostRedisplay();
            }
            break;
        case '2': // Vista comedor (solo en modo orbital)
            if (!bCamaraFPS) {
                iTipoCamara = 2;
                configurarCamara();
                glutPostRedisplay();
            }
            break;
        case '3': // Vista almacen (solo en modo orbital)
            if (!bCamaraFPS) {
                iTipoCamara = 3;
                configurarCamara();
                glutPostRedisplay();
            }
            break;
    }
}

// **FUNCION PARA MANEJAR LIBERACION DE TECLAS**
void onKeyboardUp(unsigned char key, int x, int y) {
    cameraOnKeyboardUp(key, x, y);
}

int main(int argc, char** argv) {  
    glutInit(&argc, argv);  
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);  
    glutInitWindowSize(1024, 768);  // Ventana mas grande para ver mejor la escena expandida
    glutCreateWindow("Cocina 3D Interactiva con Menu Expandido - Grupo 10");
    
    // Configuracion OpenGL  
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);  
    glEnable(GL_LIGHTING);  
    glEnable(GL_LIGHT0);  
    glEnable(GL_COLOR_MATERIAL);  
    glEnable(GL_NORMALIZE);

    // **CONFIGURACION PARA TRANSPARENCIA**
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_BLEND);  // Deshabilitado por defecto, se activa solo cuando se necesita
    
    // Configuracion inicial de iluminacion
    configurarIluminacion();
    
    creacionMenu();

    // Callbacks  
    glutDisplayFunc(display);  
    glutReshapeFunc(reshape);  
    glutMouseFunc(cameraOnMouse);      // Para clics del mouse
    glutMotionFunc(cameraOnMotion);    // Para movimiento con boton presionado
    glutIdleFunc(idle);          // Para animacion continua
    glutKeyboardFunc(onKeyboard); // Para control por teclado
    glutKeyboardUpFunc(onKeyboardUp); // Para liberacion de teclas (necesario para WASD)

    glutMainLoop();  
    return 0;  
}