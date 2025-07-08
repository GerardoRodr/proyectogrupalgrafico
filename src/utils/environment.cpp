#include "utils/environment.h"
#include "objects/common.h"

void drawPiso() {  
    // Piso principal de la cocina extendido hasta la pared derecha
    glPushMatrix();  
    glTranslatef(2.25f, -0.7f, -1.5f);  // Recentrado para cubrir hasta pared derecha
    drawCube(12.5f, 0.1f, 5.0f, COLOR_GRIS);  // Ancho aumentado para llegar a X=8.5
    glPopMatrix();  
    
    // Piso del comedor extendido hasta la pared derecha
    glPushMatrix();  
    glTranslatef(2.25f, -0.7f, 4.0f);  // Recentrado para cubrir hasta pared derecha
    drawCube(12.5f, 0.1f, 6.0f, COLOR_GRIS);  // Ancho aumentado para llegar a X=8.5
    glPopMatrix();
}

void drawParedes() {  
    // Pared trasera de la cocina (extendida para cubrir tambien el almacen)
    glPushMatrix();  
    glTranslatef(2.2f, 0.6f, -4.0f);  // Centrada para cubrir cocina + almacen
    drawCube(12.5f, 2.6f, 0.1f, COLOR_BLANCO);  // Mas ancha
    glPopMatrix();  

    // Pared lateral IZQUIERDA de la cocina (extendida para incluir el comedor)
    glPushMatrix();  
    glTranslatef(-4.0f, 0.6f, 1.5f);  // Solo la pared izquierda
    drawCube(0.1f, 2.6f, 11.0f, COLOR_BLANCO); // Extendida hacia adelante
    glPopMatrix();  
    
    // Pared lateral derecha del almacen (ajustada al mismo tamaño que la izquierda)
    glPushMatrix();
    glTranslatef(8.5f, 0.6f, 1.5f);  // Misma posicion Z que la pared izquierda
    drawCube(0.1f, 2.6f, 11.0f, COLOR_BLANCO);  // Misma profundidad que la pared izquierda
    glPopMatrix();
}

void drawGrassExterior() {
    // Dibujar el pasto exterior
    glPushMatrix();
    glTranslatef(0.0f, -1.0f, 0.0f);  // Posicionar en el suelo
    glColor3f(0.1f, 0.8f, 0.1f);  // Color verde pasto
    glBegin(GL_QUADS);
        glVertex3f(-10.0f, 0.0f, -10.0f);  // Vertice 1: Esquina TRASERA-IZQUIERDA
        glVertex3f(10.0f, 0.0f, -10.0f);   // Vertice 2: Esquina TRASERA-DERECHA  
        glVertex3f(10.0f, 0.0f, 10.0f);    // Vertice 3: Esquina FRONTAL-DERECHA
        glVertex3f(-10.0f, 0.0f, 10.0f);   // Vertice 4: Esquina FRONTAL-IZQUIERDA
    glEnd();
    glPopMatrix();
}

void drawAcera() {
    glPushMatrix();
    glTranslatef(2.25f, -0.7f, 8.0f);
    drawCube(32.5f, 0.1f, 2.0f, COLOR_METAL);
    glPopMatrix();
}

void drawCarretera() {
    glPushMatrix();
    glTranslatef(2.25f, -0.7f, 11.0f);
    drawCube(32.5f, 0.1f, 4.0f, COLOR_NEGRO);
    glPopMatrix();
}

void drawLineasAmarillasCarretera(){
    // Lineas amarillas discontinuas en el centro de la carretera
    glColor3f(1.0f, 1.0f, 0.0f);  // Color amarillo
    
    // Configuracion de las lineas
    float inicioX = -14.0f;  // Inicio del ancho de la carretera (2.25 - 32.5/2)
    float finX = 18.5f;      // Final del ancho de la carretera (2.25 + 32.5/2)
    float centroZ = 11.0f;   // Centro de la carretera (igual que drawCarretera)
    float alturaY = -0.59f;  // Ligeramente por encima del asfalto
    
    float longitudLinea = 2.0f;  // Longitud de cada linea amarilla
    float espacioEntreLineas = 1.0f;  // Espacio entre lineas
    float anchoLinea = 0.2f;     // Ancho de cada linea
    
    // Dibujar lineas amarillas discontinuas a lo largo de la carretera
    for (float x = inicioX; x < finX; x += (longitudLinea + espacioEntreLineas)) {
        glPushMatrix();
        glTranslatef(x + longitudLinea/2, alturaY, centroZ);
        
        // Dibujar linea amarilla usando primitivas OpenGL
        glBegin(GL_QUADS);
            // Cara superior de la linea amarilla
            glVertex3f(-longitudLinea/2, 0.005f, -anchoLinea/2);
            glVertex3f(longitudLinea/2, 0.005f, -anchoLinea/2);
            glVertex3f(longitudLinea/2, 0.005f, anchoLinea/2);
            glVertex3f(-longitudLinea/2, 0.005f, anchoLinea/2);
        glEnd();
        
        glPopMatrix();
    }
}