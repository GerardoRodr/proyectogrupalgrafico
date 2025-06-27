#ifndef COMMON_H
#define COMMON_H

#include <GL/freeglut.h>
#include <cmath>

// Paleta de colores globales
extern const GLfloat COLOR_BLANCO[];
extern const GLfloat COLOR_NEGRO[];
extern const GLfloat COLOR_GRIS[];
extern const GLfloat COLOR_MADERA[];
extern const GLfloat COLOR_MADERA_OSCURA[];
extern const GLfloat COLOR_METAL[];
extern const GLfloat COLOR_AZUL[];
extern const GLfloat COLOR_ROJO[];
extern const GLfloat COLOR_VERDE[];
extern const GLfloat COLOR_MARRON[];

// Funciones basicas compartidas
void drawCube(GLfloat width, GLfloat height, GLfloat depth, const GLfloat* color);
void drawSilla(float posX, float posY, float posZ, const GLfloat* colorAsiento, const GLfloat* colorRespaldo, float rotacionY = 0.0f);
void drawMesaIndividual(float posX, float posY, float posZ, float width, float depth, const GLfloat* colorSuperficie);

#endif
