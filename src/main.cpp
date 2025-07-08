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
    float coloresFondo[3][3] = {
        {0.8f, 0.8f, 0.8f}, // Gris claro
        {1.0f, 1.0f, 1.0f}, // Blanco
        {0.96f, 0.96f, 0.86f} // Beige
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

    // Calcula posicion de camara con coordenadas esfericas
    float camX = camDistance * cos(camAngleY * M_PI/180) * cos(camAngleX * M_PI/180);
    float camY = camDistance * sin(camAngleX * M_PI/180);
    float camZ = camDistance * sin(camAngleY * M_PI/180) * cos(camAngleX * M_PI/180);
    
    // Vista (punto de mira ajustado para centrar toda la escena expandida)
    gluLookAt(  
        camX, camY, camZ,  // Posicion de la camara
        2.25f, 0.0f, 0.5f,  // Punto al que mira (centrado en la escena completa)
        0.0f, 1.0f, 0.0f    // Vector "arriba"  
    );

    // Aplicar rotacion de animacion si esta activa
    if (bAnimacionActiva) {
        glRotatef(fTiempoAnimacion, 0.0f, 1.0f, 0.0f);
    }

    // Dibujar elementos segun la seccion visible
    if (iSeccionVisible == 0 || iSeccionVisible == 3) { // Cocina o todo
        drawParedes();  
        drawPiso();  
        drawKitchen();
        // Dibujar segundo piso de la cocina
        drawSecondFloorKitchen();
    }
    
    if (iSeccionVisible == 1 || iSeccionVisible == 3) { // Comedor o todo
        if (iSeccionVisible == 1) { // Solo comedor, dibujar piso basico
            glPushMatrix();  
            glTranslatef(2.25f, -0.7f, 4.0f);
            drawCube(12.5f, 0.1f, 6.0f, COLOR_GRIS);
            glPopMatrix();
        }
        drawDining();
    }
    
    if (iSeccionVisible == 2 || iSeccionVisible == 3) { // Almacen o todo
        if (iSeccionVisible == 2) { // Solo almacen, dibujar piso basico
            glPushMatrix();  
            glTranslatef(6.0f, -0.7f, -1.5f);
            drawCube(5.0f, 0.1f, 5.0f, COLOR_GRIS);
            glPopMatrix();
        }
        drawStorage();
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
    if (bAnimacionActiva) {
        glutPostRedisplay(); // Solo redibuja si la animacion esta activa
    }
}

// **FUNCION PARA MANEJAR TECLAS (OPCIONAL)**
void onKeyboard(unsigned char key, int x, int y) {
    switch(key) {
        case 27: // ESC para salir
            exit(0);
            break;
        case 'r': case 'R': // Reset vista
            camAngleX = 20.0f;
            camAngleY = 45.0f;
            camDistance = 15.0f;
            iTipoCamara = 0;
            glutPostRedisplay();
            break;
        case 'a': case 'A': // Toggle animacion
            bAnimacionActiva = !bAnimacionActiva;
            if (!bAnimacionActiva) fTiempoAnimacion = 0.0f;
            break;
        case '1': // Vista cocina
            iTipoCamara = 1;
            configurarCamara();
            glutPostRedisplay();
            break;
        case '2': // Vista comedor
            iTipoCamara = 2;
            configurarCamara();
            glutPostRedisplay();
            break;
        case '3': // Vista almacen
            iTipoCamara = 3;
            configurarCamara();
            glutPostRedisplay();
            break;
    }
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
    glutMouseFunc(onMouse);      // Para clics del mouse
    glutMotionFunc(onMotion);    // Para movimiento con boton presionado
    glutIdleFunc(idle);          // Para animacion continua
    glutKeyboardFunc(onKeyboard); // Para control por teclado

    glutMainLoop();  
    return 0;  
}
