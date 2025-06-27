#include "objects/common.h"

// Definicion de colores globales
const GLfloat COLOR_BLANCO[] = {1.0f, 1.0f, 1.0f};  
const GLfloat COLOR_NEGRO[] = {0.1f, 0.1f, 0.1f};  
const GLfloat COLOR_GRIS[] = {0.6f, 0.6f, 0.6f};  
const GLfloat COLOR_MADERA[] = {0.8f, 0.5f, 0.2f};  
const GLfloat COLOR_MADERA_OSCURA[] = {0.6f, 0.3f, 0.1f};  
const GLfloat COLOR_METAL[] = {0.8f, 0.8f, 0.9f};  
const GLfloat COLOR_AZUL[] = {0.0f, 0.4f, 0.8f};  
const GLfloat COLOR_ROJO[] = {0.8f, 0.1f, 0.1f};
const GLfloat COLOR_VERDE[] = {0.2f, 0.6f, 0.2f};
const GLfloat COLOR_MARRON[] = {0.4f, 0.2f, 0.1f};

// Funcion basica para dibujar cubos (compartida)
void drawCube(GLfloat width, GLfloat height, GLfloat depth, const GLfloat* color) {  
    glPushMatrix();  
    glColor3fv(color);  
    glScalef(width, height, depth);  

    // Frente  
    glBegin(GL_QUADS);  
    glNormal3f(0.0f, 0.0f, 1.0f);  
    glVertex3f(-0.5f, -0.5f, 0.5f);  
    glVertex3f(0.5f, -0.5f, 0.5f);  
    glVertex3f(0.5f, 0.5f, 0.5f);  
    glVertex3f(-0.5f, 0.5f, 0.5f);  
    glEnd();  

    // Atras  
    glBegin(GL_QUADS);  
    glNormal3f(0.0f, 0.0f, -1.0f);  
    glVertex3f(-0.5f, -0.5f, -0.5f);  
    glVertex3f(-0.5f, 0.5f, -0.5f);  
    glVertex3f(0.5f, 0.5f, -0.5f);  
    glVertex3f(0.5f, -0.5f, -0.5f);  
    glEnd();  

    // Arriba  
    glBegin(GL_QUADS);  
    glNormal3f(0.0f, 1.0f, 0.0f);  
    glVertex3f(-0.5f, 0.5f, -0.5f);  
    glVertex3f(-0.5f, 0.5f, 0.5f);  
    glVertex3f(0.5f, 0.5f, 0.5f);  
    glVertex3f(0.5f, 0.5f, -0.5f);  
    glEnd();  

    // Abajo  
    glBegin(GL_QUADS);  
    glNormal3f(0.0f, -1.0f, 0.0f);  
    glVertex3f(-0.5f, -0.5f, -0.5f);  
    glVertex3f(0.5f, -0.5f, -0.5f);  
    glVertex3f(0.5f, -0.5f, 0.5f);  
    glVertex3f(-0.5f, -0.5f, 0.5f);  
    glEnd();  

    // Derecha  
    glBegin(GL_QUADS);  
    glNormal3f(1.0f, 0.0f, 0.0f);  
    glVertex3f(0.5f, -0.5f, -0.5f);  
    glVertex3f(0.5f, 0.5f, -0.5f);  
    glVertex3f(0.5f, 0.5f, 0.5f);  
    glVertex3f(0.5f, -0.5f, 0.5f);  
    glEnd();  

    // Izquierda  
    glBegin(GL_QUADS);  
    glNormal3f(-1.0f, 0.0f, 0.0f);  
    glVertex3f(-0.5f, -0.5f, -0.5f);  
    glVertex3f(-0.5f, -0.5f, 0.5f);  
    glVertex3f(-0.5f, 0.5f, 0.5f);  
    glVertex3f(-0.5f, 0.5f, -0.5f);  
    glEnd();  

    glPopMatrix();  
}

// Funcion para dibujar una silla individual con rotacion
void drawSilla(float posX, float posY, float posZ, const GLfloat* colorAsiento, const GLfloat* colorRespaldo, float rotacionY) {
    glPushMatrix();
    glTranslatef(posX, posY, posZ);
    glRotatef(rotacionY, 0.0f, 1.0f, 0.0f);

    // Asiento
    glPushMatrix();
    glTranslatef(0.0f, 0.2f, 0.0f);
    drawCube(0.4f, 0.05f, 0.4f, colorAsiento);
    glPopMatrix();

    // Respaldo
    glPushMatrix();
    glTranslatef(0.0f, 0.5f, -0.2f);
    drawCube(0.4f, 0.6f, 0.05f, colorRespaldo);
    glPopMatrix();

    // Patas
    for (int k = -1; k <= 1; k += 2) {
        for (int l = -1; l <= 1; l += 2) {
            glPushMatrix();
            glTranslatef(k * 0.15f, 0.0f, l * 0.15f);
            drawCube(0.05f, 0.4f, 0.05f, COLOR_MADERA_OSCURA);
            glPopMatrix();
        }
    }
    glPopMatrix();
}

// Funcion para dibujar una mesa individual
void drawMesaIndividual(float posX, float posY, float posZ, float width, float depth, const GLfloat* colorSuperficie) {
    glPushMatrix();
    glTranslatef(posX, posY, posZ);

    // Superficie de la mesa
    glPushMatrix();
    glTranslatef(0.0f, 0.4f, 0.0f);
    drawCube(width, 0.1f, depth, colorSuperficie);
    glPopMatrix();

    // Patas de la mesa
    float offsetX = (width - 0.1f) * 0.5f * 0.8f;
    float offsetZ = (depth - 0.1f) * 0.5f * 0.8f;
    
    for (int i = -1; i <= 1; i += 2) {
        for (int j = -1; j <= 1; j += 2) {
            glPushMatrix();
            glTranslatef(i * offsetX, 0.0f, j * offsetZ);
            drawCube(0.1f, 0.8f, 0.1f, COLOR_MADERA_OSCURA);
            glPopMatrix();
        }
    }
    glPopMatrix();
}
