#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <GL/freeglut.h>

// Funciones del entorno
void drawPiso();
void drawParedes();
void drawGrassExterior(float posX, float posY, float posZ, float ancho, float profundidad);
void drawAcera();
void drawCarretera();
void drawLineasAmarillasCarretera();
void edificio(float posX, float posY, float posZ, float escala, float rotacionY, const GLfloat* colorParedes);

#endif