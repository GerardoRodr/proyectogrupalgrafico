#include "objects/kitchen.h"

// =============================================  
// **Jheferson: FREGADERO**  
// =============================================  
void drawFregadero() {  
    // Base del fregadero  
    glPushMatrix();  
    glTranslatef(-1.5f, 0.1f, 0.0f);  

    // Grifo  
    glPushMatrix();  
    glTranslatef(0.0f, 0.3f, 0.0f);  
    glColor3fv(COLOR_METAL);  
    glutSolidCylinder(0.03f, 0.3f, 8, 8);  

    glTranslatef(0.0f, 0.0f, 0.15f);  
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);  
    glutSolidCylinder(0.03f, 0.3f, 8, 8);  
    glPopMatrix();  

    glPopMatrix();  
}

// =============================================  
// **Brenda: GABINETES SUPERIORES**  
// =============================================  
void drawGabinetesSuperiores() {  
    for(int i = 0; i < 4; i++) {  
        glPushMatrix();  
        glTranslatef(-1.0f + i * 1.1f, 1.5f, -3.7f);  
        drawCube(1.0f, 0.6f, 0.4f, COLOR_MADERA);  

        // Puerta del gabinete  
        glTranslatef(0.0f, 0.0f, 0.21f);  
        drawCube(0.9f, 0.5f, 0.02f, COLOR_MADERA_OSCURA);  

        // Manija  
        glTranslatef(0.35f, 0.0f, 0.03f);  
        drawCube(0.08f, 0.08f, 0.04f, COLOR_METAL);  

        glPopMatrix();  
    }  
}

// =============================================  
// **Bryan: ENCIMERA Y BASE**  
// =============================================  
void drawEncimera() {  
    // Base de los gabinetes  
    glPushMatrix();  
    glTranslatef(2.4f, -0.15f, 0.0f);  
    drawCube(9.8f, 0.7f, 1.2f, COLOR_MADERA_OSCURA);  
    glPopMatrix();  

    // Encimera  
    glPushMatrix();  
    glTranslatef(2.4f, 0.2f, 0.0f);  
    drawCube(9.8f, 0.1f, 1.2f, COLOR_GRIS);  
    glPopMatrix();  

    // Cajones  
    for(int i = 0; i < 8; i++) {  
        glPushMatrix();  
        glTranslatef(-1.8f + i * 1.2f, 0.0f, -0.6f);  
        drawCube(1.0f, 0.3f, 0.05f, COLOR_MADERA);  

        // Manija del cajon  
        glTranslatef(0.0f, 0.0f, -0.05f);  
        drawCube(0.2f, 0.04f, 0.04f, COLOR_METAL);  
        glPopMatrix();  
    }  
}

// =============================================  
// **Jose: REFRIGERADOR Y ESTUFA**  
// =============================================  
void drawRefrigerador() {  
    // Cuerpo principal  
    glPushMatrix();  
    glTranslatef(-2.5f, 0.25f, -3.5f);  
    drawCube(1.0f, 1.8f, 0.8f, COLOR_GRIS);  

    // Manija  
    glPushMatrix();  
    glTranslatef(0.4f, 0.0f, 0.45f);  
    drawCube(0.1f, 0.3f, 0.05f, COLOR_METAL);  
    glPopMatrix();  

    glPopMatrix();  
}

void drawEstufa() {  
    // Base de la estufa  
    glPushMatrix();  
    glTranslatef(1.8f, 0.25f, 0.0f);  
    drawCube(1.4f, 0.1f, 1.0f, COLOR_NEGRO);  

    // Quemadores (usando glutSolidTorus)  
    for (int i = -1; i <= 1; i += 2) {  
        for (int j = -1; j <= 1; j += 2) {  
            glPushMatrix();  
            glTranslatef(i * 0.4f, 0.06f, j * 0.3f);  
            glColor3fv(COLOR_NEGRO);  
            glRotatef(90.0f, 1.0f, 0.0f, 0.0f);  
            glutSolidTorus(0.05f, 0.15f, 16, 16);  
            glPopMatrix();  
        }  
    }  
    glPopMatrix();  
}

// =============================================  
// **Angello: MESA Y SILLAS (COCINA)**  
// =============================================  
void drawMesa() {  
    // Mesa de la cocina (mesa original)
    glPushMatrix();  
    glTranslatef(0.0f, -0.3f, -2.5f);  

    // Superficie  
    glPushMatrix();  
    glTranslatef(0.0f, 0.4f, 0.0f);  
    drawCube(1.6f, 0.1f, 1.0f, COLOR_MADERA);  
    glPopMatrix();  

    // Patas  
    for (int i = -1; i <= 1; i += 2) {  
        for (int j = -1; j <= 1; j += 2) {  
            glPushMatrix();  
            glTranslatef(i * 0.7f, 0.0f, j * 0.4f);  
            drawCube(0.1f, 0.8f, 0.1f, COLOR_MADERA_OSCURA);  
            glPopMatrix();  
        }  
    }

    // Sillas de la cocina
    for (int i = 0; i < 2; i++) {  
        for (int j = 0; j < 2; j++) {  
            float posX = -1.0f + i * 2.0f;  
            float posZ = -0.8f + j * 1.6f;  
            drawSilla(posX, -0.1f, posZ, COLOR_MADERA, COLOR_MADERA, 0.0f);
        }  
    }
    glPopMatrix();  
}

// Funcion principal para dibujar toda la cocina
void drawKitchen() {
    drawGabinetesSuperiores();  
    drawEncimera();  
    drawRefrigerador();  
    drawEstufa();  
    drawMesa();
    drawFregadero();  
}
