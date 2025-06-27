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
