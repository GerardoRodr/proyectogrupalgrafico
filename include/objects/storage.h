#ifndef STORAGE_H
#define STORAGE_H

#include "common.h"

// Funciones especificas del almacen
void drawCajaComida(float posX, float posY, float posZ, float width, float height, float depth, const GLfloat* colorPrincipal, const GLfloat* colorEtiqueta);
void drawBotella(float posX, float posY, float posZ, float altura, const GLfloat* colorLiquido);
void drawSaco(float posX, float posY, float posZ, const GLfloat* colorSaco);
void drawEstanteria(float posX, float posY, float posZ);
void drawCongelador();

// Funcion principal para dibujar todo el almacen
void drawAlmacenComida();

// Alias para compatibilidad
void drawStorage();

#endif
