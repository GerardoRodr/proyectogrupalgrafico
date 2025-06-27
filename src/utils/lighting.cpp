#include "utils/lighting.h"

// Variables globales de iluminación
int iTipoLuz = 0; // 0=dia, 1=noche, 2=ambiente

// **CONFIGURACION DE ILUMINACION**
void configurarIluminacion() {
    // Posicion de la luz
    GLfloat lightPos[] = {5.0f, 8.0f, 5.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    
    if (iTipoLuz == 0) { // Luz de dia
        GLfloat lightColor[] = {1.0f, 1.0f, 0.9f, 1.0f}; // Blanco calido
        GLfloat ambientLight[] = {0.4f, 0.4f, 0.4f, 1.0f}; // Ambiente claro
        glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
        glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    }
    else if (iTipoLuz == 1) { // Luz de noche
        GLfloat lightColor[] = {0.7f, 0.7f, 1.0f, 1.0f}; // Azul frio
        GLfloat ambientLight[] = {0.1f, 0.1f, 0.2f, 1.0f}; // Ambiente oscuro
        glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
        glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    }
    else { // Luz ambiente suave
        GLfloat lightColor[] = {1.0f, 0.8f, 0.6f, 1.0f}; // Amarillo suave
        GLfloat ambientLight[] = {0.6f, 0.5f, 0.4f, 1.0f}; // Ambiente calido
        glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
        glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    }
}
