#ifndef KITCHEN_H
#define KITCHEN_H

#include "common.h"

// Funciones especificas de la cocina
void drawFregadero();
void drawGabinetesSuperiores();
void drawEncimera();
void drawRefrigerador();
void drawEstufa();
void drawMesa();

// Funcion principal para dibujar toda la cocina
void drawKitchen();

// Funciones del segundo piso
void drawSegundoPisoParedes();
void drawSegundoPisoPiso();
void drawSegundoPisoFregadero();
void drawSegundoPisoGabinetesSuperiores();
void drawSegundoPisoEncimera();
void drawSegundoPisoRefrigerador();
void drawVIPSquareTable();
void drawSegundoPisoMesonCentral();
void drawMesasComensalesSecundoPiso();
void drawEscaleras();

// Funcion principal para dibujar el segundo piso completo
void drawSecondFloorKitchen();

// Funcion de inicializacion del segundo piso
void initSecondFloor();

#endif