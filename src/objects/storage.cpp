#include "objects/storage.h"

// =============================================  
// **ALMACEN DE COMIDA**  
// =============================================  

void drawCajaComida(float posX, float posY, float posZ, float width, float height, float depth, const GLfloat* colorPrincipal, const GLfloat* colorEtiqueta) {
    // Caja principal
    glPushMatrix();
    glTranslatef(posX, posY, posZ);
    drawCube(width, height, depth, colorPrincipal);
    
    // Etiqueta frontal
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, (depth/2) + 0.01f);
    drawCube(width * 0.7f, height * 0.4f, 0.01f, colorEtiqueta);
    glPopMatrix();
    
    glPopMatrix();
}

void drawBotella(float posX, float posY, float posZ, float altura, const GLfloat* colorLiquido) {
    glPushMatrix();
    glTranslatef(posX, posY, posZ);
    
    // **HABILITAR TRANSPARENCIA**
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // **PRIMERO DIBUJAR EL LIQUIDO (mas opaco y visible)**
    glColor4f(colorLiquido[0], colorLiquido[1], colorLiquido[2], 0.9f);  // Liquido casi opaco
    glPushMatrix();
    glTranslatef(0.0f, altura/2 - 0.05f, 0.0f);
    glScalef(0.08f, altura - 0.1f, 0.08f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // **LUEGO LA BOTELLA (mas transparente)**
    glColor4f(1.0f, 1.0f, 1.0f, 0.2f);  // Vidrio muy transparente
    glPushMatrix();
    glTranslatef(0.0f, altura/2, 0.0f);
    glScalef(0.1f, altura, 0.1f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // **FINALMENTE LA TAPA (opaca)**
    glColor4f(COLOR_METAL[0], COLOR_METAL[1], COLOR_METAL[2], 1.0f);  // Completamente opaca
    glPushMatrix();
    glTranslatef(0.0f, altura - 0.02f, 0.0f);
    glScalef(0.12f, 0.04f, 0.12f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // **DESHABILITAR TRANSPARENCIA**
    glDisable(GL_BLEND);
    
    glPopMatrix();
}

void drawSaco(float posX, float posY, float posZ, const GLfloat* colorSaco) {
    glPushMatrix();
    glTranslatef(posX, posY, posZ);
    
    // Saco base (forma irregular usando esferas deformadas)
    glColor3fv(colorSaco);
    glPushMatrix();
    glScalef(0.4f, 0.6f, 0.3f);
    glutSolidSphere(0.5f, 12, 8);
    glPopMatrix();
    
    // Parte superior del saco (mas estrecha)
    glPushMatrix();
    glTranslatef(0.0f, 0.25f, 0.0f);
    glScalef(0.25f, 0.2f, 0.2f);
    glutSolidSphere(0.5f, 12, 8);
    glPopMatrix();
    
    glPopMatrix();
}

void drawEstanteria(float posX, float posY, float posZ) {
    // Estructura principal de la estanteria
    glPushMatrix();
    glTranslatef(posX, posY, posZ);
    
    // Postes verticales
    for(int i = 0; i < 3; i++) {
        glPushMatrix();
        glTranslatef(-0.8f + i * 0.8f, 0.0f, 0.0f);
        drawCube(0.1f, 2.0f, 0.1f, COLOR_METAL);
        glPopMatrix();
    }
    
    // Estantes horizontales (4 niveles)
    for(int nivel = 0; nivel < 4; nivel++) {
        glPushMatrix();
        glTranslatef(0.0f, -0.7f + nivel * 0.5f, 0.0f);
        drawCube(1.6f, 0.05f, 0.6f, COLOR_METAL);
        glPopMatrix();
    }
    
    glPopMatrix();
}

void drawCongelador() {
    glPushMatrix();
    glTranslatef(5.5f, 0.0f, -2.0f);
    
    // Cuerpo principal del congelador
    drawCube(1.2f, 1.6f, 0.8f, COLOR_BLANCO);
    
    // Tapa superior
    glPushMatrix();
    glTranslatef(0.0f, 0.85f, 0.0f);
    drawCube(1.25f, 0.1f, 0.85f, COLOR_GRIS);
    glPopMatrix();
    
    // Manija de la tapa
    glPushMatrix();
    glTranslatef(0.4f, 0.9f, 0.0f);
    drawCube(0.2f, 0.05f, 0.1f, COLOR_NEGRO);
    glPopMatrix();
    
    // Rejilla de ventilacion
    for(int i = 0; i < 3; i++) {
        glPushMatrix();
        glTranslatef(-0.3f + i * 0.3f, -0.5f, 0.41f);
        drawCube(0.1f, 0.3f, 0.02f, COLOR_NEGRO);
        glPopMatrix();
    }
    
    glPopMatrix();
}

// Funcion para dibujar una estanteria completa con todos sus productos
void drawEstanteriaCompleta(float posX, float posY, float posZ, int tipoEstanteria) {
    glPushMatrix();
    glTranslatef(posX, posY, posZ);
    
    // Dibujar la estructura de la estanteria (centrada en el origen local)
    drawEstanteria(0.0f, 0.0f, 0.0f);
    
    if(tipoEstanteria == 1) {
        // **ESTANTERIA TIPO 1 - Productos variados**
        
        // Nivel inferior - Sacos de harina y azucar (detras de la estanteria)
        drawSaco(-0.6f, -0.7f, -1.3f, COLOR_BLANCO);     // Saco de harina
        drawSaco(-0.2f, -0.7f, -1.3f, COLOR_MARRON);     // Saco de azucar morena
        drawSaco(0.2f, -0.7f, -1.3f, COLOR_BLANCO);      // Otro saco de harina
        
        // Nivel 2 - Cajas de cereales y productos secos
        drawCajaComida(-0.5f, 0.0f, 0.0f, 0.3f, 0.4f, 0.2f, COLOR_ROJO, COLOR_BLANCO);
        drawCajaComida(-0.5f, -0.5f, -0.1f, 0.25f, 0.35f, 0.15f, COLOR_AZUL, COLOR_BLANCO);
        drawCajaComida(0.3f, -0.5f, 0.1f, 0.28f, 0.38f, 0.18f, COLOR_ROJO, COLOR_BLANCO);
        drawCajaComida(0.3f, 0.0f, 0.1f, 0.28f, 0.38f, 0.18f, COLOR_VERDE, COLOR_BLANCO);
        
        // Nivel 3 - Latas y conservas
        for(int i = 0; i < 4; i++) {
            glPushMatrix();
            glTranslatef(-0.6f + i * 0.25f, 0.3f, 0.0f + (i%2) * 0.1f);
            glColor3fv(COLOR_METAL);
            glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
            glutSolidCylinder(0.08f, 0.2f, 12, 8);
            // Etiqueta de la lata
            glColor3fv((i%2 == 0) ? COLOR_ROJO : COLOR_VERDE);
            glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
            glTranslatef(0.0f, 0.08f, 0.1f);
            glScalef(0.1f, 0.05f, 0.01f);
            glutSolidCube(1.0f);
            glPopMatrix();
        }
        
        // Nivel superior - Botellas de aceites y vinagres
        drawBotella(-0.5f, 0.8f, 0.0f, 0.3f, COLOR_VERDE);     // Aceite de oliva
        drawBotella(-0.2f, 0.8f, -0.1f, 0.25f, COLOR_ROJO);    // Vinagre
        drawBotella(0.1f, 0.8f, 0.1f, 0.28f, COLOR_VERDE);     // Otro aceite
        
    } else if(tipoEstanteria == 2) {
        // **ESTANTERIA TIPO 2 - Productos diferentes**
        
        // Nivel inferior - Cajas grandes de productos
        drawCajaComida(-0.5f, 0.05f, 0.0f, 0.4f, 0.5f, 0.3f, COLOR_MARRON, COLOR_BLANCO);
        drawCajaComida(0.4f, 0.05f, 0.0f, 0.35f, 0.45f, 0.25f, COLOR_AZUL, COLOR_BLANCO);
        drawCajaComida(0.5f, -0.5f, 0.05f, 0.38f, 0.48f, 0.28f, COLOR_VERDE, COLOR_BLANCO);
        
        // Nivel 2 - Paquetes medianos (algunos en la barra cercana)
        drawCajaComida(-1.3f, 0.1f, 1.9f, 0.2f, 0.3f, 0.15f, COLOR_ROJO, COLOR_BLANCO);
        drawCajaComida(-1.0f, 0.1f, 2.05f, 0.2f, 0.3f, 0.15f, COLOR_AZUL, COLOR_BLANCO);
        drawCajaComida(-0.7f, 0.1f, 2.2f, 0.2f, 0.3f, 0.15f, COLOR_VERDE, COLOR_BLANCO);
        
        // Nivel 3 - Mas latas
        for(int i = 0; i < 5; i++) {
            glPushMatrix();
            glTranslatef(-0.5f + i * 0.2f, 0.3f, 0.0f + (i%3) * 0.1f);
            glColor3fv(COLOR_METAL);
            glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
            glutSolidCylinder(0.06f, 0.18f, 10, 6);
            // Etiqueta de la lata
            glColor3fv((i%3 == 0) ? COLOR_ROJO : (i%3 == 1) ? COLOR_VERDE : COLOR_AZUL);
            glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
            glTranslatef(0.0f, 0.06f, 0.09f);
            glScalef(0.08f, 0.04f, 0.01f);
            glutSolidCube(1.0f);
            glPopMatrix();
        }
    }
    
    glPopMatrix();
}

void drawAlmacenComida() {
    // **OFFSET PARA MOVER TODO EL ALMACEN**
    float offsetX = 0.5f; // Gente cambien este valor pa mover las cosas del almacen a la derecha/izquierda
    float offsetZ = -1.45f; // y este para atras o adelante
    
    // **ESTANTERIAS COMPLETAS CON COMIDA**
    
    // Estanteria 1 - Izquierda (con productos tipo 1)
    drawEstanteriaCompleta(2.0f + offsetX, 0.3f, -1.0f + offsetZ, 1);
    
    // Estanteria 2 - Centro (con productos tipo 2)
    drawEstanteriaCompleta(4.5f + offsetX, 0.3f, -0.5f + offsetZ, 2);
    
    // **CONGELADOR** (tambien se modifica la funcion drawCongelador)
    glPushMatrix();
    glTranslatef(5.5f + offsetX, 0.0f, -2.0f + offsetZ);
    
    // Cuerpo principal del congelador
    drawCube(1.2f, 1.6f, 0.8f, COLOR_BLANCO);
    
    // Tapa superior
    glPushMatrix();
    glTranslatef(0.0f, 0.85f, 0.0f);
    drawCube(1.25f, 0.1f, 0.85f, COLOR_GRIS);
    glPopMatrix();
    
    // Manija de la tapa
    glPushMatrix();
    glTranslatef(0.4, 0.9f, 0.0f);
    drawCube(0.2f, 0.05f, 0.1f, COLOR_NEGRO);
    glPopMatrix();
    
    // Rejilla de ventilacion
    for(int i = 0; i < 3; i++) {
        glPushMatrix();
        glTranslatef(-0.3f + i * 0.3f, -0.5f, 0.41f);
        drawCube(0.1f, 0.3f, 0.02f, COLOR_NEGRO);
        glPopMatrix();
    }
    
    glPopMatrix();
    
    // **CAJAS EN EL TECHO**
    
    // Mas cajas dispersas (sobre la barra ya q estamos xdd)
    drawCajaComida(4.5f + offsetX, 0.4f, 1.7f + offsetZ, 0.4f, 0.3f, 0.3f, COLOR_AZUL, COLOR_BLANCO);
    drawCajaComida(5.8f + offsetX, 0.4f, 1.7f + offsetZ, 0.35f, 0.35f, 0.25f, COLOR_VERDE, COLOR_BLANCO);
    
    // **SACOS ADICIONALES EN EL SUELO**
    for(int i=0; i<2; i++) {
        drawSaco(3.5f + offsetX + i, -0.5f, -2.3f + offsetZ, COLOR_BLANCO);      // Saco de arroz
        drawSaco(3.8f + offsetX + i, -0.5f, -2.3f + offsetZ, COLOR_MARRON);     // Saco de frijoles
    }
    
    // **BOTELLAS EN LA BARRA**
    for(int i = 0; i < 9; i++) {
        drawBotella(4.2f + offsetX + i * 0.2f, 0.25f, 1.0f + offsetZ, 0.4f, 
                   (i == 0) ? COLOR_VERDE : (i == 1) ? COLOR_ROJO : COLOR_AZUL);
    }
}

// Alias para compatibilidad
void drawStorage() {
    drawAlmacenComida();
}
