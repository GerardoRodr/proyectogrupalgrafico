#ifndef CAMERA_H
#define CAMERA_H

// Variables globales de camara
extern float camAngleX;
extern float camAngleY;
extern float camDistance;
extern int mouseX, mouseY;
extern bool mouseLeftDown;
extern int iTipoCamara;

// Funciones de control de camara
void configurarCamara();
void onMouse(int button, int state, int x, int y);
void onMotion(int x, int y);

#endif