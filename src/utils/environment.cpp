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

void drawGrassExterior(float posX, float posY, float posZ, float ancho, float profundidad) {
    // Dibujar pasto exterior reutilizable con parámetros personalizables
    glPushMatrix();
    glTranslatef(posX, posY, posZ);  // Posición personalizable
    glColor3f(0.1f, 0.8f, 0.1f);  // Color verde pasto
    glBegin(GL_QUADS);
        // Dimensiones personalizables
        float mitadAncho = ancho / 2.0f;
        float mitadProfundidad = profundidad / 2.0f;
        glVertex3f(-mitadAncho, 0.0f, -mitadProfundidad);  // Esquina TRASERA-IZQUIERDA
        glVertex3f(mitadAncho, 0.0f, -mitadProfundidad);   // Esquina TRASERA-DERECHA  
        glVertex3f(mitadAncho, 0.0f, mitadProfundidad);    // Esquina FRONTAL-DERECHA
        glVertex3f(-mitadAncho, 0.0f, mitadProfundidad);   // Esquina FRONTAL-IZQUIERDA
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

void edificio(float posX, float posY, float posZ, float escala, float rotacionY, const GLfloat* colorParedes) {
    glPushMatrix();
    
    // Aplicar transformaciones principales
    glTranslatef(posX, posY, posZ);
    glRotatef(rotacionY, 0.0f, 1.0f, 0.0f);
    glScalef(escala, escala, escala);
    
    // Piso del edificio
    glPushMatrix();
    glTranslatef(0.0f, -0.7f, 0.0f);
    drawCube(5.0f, 0.1f, 2.5f, COLOR_GRIS);
    glPopMatrix();
    
    // Estructura principal del edificio - 3 pisos (usando el color parametrizado)
    glPushMatrix();
    glTranslatef(0.0f, 1.8f, 0.0f);
    drawCube(5.0f, 5.6f, 2.5f, colorParedes);
    glPopMatrix();
    
    // Techo del edificio
    glPushMatrix();
    glTranslatef(0.0f, 4.7f, 0.0f);
    drawCube(5.2f, 0.3f, 2.7f, COLOR_MADERA_OSCURA);
    glPopMatrix();
    
    // Cornisa decorativa entre pisos
    glPushMatrix();
    glTranslatef(0.0f, 1.8f, 0.0f);
    drawCube(5.1f, 0.1f, 2.6f, COLOR_GRIS);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.0f, 3.3f, 0.0f);
    drawCube(5.1f, 0.1f, 2.6f, COLOR_GRIS);
    glPopMatrix();
    
    // Puerta principal centrada
    glPushMatrix();
    glTranslatef(0.0f, 0.5f, 1.25f);
    drawCube(0.8f, 2.0f, 0.1f, COLOR_MADERA);
    glPopMatrix();
    
    // Marco de la puerta
    glPushMatrix();
    glTranslatef(0.0f, 0.5f, 1.27f);
    drawCube(1.0f, 2.2f, 0.05f, COLOR_MADERA_OSCURA);
    glPopMatrix();
    
    // Escalon de la puerta
    glPushMatrix();
    glTranslatef(0.0f, -0.6f, 1.3f);
    drawCube(1.2f, 0.1f, 0.3f, COLOR_GRIS);
    glPopMatrix();
    
    // Ventanas primer piso - simetricas con marcos
    glPushMatrix();
    glTranslatef(-1.7f, 1.0f, 1.26f);
    drawCube(0.6f, 0.6f, 0.08f, COLOR_AZUL);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-1.7f, 1.0f, 1.28f);
    drawCube(0.8f, 0.8f, 0.03f, COLOR_BLANCO);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(1.7f, 1.0f, 1.26f);
    drawCube(0.6f, 0.6f, 0.08f, COLOR_AZUL);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(1.7f, 1.0f, 1.28f);
    drawCube(0.8f, 0.8f, 0.03f, COLOR_BLANCO);
    glPopMatrix();
    
    // Ventanas segundo piso - simetricas con marcos
    glPushMatrix();
    glTranslatef(-1.7f, 2.5f, 1.26f);
    drawCube(0.6f, 0.6f, 0.08f, COLOR_AZUL);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-1.7f, 2.5f, 1.28f);
    drawCube(0.8f, 0.8f, 0.03f, COLOR_BLANCO);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.0f, 2.5f, 1.26f);
    drawCube(0.6f, 0.6f, 0.08f, COLOR_AZUL);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.0f, 2.5f, 1.28f);
    drawCube(0.8f, 0.8f, 0.03f, COLOR_BLANCO);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(1.7f, 2.5f, 1.26f);
    drawCube(0.6f, 0.6f, 0.08f, COLOR_AZUL);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(1.7f, 2.5f, 1.28f);
    drawCube(0.8f, 0.8f, 0.03f, COLOR_BLANCO);
    glPopMatrix();
    
    // Ventanas tercer piso - simetricas con marcos
    glPushMatrix();
    glTranslatef(-1.7f, 4.0f, 1.26f);
    drawCube(0.6f, 0.6f, 0.08f, COLOR_AZUL);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-1.7f, 4.0f, 1.28f);
    drawCube(0.8f, 0.8f, 0.03f, COLOR_BLANCO);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.0f, 4.0f, 1.26f);
    drawCube(0.6f, 0.6f, 0.08f, COLOR_AZUL);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.0f, 4.0f, 1.28f);
    drawCube(0.8f, 0.8f, 0.03f, COLOR_BLANCO);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(1.7f, 4.0f, 1.26f);
    drawCube(0.6f, 0.6f, 0.08f, COLOR_AZUL);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(1.7f, 4.0f, 1.28f);
    drawCube(0.8f, 0.8f, 0.03f, COLOR_BLANCO);
    glPopMatrix();
    
    // Detalles decorativos en las esquinas
    glPushMatrix();
    glTranslatef(-2.4f, 2.8f, 0.0f);
    drawCube(0.2f, 5.6f, 0.2f, COLOR_GRIS);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(2.4f, 2.8f, 0.0f);
    drawCube(0.2f, 5.6f, 0.2f, COLOR_GRIS);
    glPopMatrix();
    
    // Letrero del edificio
    glPushMatrix();
    glTranslatef(0.0f, 1.5f, 1.3f);
    drawCube(2.0f, 0.3f, 0.05f, COLOR_NEGRO);
    glPopMatrix();
    
    glPopMatrix(); // Cerrar transformaciones principales
}